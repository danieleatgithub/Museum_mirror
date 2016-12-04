#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <linux/capability.h>

#define EXIT_SUCCESS   0
#define EXIT_FAILURE   1

#define MAX_PORT 0xffff

int
main(int argc, char *argv[])
{
int ii;

char *endptr, *str;
unsigned int port;
unsigned char value;

port=0;
value=0;

if(argc != 2) {
	fprintf(stderr, "Usage: %s port\n",
		argv[0]);
	exit(EXIT_FAILURE);
}


str=argv[1];
port=strtol(str,&endptr,0);

/* Check for various possible errors */

if ((errno == ERANGE && (port == LONG_MAX || port == LONG_MIN))
   || (errno != 0 && port == 0)
   || (port > MAX_PORT)
   || (endptr == str)) {
	fprintf(stderr,"Invalid port value %s range 0x0 0x%x\n",
		argv[1],MAX_PORT);
	exit(EXIT_FAILURE);
}


ioperm(port,1,CAP_SYS_RAWIO);
value=inb(port); 
printf("0x%x 0x%x %d ",(port),value,value);
   for(ii=0x80;ii>0;ii=(ii>>1)) 
      (value & ii) ? printf("1") : printf("0");
   printf("\n");

exit(EXIT_SUCCESS);
}





