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

/* ppdrv_test.c -- example of how to use the parapindriver kernel driver module
   that wraps around kparapin.  Not useful functionally, since it assumes custom
   hardware, but this shows how to use the parapindriver device interface
   via ioctl's.  */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <parapindriver.h>

#define COIL_0R LP_PIN01
#define COIL_0L LP_PIN02
#define COIL_1R LP_PIN03
#define COIL_1L LP_PIN04


int main(int argc, char *argv[])
{
  int i, value;
  int device;

  /* Get things set up */
  if(argc > 2) 
  device = open("/dev/ppdrv_device1", 0);
  else
  device = open("/dev/ppdrv_device", 0);

  if (device < 0) {
    fprintf(stderr, "device open failed, we're outta here\n");
    exit(-1);
  }

  ioctl(device, PPDRV_IOC_PINMODE_OUT, COIL_0R | COIL_0L | COIL_1R | COIL_1L);

  /* make sure we're in the idle state */
  ioctl(device, PPDRV_IOC_PINSET, COIL_0R | COIL_0L);
  ioctl(device, PPDRV_IOC_PINCLEAR, COIL_1R | COIL_1L);


  /* close the device */
  close(device);

  return 0;
}
