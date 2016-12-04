#define __MOTOR_C__
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "stepper.h"

int verbose = 100;

/* create_motor
 * Create motor descriptor and keep all coils off and motor disabled
 * dev - name of the ppdrv port control
 * err        - Library error code
 * RETURN pointer to the motor or NULL on error
 */
ST_MOTOR *create_motor(	char *dev,int coil_en,
			int coil_as,int coil_an,
			int coil_bs,int coil_bn,
			int d360steps, 
			ST_ERROR *err)
{
ST_MOTOR *m;

	/* Allocate motor descriptor */
	m=malloc(sizeof(ST_MOTOR));
	if(NULL==m) {
		*err=ST_ERROR_NOMEM;
		return(NULL);
	}

	m->devname=dev;

	/* Open device */
	m->device=open(dev,0);
	if( m->device <= 0) {
		free(m);
		*err=ST_ERROR_BUSY;
		return(NULL);
	}

	/* Create steps table */
	m->init=create_steps(coil_as, coil_an,
                             coil_bs, coil_bn,
			     err);
	if(!m->init) {
		close( m->device);
		free(m);
		return(NULL);
	}
	m->current = m->init;
	m->mode    = ST_MODE_ERROR;
	m->status  = ST_STATUS_OFF;
	m->enable  = coil_en;
	m->coils   = coil_as | coil_an | coil_bs | coil_bn;
	m->d360steps= d360steps;
#ifdef __TEST__
	m->d360steps= 500; 
#endif
	/* Disable motor driver and turn off coils */
	/* Motor is off and free 		   */
  	ioctl(m->device, PPDRV_IOC_PINMODE_OUT,(m->enable | m->coils ));
  	ioctl(m->device, PPDRV_IOC_PINCLEAR,   (m->enable | m->coils ));

	printf("create_motor OK: %s mode=%d coils=0x%x d360steps=%d deg/FULL=%.2f deg/HALF=%.2f\n",
		m->devname, m->mode, m->coils, m->d360steps, (360.0/m->d360steps), (180.0/m->d360steps)); 

	/* Ready to spin */
	return(m);

}

ST_MOTOR *destroy_motor(ST_MOTOR *m, ST_ERROR *err)
{
	ioctl(m->device, PPDRV_IOC_PINCLEAR, (m->enable | m->coils ));
	destroy_steps(m->init,err);
	close(m->device);
	free(m);
	return(NULL);
}

/*
 * move_motor
 * move the motor of steps pass (half or full) right for positive value or left for negative,
 * move can be expressed in degree only when the motor is calibrated in how many steps are
 * necessary for a complete revolution
 * m      - motor descriptor
 * mode   - half or full
 * steps  - steps to move positive for right negative for left 
 * degree - degree to move positive for right negative for left (not implemented yet)
 * ms     - milliseconds beetween each single step
 */ 
ST_RESULT *move_motor(ST_MOTOR *m, ST_MODE mode, long steps, double degree, long ms)
{

	printf("move_motor: %s mode=%d steps=%ld degree=%.2f ms=%ld\n",
		m->devname, mode, steps, degree, ms); 
	if((steps != 0 && degree != 0) || ( degree != 0 && m->d360steps == 0)) return(NULL); 
	if(steps>0) {
		while(steps) {
			 m->current=m->current->nxt;
			 if(mode == ST_MODE_FULL && m->current->type == ST_MODE_HALF) 
				m->current=m->current->nxt;
			ioctl(m->device,PPDRV_IOC_PINSET, m->current->coils);
			printf("step_pos %ld, number=%d, coils=%d\n",
				steps,m->current->number,m->current->coils);
			steps--;
			usleep(ms*1000);
		}
	}
	if(steps<0) {
		while(steps) {
			 m->current=m->current->prv;
			 if(mode == ST_MODE_FULL && m->current->type == ST_MODE_HALF) 
				m->current=m->current->prv;
			ioctl(m->device,PPDRV_IOC_PINSET, m->current->coils);
			printf("step_neg %ld, number=%d, coils=%d\n",
				steps,m->current->number,m->current->coils);
			steps++;
			usleep(ms*1000);
		}
	}
	if(degree != 0) {
		steps=   (long) ((m->d360steps * degree ) / 360);
		if(mode == ST_MODE_HALF) steps *= 2;
		while(steps) {
			if(steps > 0) {
				m->current=m->current->nxt;
				if(mode == ST_MODE_FULL && m->current->type == ST_MODE_HALF)
					m->current=m->current->nxt;
			}
			if(steps < 0) {
				 m->current=m->current->prv;
				 if(mode == ST_MODE_FULL && m->current->type == ST_MODE_HALF) 
					m->current=m->current->prv;
			}
                        ioctl(m->device,PPDRV_IOC_PINSET, m->current->coils);
                        printf("step_degree (%.2f, %.2f), steps=%ld, number=%d, coils=%d\n",
                                degree,
				((mode == ST_MODE_FULL) ? 
				((degree-(360.0/m->d360steps)*steps)) : 
				((degree-(180.0/m->d360steps)*steps))),
				steps, m->current->number,m->current->coils);
                        if(steps > 0) steps--;
			if(steps < 0) steps++;
                        usleep(ms*1000);
                }
	}
	m->mode = mode;
	return(NULL);
}

