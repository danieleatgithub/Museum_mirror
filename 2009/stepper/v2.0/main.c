#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/io.h>
#include <linux/capability.h>


#include "stepper.h"


#define COIL_EN LP_PIN[6]
#define COIL_AS LP_PIN[2]
#define COIL_AN LP_PIN[3]
#define COIL_BS LP_PIN[4]
#define COIL_BN LP_PIN[5]



struct termios stdin_store, stdin_raw;
ST_ERROR errcode;
ST_MOTOR *m;

extern int verbose;

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

	/* EM-28. 400 steps full */

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
   status_motor(m,ST_STATUS_ON);
   tst_i = 0;
   printf("Complete rotation clockwise\n");
   printf("Make a complete rotation and press q\n");
   printf("[x] clockwise\n[z] anticlockwise\n[q]Rotor is on the marker\n"); 
   while(1) {
	verbose = 5;
	tst_ch=getchar();
   	if(tst_ch=='x') {
 		tst_i += 1;
		move_motor(m, ST_MODE_FULL, 1, 0, tst_del);
   	}
	if(tst_ch=='z') {
		tst_i -= 1;
		move_motor(m, ST_MODE_FULL, -1, 0, tst_del);
   	}
	if(tst_ch=='X') {
		tst_i += 0.5; 
		move_motor(m, ST_MODE_HALF, 1, 0, tst_del);
   	}
	if(tst_ch=='Z') {
		tst_i -= 0.5;
		move_motor(m, ST_MODE_HALF, -1, 0, tst_del);
	}
        if(tst_ch=='q') break;
	printf("STEPS=%.2f\n",tst_i);
  }
  printf("Steps = %.2f Degree/step=%.2f\n", tst_i, (double) (((double) tst_i)/360.0));


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
