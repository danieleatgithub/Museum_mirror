#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <linux/capability.h>

#define EXIT_SUCCESS   0
#define EXIT_FAILURE   1


int
main(int argc, char *argv[])
{
int opt,i,ii;

char *endptr, *str;
unsigned int port,nbytes,wr;
unsigned char value;

wr=0;
port=0;
nbytes=1;
value=0;

while ((opt = getopt(argc, argv, "n:w:")) != -1) {
switch (opt) {
    case 'n':
	nbytes=atoi(optarg);
	break;
    case 'w':
	str=optarg;
	value = strtol(str,&endptr,0);
	if (nbytes != 1 ) {
		fprintf(stderr, "write mode only for one byte\n",
                argv[0]);
        exit(EXIT_FAILURE);
	}
	wr = 1;
	break;
    default: /* '?' */
	fprintf(stderr, "Usage: %s [-w value] [-n nbytes] ioport\n",
		argv[0]);
	exit(EXIT_FAILURE);
    }
}


if (optind >= argc) {
    fprintf(stderr, "ioport missed\n");
    exit(EXIT_FAILURE);
}

str=argv[optind];
port=strtol(str,&endptr,0);


ioperm(port,nbytes,CAP_SYS_RAWIO);

if(wr==1) {
	outb(value,port);
}
for(i=0;i<nbytes;i++) {
   value=inb(port+i); 
   printf("0x%x 0x%x %d ",(port+i),value,value);
   for(ii=0x80;ii>0;ii=(ii>>1)) 
      (value & ii) ? printf("1") : printf("0");
   printf("\n");
}


/* Other code omitted */

exit(EXIT_SUCCESS);
}





