#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/io.h>
#include <linux/capability.h>

#include <parapindriver.h>


int main(int argc, char *argv[])
{
  int i;
  int device;
  unsigned int val;

  if (argc<2) {
    printf("%s /dev/ppdrv0\n",argv[0]); 
    exit(1);
  }

ioperm(0x27a,1,CAP_SYS_RAWIO);
  val=inb(0x27a); 
  syslog(LOG_KERN,"ppdrv -------- init ctrlreg 0x%x --------\n",val);
  sleep(1);

  /* Get things set up */
  syslog(LOG_KERN,"ppdrv -------- open device ----------%s\n",argv[1]);
  device = open(argv[1], 0);
  sleep(1);

  if (device < 0) {
    fprintf(stderr, "device open failed, we're outta here\n");
    exit(-1);
  }

  val=inb(0x27a); 
  syslog(LOG_KERN,"ppdrv -------- set out mode - 0x%x --------\n",val);
  ioctl(device, PPDRV_IOC_PINMODE_OUT, 
		(LP_PIN[1] | LP_PIN[14] | LP_PIN[16] | LP_PIN[17]));
  sleep(1);

  val=inb(0x27a); 
  syslog(LOG_KERN,"ppdrv ------   set pin 1 --- 0x%x ----\n",val);
  ioctl(device, PPDRV_IOC_PINSET,   LP_PIN[1]); sleep(1);
  val=inb(0x27a); 
  syslog(LOG_KERN,"ppdrv ------ clear pin 1 ---  0x%x ----\n",val);
  ioctl(device, PPDRV_IOC_PINCLEAR, LP_PIN[1]); sleep(1);
  syslog(LOG_KERN,"ppdrv ------ set   pin 14 -------\n");
  ioctl(device, PPDRV_IOC_PINSET,   LP_PIN[14]); sleep(1);
  syslog(LOG_KERN,"ppdrv ------ clear pin 14 -------\n");
  ioctl(device, PPDRV_IOC_PINCLEAR, LP_PIN[14]); sleep(1);
  syslog(LOG_KERN,"ppdrv ------ set pin 16 -------\n");
  ioctl(device, PPDRV_IOC_PINSET,   LP_PIN[16]); sleep(1);
  syslog(LOG_KERN,"ppdrv ------ set clear 16 -------\n");
  ioctl(device, PPDRV_IOC_PINCLEAR, LP_PIN[16]); sleep(1);
  syslog(LOG_KERN,"ppdrv ------ set pin 17 -------\n");
  ioctl(device, PPDRV_IOC_PINSET,   LP_PIN[17]); sleep(1);
  syslog(LOG_KERN,"ppdrv ------ set clear 17 -------\n");
  ioctl(device, PPDRV_IOC_PINCLEAR, LP_PIN[17]); sleep(1);


  /* close the device */
  syslog(LOG_KERN,"ppdrv ------ close device -------\n");
  close(device);

  return 0;
}
