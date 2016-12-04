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
  int i,o,n;
  int device;
  char *x;

  x=malloc(1024);
  o = open("/tmp/meminfo", O_CREAT);
  for(n=0;n<4;n++) {
  	device = open("/proc/meminfo", O_RDONLY);
	
	  i=read(device,x,0);
	  write(o,x,i);
	  sleep(1);
  	close(device);
  }
  close(o);

  return 0;
}
