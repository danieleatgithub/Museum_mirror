#define __STEPS_C__
#include <stdlib.h>
#include "stepper.h"

#define MAX_STEPS 8


/* Create a steps descriptor ring for HALF step mode 
 * use Odd only for the FULL step mode.
 * Applicable only for bipolar motors with four wires
 * coil_as,an - pins bitmap south and north connected to coil a
 * coil_bs,bn - pins bitmap south and north connected to coil b 
 * err = Library code error
 * RETURN pointer to first step
 * ERROR  NULL for not enough memory
 */
ST_STEP *create_steps(unsigned int coil_as, unsigned int coil_an,
                      unsigned int coil_bs, unsigned int coil_bn,
			ST_ERROR *err)
{
  int i,n;
  ST_STEP *p[MAX_STEPS];

	*err=ST_ERROR_NOERROR;
        /* Allocate 4 steps for FULL mode and 4 steps */
	/* for the HALF steps mode		      */
	for(i=0;i<MAX_STEPS;i++) {
		p[i] = malloc(sizeof(ST_STEP)*MAX_STEPS);
		if (NULL == p[i]) {
			for(n=i;n>=0;n--) if(p[n]) free(p[n]);
			*err=ST_ERROR_NOMEM;
			return(NULL);
		}
	}

	/* Initialize double linked list and step type */
	for(i=0;i<MAX_STEPS;i++) {
		if(0 == i) p[0]->prv = p[7];
		else       p[i]->prv = p[i-1];	
		if(i == (MAX_STEPS-1)) p[i]->nxt = p[0];
		else     	       p[i]->nxt = p[i+1];	
		if(i%2) p[i]->type = ST_MODE_HALF;
		else    p[i]->type = ST_MODE_FULL;
		p[i]->number = i;
	}

	/* Initialize coils for FULL and HALF mode */
	/* Odd is FULL steps mode 		   */
	/* Even is HALF steps mode		   */
	p[0]->coils = coil_as;
	p[1]->coils = coil_as | coil_bs;
	p[2]->coils = coil_bs;
	p[3]->coils = coil_bs | coil_an;
	p[4]->coils = coil_an;
	p[5]->coils = coil_an | coil_bn;
	p[6]->coils = coil_bn;
	p[7]->coils = coil_bn | coil_as;

	return(p[0]);
	
}

ST_STEP *destroy_steps(ST_STEP *p,ST_ERROR *err)
{
	ST_STEP *a,*b;

	a = p;
	a->prv->nxt =NULL;
	*err=ST_ERROR_NOERROR;
	while(a->nxt) {
		b = a->nxt;
		free((void *)a);
		a = b;
	}
	free((void *)a);
	return(NULL);
}

