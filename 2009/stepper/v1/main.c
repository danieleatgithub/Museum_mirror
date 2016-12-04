#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/io.h>
#include <linux/capability.h>


#include "stepper.h"


#define COIL_EN LP_PIN[6]
#define COIL_AS LP_PIN[2]
#define COIL_AN LP_PIN[3]
#define COIL_BS LP_PIN[4]
#define COIL_BN LP_PIN[5]

ST_ERROR errcode;

int main(int argc, char *argv[])
{

ST_MOTOR *m;

  if (argc<2) {
    printf("%s /dev/ppdrv1\n",argv[0]); 
    exit(1);
  }

  m=create_motor(argv[1],COIL_EN,COIL_AS,COIL_AN,COIL_BS,COIL_BN,0,&errcode);
  if(NULL == m) {
	printf("Failed: %d\n",errcode);
        exit(1);
  }
#ifdef __TEST__
  {
  int test_del = 200;
  printf("move_motor(m, ST_MODE_FULL, 10, 0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_FULL, 10, 0, test_del);
  printf("move_motor(m, ST_MODE_HALF, 10, 0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_HALF, 10, 0, test_del);
  printf("move_motor(m, ST_MODE_FULL, -10, 0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_FULL, -10, 0, test_del);
  printf("move_motor(m, ST_MODE_HALF, -10, 0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_HALF, -10, 0, test_del);
  printf("move_motor(m, ST_MODE_FULL, 0, 90.0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_FULL, 0, 90.0, test_del);
  printf("move_motor(m, ST_MODE_HALF, 0, 90.0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_HALF, 0, 90.0, test_del);
  printf("move_motor(m, ST_MODE_FULL, 0, -90.0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_FULL, 0, -90.0, test_del);
  printf("move_motor(m, ST_MODE_HALF, 0, -90.0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_HALF, 0, -90.0, test_del);
  printf("move_motor(m, ST_MODE_FULL, 0, 520.0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_FULL, 0, 520.0, test_del);
  printf("move_motor(m, ST_MODE_HALF, 0, -520.0, test_del)\n");
  sleep(2);
  move_motor(m, ST_MODE_HALF, 0, -520.0, test_del);
  printf("\n");
  }
#endif

  printf("destroy_motor\n");
  
  destroy_motor(m,&errcode);
  return 0;
}
