#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <linux/capability.h>
/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>



#define EXIT_SUCCESS   0
#define EXIT_FAILURE   1

char at[1000];

int
main(int argc, char *argv[])
{
int opt,i,ii;

char *endptr, *str;
unsigned int port,nbytes,wr;
unsigned char value;
long max,cur;
char *ast;

struct timeval tv,s,e;

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




/* Wait up to five seconds. */
tv.tv_sec = 0;
tv.tv_usec = 1000000;

cur=0;
max=0;

while(1) {
gettimeofday(&s,NULL);
select(0, NULL, NULL, NULL, &tv);
gettimeofday(&e,NULL);
cur=((e.tv_usec - s.tv_usec) - tv.tv_usec);


if( cur > max || cur > 100000) {
 ast=ctime(&e);
 printf("c=%d m=%d %s",cur,max,ast);
 max=cur;
}
}


exit(EXIT_SUCCESS);
}




