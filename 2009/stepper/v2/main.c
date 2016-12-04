#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/io.h>
#include <sys/time.h>
#include <time.h>
#include <linux/capability.h>

#include <parapindriver.h>

#include "stepper.h"


#define COIL_EN LP_PIN[6]
#define COIL_AS LP_PIN[2]
#define COIL_AN LP_PIN[3]
#define COIL_BS LP_PIN[4]
#define COIL_BN LP_PIN[5]
#define SENSOR LP_PIN[11]


struct termios stdin_store, stdin_raw;
ST_ERROR errcode;
ST_MOTOR *m;
ST_MODE cal_mode;
char *str_mode[]={"error","WAVE","FULL","HALF"};
int ssto=100; /* Calibration step time in ms */
struct timeval ck_start,ck_finish;
unsigned long elaps;
int sensor;

extern int verbose;
void help();
int get_sens(ST_MOTOR *);
void print_stats(ST_MOTOR *);

void sig_ctrlc(int code)
{
  printf("Ctrl-c caught ... stop motor and exit\n");
  tcsetattr(STDIN_FILENO,TCSANOW,&stdin_store);
  if(m) destroy_motor(m,&errcode);
  exit(1);
}

int main(int argc, char *argv[])
{
  m = NULL;

  if (argc<2) {
    printf("%s /dev/ppdrv1\n",argv[0]); 
    exit(1);
  }

  tcgetattr(STDIN_FILENO,&stdin_store);
  tcgetattr(STDIN_FILENO,&stdin_raw);
  stdin_raw.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&stdin_raw);
  signal(SIGINT, sig_ctrlc);

	/* EM-258. 200 steps full */

  m=create_motor(argv[1],COIL_EN,COIL_AS,COIL_AN,COIL_BS,COIL_BN,200,&errcode);
  if(NULL == m) {
	printf("Failed: %d\n",errcode);
	tcsetattr(STDIN_FILENO,TCSANOW,&stdin_store);
        exit(1);
  }
#if defined __TEST__
  {
  int tst_del = 200;
  double tst_i;
  char tst_ch;
 
#if defined __TEST_CALIBRATE__  
  {
   ioctl(m->device, PPDRV_IOC_PINMODE_IN, SENSOR);
   status_motor(m,ST_STATUS_ON);
   tst_i = 0;
   verbose = 0;
   cal_mode=ST_MODE_WAVE;
   help();
   while(1) {
	tst_ch=getchar();
    if(tst_ch=='d') verbose++;
    if(tst_ch=='D') verbose=0;
   	if(tst_ch=='h') help();
  	if(tst_ch=='x') {
 		tst_i += 1;
		move_motor(m, cal_mode, 1, 0, tst_del);
   	}
	if(tst_ch=='z') {
		tst_i -= 1;
		move_motor(m, cal_mode, -1, 0, tst_del);
   	}
	if(tst_ch=='p') {
		tst_i -= 1;
 		sensor=get_sens(m);
		printf("\nCalibrate clockwise position on start %d",sensor);
		while(get_sens(m)==sensor) {
			putchar('*');
			fflush(stdout);
			move_motor(m, cal_mode, 1, 0, ssto);
		}
		printf(" Reset statistics");
		reset_stats(m);
		printf("\nComplete rotation clockwise %d ms/step",ssto);
		gettimeofday(&ck_start,NULL);
		do{
			putchar('.');
			fflush(stdout);
			move_motor(m, cal_mode, 1, 0, ssto);
		} while(get_sens(m)!=sensor);
		
 		while(get_sens(m)==sensor) {
			putchar('-');
			fflush(stdout);
			move_motor(m, cal_mode, 1, 0, ssto);
		}
		gettimeofday(&ck_finish,NULL);
		elaps=(ck_finish.tv_sec * 1000000 + ck_finish.tv_usec) - (ck_start.tv_sec * 1000000 + ck_start.tv_usec);
		printf("\nElaps: %ld ms\n",elaps/1000);
		print_stats(m);
	}
    if(tst_ch=='m')  {
		if(cal_mode==ST_MODE_WAVE) cal_mode=ST_MODE_FULL;
		else if(cal_mode==ST_MODE_FULL) cal_mode=ST_MODE_HALF;
		else if(cal_mode==ST_MODE_HALF) cal_mode=ST_MODE_WAVE;
		print_stats(m);
	}
    if(tst_ch=='t') {
		ssto++;
		printf("\r%d    ",ssto);
	}
    if(tst_ch=='T') {
		ssto--;
		if(ssto < 0) ssto=0;
		printf("\r%d    ",ssto);
	}
	if(tst_ch=='s') print_stats(m);
	if(tst_ch=='S') reset_stats(m);
	if(tst_ch=='q') break;
  }
  /* printf("Steps = %.2f Degree/step=%.2f\n", tst_i, (double) (((double) tst_i)/360.0)); */

  } 
#endif /* __TEST_CALIBRATE__ */

#if defined __TEST_OFFLINE__  
  {
  tst_del = 0;
  status_motor(m,ST_STATUS_OFF);
  printf("move_motor(m, ST_MODE_FULL, 10, 0, tst_del)\n");
  move_motor(m, ST_MODE_FULL, 10, 0, tst_del);
  printf("move_motor(m, ST_MODE_HALF, 10, 0, tst_del)\n");
  move_motor(m, ST_MODE_HALF, 10, 0, tst_del);
  printf("move_motor(m, ST_MODE_FULL, -10, 0, tst_del)\n");
  move_motor(m, ST_MODE_FULL, -10, 0, tst_del);
  printf("move_motor(m, ST_MODE_HALF, -10, 0, tst_del)\n");
  move_motor(m, ST_MODE_HALF, -10, 0, tst_del);
  printf("move_motor(m, ST_MODE_FULL, 0, 90.0, tst_del)\n");
  move_motor(m, ST_MODE_FULL, 0, 90.0, tst_del);
  printf("move_motor(m, ST_MODE_HALF, 0, 90.0, tst_del)\n");
  move_motor(m, ST_MODE_HALF, 0, 90.0, tst_del);
  printf("move_motor(m, ST_MODE_FULL, 0, -90.0, tst_del)\n");
  move_motor(m, ST_MODE_FULL, 0, -90.0, tst_del);
  printf("move_motor(m, ST_MODE_HALF, 0, -90.0, tst_del)\n");
  move_motor(m, ST_MODE_HALF, 0, -90.0, tst_del);
  printf("move_motor(m, ST_MODE_FULL, 0, 520.0, tst_del/2)\n");
  move_motor(m, ST_MODE_FULL, 0, 520.0, (tst_del/2));
  printf("move_motor(m, ST_MODE_HALF, 0, -520.0, tst_del/2)\n");
  move_motor(m, ST_MODE_HALF, 0, -520.0, (tst_del/2));
  printf("\n");
  }
#endif /* __TEST_OFFLINE __ */
}
#endif /* __TEST__ */
  printf("destroy_motor\n");
  destroy_motor(m,&errcode);
  tcsetattr(STDIN_FILENO,TCSANOW,&stdin_store); 
  return 0;
}
void help() {
   printf("Complete rotation clockwise\n");
   printf("Make a complete rotation and press q\n");
   printf("[x] clockwise\n[z] anticlockwise\n[q]Quit\n"); 
   printf("[h]help\n[dD] debug/reset debug\n[sS] status view/reset status\n"); 
   printf("[tT] step TO +/-"); 
   printf("\n");
  }
int get_sens(ST_MOTOR *m) {
	return(ioctl(m->device, PPDRV_IOC_PINGET, SENSOR) ? 1 : 0);
}
void print_stats(ST_MOTOR *m) {
		printf("degree=%f steps=%ld rotation=%ld\ntest:sensor=%d mode=%s deb=%d ssto=%d\n",
			m->stats->degree,
			m->stats->steps,
			m->stats->rotation,
			get_sens(m),
			str_mode[(int)cal_mode],
			verbose,
			ssto);
}

