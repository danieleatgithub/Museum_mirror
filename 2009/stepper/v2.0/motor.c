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
	m->stats = malloc(sizeof(ST_STATS));
	if(NULL==m->stats) {
		free(m);
		*err=ST_ERROR_NOMEM;
		return(NULL);
	}

	m->devname=dev;

	/* Open device */
	m->device=open(dev,0);
	if( m->device <= 0) {
		free(m->stats);
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
		free(m->stats);
		free(m);
		return(NULL);
	}
	m->current = m->init;
	m->mode    = ST_MODE_ERROR;
	m->status  = ST_STATUS_OFF;
	m->enable  = coil_en;
	m->coils   = coil_as | coil_an | coil_bs | coil_bn;
	m->d360steps= d360steps;
	m->stats->degree   = 0.0;
	m->stats->steps = 0;
	m->stats->rotation = 0;

	/* Disable motor driver and turn off coils */
	/* Motor is off and free 		   */
  	ioctl(m->device, PPDRV_IOC_PINMODE_OUT,(m->enable | m->coils ));
  	ioctl(m->device, PPDRV_IOC_PINCLEAR,   (m->enable | m->coils ));

	if(verbose>1) 
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
	int vs = 0;
	double deg4ss;

	if(verbose>1) 
		printf("move_motor: %s mode=%d steps=%ld degree=%.2f ms=%ld\n",
		m->devname, mode, steps, degree, ms); 
	/* Check call parameter 
 	 * steps and degree are mutual exclusive, a degree rotation can be done only
 	 * if the calibration is defined
 	 */ 
	if((steps != 0 && degree != 0) || ( degree != 0 && m->d360steps == 0)) return(NULL); 
	
	/* Compute steps or degree */
	if(degree != 0) {
		/* compute steps for a full step mode and redouble it if
 		 * a half step mode is required */ 
		steps =   (long) ((m->d360steps * degree ) / 360);
		if(mode == ST_MODE_HALF)  steps *= 2;
	} else {
		/* Step motion is requested, compute how many degree and if 
 		 * motion is clockwise (positive) or anticlockwise
 		 */	 
		degree = (double) (labs(steps) * (360.0 / m->d360steps));
		if(mode == ST_MODE_HALF)  degree = degree / 2;
		if(steps < 0) degree *= -1;
	}

	if(mode == ST_MODE_HALF) deg4ss = (360.0/m->d360steps) / 2;
	else 		         deg4ss = (360.0/m->d360steps);

	/* set clockwise or anticlockwise rotation */
	if (steps > 0) vs = -1;
	if (steps < 0) vs =  1;

	/* Assertion error condition */
	if (steps == 0 || vs == 0) return(NULL);

	/* Start rotation */
	while(steps) {
		/* Go to the next step descriptor */
		if(steps > 0) {
			 m->current=m->current->nxt;
			 if(mode == ST_MODE_FULL && m->current->type == ST_MODE_HALF) 
				m->current=m->current->nxt;
			 else 
				deg4ss = deg4ss / 2;
		}
		if(steps < 0) {
			 m->current=m->current->prv;
			 if(mode == ST_MODE_FULL && m->current->type == ST_MODE_HALF) 
				m->current=m->current->prv;
			 else 
				deg4ss = deg4ss / 2;
		}
		/* Change the coils status */
		ioctl(m->device,PPDRV_IOC_PINSET, m->current->coils_set);
		ioctl(m->device,PPDRV_IOC_PINCLEAR, m->current->coils_clr);
		printf("dddd %.2f\n",deg4ss);
		m->stats->degree += deg4ss * vs * -1; 
		if(m->stats->degree >= 360.0) {
			m->stats->degree = 0;
			m->stats->rotation++;
		}
		if(m->stats->degree < 0) {
			m->stats->degree = 360.0;
			m->stats->rotation--;
		}
		m->stats->steps++;
		
		if(verbose>2) 
			printf("step rot=%ld deg(%.2f,%.2f) steps(%ld,%ld) num=%d, coils(set=0x%x clr=0x%x) type=%d\n",
			m->stats->rotation,
			degree,
			m->stats->degree,
			steps,
			m->stats->steps, 
			m->current->number,
			m->current->coils_set,
			m->current->coils_clr,
			m->current->type);
		steps += vs;
		usleep(ms*1000);
	}
	m->mode = mode;
	return(NULL);
}
ST_STATUS status_motor(ST_MOTOR *m, ST_STATUS s)
{
	if(s != ST_STATUS_ERROR) {
		if(s == ST_STATUS_ON)  
			ioctl(m->device, PPDRV_IOC_PINSET, m->enable);
		if(s == ST_STATUS_OFF) 
			ioctl(m->device, PPDRV_IOC_PINCLEAR, m->enable);
		m->status = s;
	}
        return(m->status);
}
