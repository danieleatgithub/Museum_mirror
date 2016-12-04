#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <parapindriver.h>

int main(int argc, char *argv[])
{
  int i, pin, s, del;
  int device;
  float temp;

  if (argc<2 ) {
    printf("%s /dev/ppdrv0 pin\n",argv[0]); 
    exit(1);
  }
  s = 1;
  if ( strstr(argv[0],"on") == NULL ) s=0;
  pin = atoi(argv[2]);

  /* Get things set up */
  device = open(argv[1], 0);

  if (device < 0) {
    fprintf(stderr, "device open failed, we're outta here\n");
    exit(-1);
  }

  ioctl(device, PPDRV_IOC_PINMODE_OUT, LP_PIN[pin]); 

  if(s) ioctl(device, PPDRV_IOC_PINSET, LP_PIN[pin]);
  else ioctl(device, PPDRV_IOC_PINCLEAR, LP_PIN[pin]);


  /* close the device */
  close(device);

  return 0;
}
