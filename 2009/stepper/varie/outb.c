#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/io.h>
#include <linux/capability.h>

#define EXIT_SUCCESS   0
#define EXIT_FAILURE   1

#define MAX_PORT 0xffff
#define MAX_VALUE 0xff

static volatile unsigned char ch_value;

int
main(int argc, char *argv[])
{
int ii,opt;

char *endptr, *str;
unsigned int port,value,rdflag;

port=0;
value=0;
rdflag=0;

while ((opt = getopt(argc, argv, "r")) != -1) {
switch (opt) {
    case 'r':
	rdflag=1;
	break;
    default: /* '?' */
	fprintf(stderr, "Usage: %s [-r] port value\n",
		argv[0]);
	exit(EXIT_FAILURE);
    }
}


if ((argc - optind) < 2) {
    fprintf(stderr, "Usage: %s [-r] port value\n",
		argv[0]);
    exit(EXIT_FAILURE);
}



str=argv[(optind)];
port=strtol(str,&endptr,0);
if ((errno == ERANGE && (port == LONG_MAX || port == LONG_MIN))
   || (errno != 0 && port == 0)
   || (port > MAX_PORT)
   || (endptr == str)) {
	fprintf(stderr,"Invalid port %s range 0x0 0x%x\n",
		argv[(optind+1)],MAX_PORT);
	exit(EXIT_FAILURE);
}

str=argv[(optind+1)];
if  (strlen(str) > 2 && str[1] == 'b') 
	value=strtol(&str[2],&endptr,2);
else 
	value=strtol(str,&endptr,0);
if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN))
   || (errno != 0 && value == 0)
   || (value > MAX_VALUE)
   || (endptr == str)) {
	fprintf(stderr,"Invalid value %s range 0x0 0x%x\n",
		argv[(optind+2)],MAX_VALUE);
	exit(EXIT_FAILURE);
}

ch_value = (unsigned char) value;

ioperm(port,1,CAP_SYS_RAWIO);
outb(ch_value,port); 

if(rdflag == 0) {
	ch_value=0;
	ch_value=inb(port); 
	printf("0x%x 0x%02x %03d ",(port),ch_value,ch_value);
	   for(ii=0x80;ii>0;ii=(ii>>1)) 
	      (ch_value & ii) ? printf("1") : printf("0");
	   printf("\n");
}
exit(EXIT_SUCCESS);
}





