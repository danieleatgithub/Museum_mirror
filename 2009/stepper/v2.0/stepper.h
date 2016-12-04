/*
 *
 * Common defines for stepper motor daemon
 *
 * 2009 - alpha 
 *
 */


#ifndef __STEPPER_H__
#define __STEPPER_H__

#include <parapindriver.h>

typedef enum 
{
	ST_MODE_ERROR = 0,
	ST_MODE_FULL,
	ST_MODE_HALF
} ST_MODE;

typedef enum 
{
	ST_STATUS_ERROR = 0,
	ST_STATUS_ON,
	ST_STATUS_OFF,
	ST_STATUS_HOLD
} ST_STATUS;

typedef enum 
{
        ST_ERROR_NOERROR = 0,
        ST_ERROR_GENERIC = -1,
	ST_ERROR_NOMEM = -2,
	ST_ERROR_BUSY = -3
} ST_ERROR;

typedef struct T_ST_STEP 
{
	struct T_ST_STEP *nxt;
	struct T_ST_STEP *prv;
	ST_MODE  type;
	int          number;
        unsigned int coils_set;
        unsigned int coils_clr;
}ST_STEP;

typedef struct T_ST_STATS 
{
	double degree;
	unsigned long steps;
	unsigned long rotation;
}ST_STATS;

typedef struct T_ST_PARAMS 
{
	char 		name[20];
	char 		manufacturer[20];
	unsigned int 	wires;
	unsigned int	d360steps;
	unsigned long   min_usec_delay;
}ST_PARAMS;

typedef struct T_ST_MOTOR 
{
        char 		*devname;
 	int 		device;
	ST_MODE		mode;
	ST_STATUS 	status;
        ST_STEP 	*init;
	ST_STEP		*current;
	unsigned int 	coils;	
	unsigned int 	enable;	
	unsigned int 	d360steps;	
	ST_STATS	*stats;
	ST_PARAMS	*params;
}ST_MOTOR;


typedef struct T_ST_RESULT 
{
 	int 		result;
}ST_RESULT;

#endif

/* Export public function for steps module */
#ifndef __STEPS_C__
extern ST_STEP *create_steps(int,int,int,int,ST_ERROR *);
extern ST_STEP *destroy_steps(ST_STEP *,ST_ERROR *);
#endif
#ifndef __MOTOR_C__
extern ST_MOTOR *create_motor(char *, int,
			int, int,int,int,
			int , ST_ERROR *);

extern ST_MOTOR *destroy_motor(ST_MOTOR *,
			ST_ERROR *);
extern ST_RESULT *move_motor(ST_MOTOR *, ST_MODE, long, double, long);
extern ST_STATUS status_motor(ST_MOTOR *, ST_STATUS);
#endif
