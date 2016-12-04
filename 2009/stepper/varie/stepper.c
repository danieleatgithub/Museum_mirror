#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/io.h>
#include <linux/capability.h>
#include <termios.h>

#include <parapindriver.h>

#define COIL_EN LP_PIN[6]
#define COIL_AP LP_PIN[2]
#define COIL_AM LP_PIN[3]
#define COIL_BP LP_PIN[4]
#define COIL_BM LP_PIN[5]

#define PINCLR PPDRV_IOC_PINCLEAR
#define PINSET PPDRV_IOC_PINSET

int device = 0; /* parallel port fd */


int main(int argc, char *argv[])
{
  int i;
  int device;
  char mode;
  char ch;
  unsigned long delay;
  unsigned long loop;

  if (argc<4) {
    printf("%s /dev/ppdrv0 delay loop\n",argv[0]); 
    exit(1);
  }

  device = open(argv[1], 0);
  delay = atol(argv[2]);
  loop = atol(argv[3]);



  if (device <= 0) {
    fprintf(stderr, "device %s open failed\n",argv[0]);
    exit(-1); 
  }

  ioctl(device, PPDRV_IOC_PINMODE_OUT, 
		(COIL_EN | COIL_AP | COIL_AM | COIL_BP | COIL_BM));

  ioctl(device, PINCLR, COIL_EN );
  ioctl(device, PINCLR, (COIL_AP | COIL_AM | COIL_BP | COIL_BM));
  ioctl(device, PINSET, COIL_EN );

  printf("Ready to connect coils [s] for single coil steps\n");
  mode=getchar();
  printf("Ok go %c...\n",mode);


/*
#define COIL_AP LP_PIN[2]
#define COIL_AM LP_PIN[3]
#define COIL_BP LP_PIN[4]
#define COIL_BM LP_PIN[5]
*/
  for(i=0;i<loop;i++) {
  /* step 1  coil a on */
  ioctl(device, PINCLR, COIL_BM); 
  ioctl(device, PINSET, COIL_AP); 
  if (mode == 's') {
      printf("Coil a on forward pin 2 High .. press key ...\n");
      getchar();
  }  else {
      usleep(delay);
  } 

  /* step 2  coil b on */
  ioctl(device, PINCLR, COIL_AP); 
  ioctl(device, PINSET, COIL_BP); 
  if (mode == 's') {
      printf("Coil b on forward pin 4 High .. press key ...\n");
      getchar();
  }  else {
      usleep(delay);
  } 

  /* step 3  coil a on reverse */
  ioctl(device, PINCLR, COIL_BP); 
  ioctl(device, PINSET, COIL_AM); 
  if (mode == 's') { 
      printf("Coil a on reverse pin 3 High .. press key ...\n");
      getchar();
  } else {
      usleep(delay);
  } 

  /* step 4  coil b on reverse */
  ioctl(device, PINCLR, COIL_AM); 
  ioctl(device, PINSET, COIL_BM); 
  if (mode == 's') {
      printf("Coil b on reverse pin 5 High .. press key ...\n");
      getchar();
  } else {
	  printf("f",i);
          usleep(delay);
  }
  }
  ioctl(device, PINCLR, COIL_EN );
  ioctl(device, PINCLR, (COIL_AP | COIL_AM | COIL_BP | COIL_BM));


  /* close the device */
  close(device);

  return 0;
}
