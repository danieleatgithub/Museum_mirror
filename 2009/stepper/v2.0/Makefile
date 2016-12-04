
default: mot

clean: 
	rm mot

mot: main.c motor.c steps.c stepper.h
	cc -g -Wall --pedantic -D__TEST__ -D__TEST_CALIBRATE__ -o mot  main.c motor.c steps.c stepper.h
