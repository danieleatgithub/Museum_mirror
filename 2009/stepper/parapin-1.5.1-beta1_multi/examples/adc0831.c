/*  This file is part of the package "parapin".

    The parapin package is free software; you can redistribute it
    and/or modify it under the terms of the GNU Library General Public
    License (LGPL) as published by the Free Software Foundation.

    The parapin package is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with parapin; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA


    For futher information on the parapin package, please refer to the
    project information hosted on Sourceforge --

    http://sourceforge.net/projects/parapin/

*/
 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "parapin.h"


#define VCC LP_PIN02
#define CS  LP_PIN03
#define CLK LP_PIN04
#define DBG LP_PIN05

#define D0  LP_PIN10


#define TPD0    2500
#define TSETUP  250

#define NUM_SAMPLES  200

int numdev = 1;

void inline clock(int dev)
{
  set_pin(dev,CLK);
  clear_pin(dev,CLK);
}



void terminate(int signo)
{
  puts("Shutting down...");
  clear_pin(numdev,VCC | CS | CLK | DBG);
  exit(0);
}


int acquire(int dev)
{
  int sample, i, total, iterations, wait;

  iterations = NUM_SAMPLES;
  total = 0;

  while (iterations--) {

    clear_pin(dev,CS); /* pull CS low */
    wait = TSETUP;
    while (wait--); /* set-up time */
    clock(dev); /* tell chip to acquire */

    sample = 0;
    for (i = 0; i < 8; i++) {
      clock(dev);
      wait = TPD0;
      while (wait--); /* wait for output to stabilize */
      sample <<= 1;
      sample |= (pin_is_set(dev,D0) == D0);
    }

    set_pin(dev,CS);

    total += sample;
    /* delay before next sample */
    wait = 7000;
    while (wait--);
  }

  return total/NUM_SAMPLES;
}


int main(int argc, char *argv[])
{


  signal(SIGINT, terminate);
  signal(SIGTERM, terminate);
  signal(SIGHUP, terminate);

  pin_init_user(numdev,LPT1);

  set_pin(numdev,VCC | CS);

  sleep(1);

  if (argc != 1) {
    for (;;) {
      set_pin(numdev,DBG);
      acquire(numdev);
      clear_pin(numdev,DBG);
      acquire(numdev);
    }
  } else {
    for (;;) {
      printf("Got sample: %d\n", acquire(numdev));
      sleep(1);
    }
  }

  return 0;
}
