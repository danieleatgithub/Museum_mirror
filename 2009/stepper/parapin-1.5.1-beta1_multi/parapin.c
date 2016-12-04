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
 

#define DEBUG
/*
 * parapin
 *
 * $Id: parapin.c,v 1.20 2004/11/30 21:23:55 ahooton Exp $
 *
 */

/* Includes appropriate for any platform (currently only Linux) */
#include "parapin.h"

/* prototypes for functions defined later in the file */
static void pin_init_internal(int dev);

/* Platform-specific includes */
#include "parapin-linux.h"


#ifdef MODULE
#include <linux/module.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
/* Module documentation for those who find it */
MODULE_LICENSE("LGPL");
MODULE_AUTHOR("Al Hooton <al@hootons.org>");
MODULE_DESCRIPTION("parapin library for programming pins on a parallel port under Linux (http://parapin.sourceforge.net/)");
#endif /* LINUX_VERSION_CODE */

#endif /* MODULE */


/* most recently read or written values of the three parallel port I/O
 * registers.  kept in TRUE logic; i.e. the actual high/low electrical
 * state on the pins, NOT the values of register bits. */
static int lp_register[MAX_PARPIN][3];

/* masks of pins that we currently allow input and output on */
static int lp_input_pins[MAX_PARPIN];
static int lp_output_pins[MAX_PARPIN];



/************************* Basic Utilities *****************************/


#ifdef DEBUG
char *bin_to_char(int num)
{
  int i;
  static char buf[9];

  buf[8] = '\0';

  for (i = 0; i < 8; i++) {
    if (num & (1 << i))
      buf[7-i] = '1';
    else
      buf[7-i] = '0';
  }

  return buf;
      
}
#endif

/* read a byte from an I/O port (base + regnum), correct for inverted
 * logic on some bits, and store in the lp_register variable.  Return
 * the value read.  */
static inline int read_register(int dev,int regnum)
{
#ifdef DEBUG
  int result,a,b;
  

  a=INB(dev,regnum);
  b=(a ^ lp_invert_masks[regnum]);
  result = lp_register[dev][regnum] = b;
 
  /* result = (lp_register[dev][regnum] = (INB(dev,regnum) ^ lp_invert_masks[regnum]));
  */
  printf("rd-a:rn=%d reg:0x%x raw=%s 0x%x\n", regnum, (lp_base[dev] + regnum), bin_to_char(a), a);
  printf("rd-b:rn=%d reg:0x%x xor=%s 0x%x\n", regnum, (lp_base[dev] + regnum), bin_to_char(result), result);

  return result;
#else
  return lp_register[dev][regnum] = (INB(dev,regnum) ^ lp_invert_masks[regnum]);
#endif
}


/* store the written value in the lp_register variable, correct for
 * inverted logic on some bits, and write a byte to an I/O port (base
 * + regnum) */
static inline void write_register(int dev,int value, int regnum) 
{
  int a;
  a= (value ^ lp_invert_masks[regnum]);

#ifdef DEBUG
  printf("wr-a reg:0x%x raw=%s 0x%x\n", (lp_base[dev] + regnum), bin_to_char(a), a);
#endif
  lp_register[dev][regnum] = value;
  OUTB(dev,a, regnum);
}


/********************* Initialization *************************************/


/* Initialization that kernel-mode and user-mode have in common */
static void pin_init_internal(int dev)
{
  /* i've redesigned how the library is initialized with a very
   * minimalist approach: instead of trying to figure out what values
   * are "safe", we just avoid touching the parallel port registers
   * *at all* until the user tells us to do so.  accordingly, all
   * switchable pins are in neither input nor output mode to start
   * with.  this enforces the fact that outputs/inputs can not be used
   * until a pin is explicitly configured as either an input or output
   * pin.
   *
   * note that it is always legal to read from and write to the
   * "pseudo pins" of INPUT_MODE and IRQ_MODE because these are
   * actually control bits.
   */

  lp_output_pins[dev] = LP_INPUT_MODE | LP_IRQ_MODE;
  lp_input_pins[dev] = LP_ALWAYS_INPUT_PINS | LP_INPUT_MODE | LP_IRQ_MODE;
}



/******************** Pin Setting and Clearing **************************/


/* set output pins in the data register.  we'll do read-before-write,
 * just to be safe.*/
static inline void set_datareg(int dev, int pins)
{
  write_register(dev,read_register(dev,0) | pins, 0);
}

/* clear output pins in the data register.  we'll do
 * read-before-write, just to be safe. */
static inline void clear_datareg(int dev, int pins)
{
  write_register(dev,(read_register(dev,0) & (~pins)), 0);
}

/* set output pins in the control register */
static inline void set_controlreg(int dev,int pins)
{
  /* the control register requires:
   *    - switchable pins that are currently being used as inputs must be 1
   *    - all other pins may be either set or cleared
   */

  /* read existing register into lp_register[2] */
  read_register(dev,2);

  /* set the requested bits to 1, leaving the others unchanged */
  lp_register[dev][2] |= pins;

  /* set all inputs to one (they may have been read as 0's!) 1 */
  lp_register[dev][2] |= (0x0f & ((lp_input_pins[dev] & LP_SWITCHABLE_PINS) >> 16));

  /* write it back */
  write_register(dev,lp_register[dev][2], 2);
}


/* clear output pins in the control register */
static inline void clear_controlreg(int dev,int pins)
{
  /* the control register requires:
   *    - switchable pins that are currently being used as inputs must be 1
   *    - all other pins may be either set or cleared
   */

  /* read existing register into lp_register[2] */
  read_register(dev,2);

  /* clear the requested pins, leaving others unchanged */
  lp_register[dev][2] &= (~pins);

  /* set all inputs to one (they may have been read as 0's!) 1 */
  lp_register[dev][2] |= (0x0f & ((lp_input_pins[dev] & LP_SWITCHABLE_PINS) >> 16));

  /* write it back */
  write_register(dev,lp_register[dev][2], 2);
}



/*
 * externally visible function: set_pin(int pins)
 *
 * this can be used to set any number of pins without disturbing other pins.
 *
 * example: set_pin(LP_PIN02 | LP_PIN05 | LP_PIN07)
 */
void set_pin(int dev,int pins)
{
  /* make sure the user is only trying to set an output pin */
  pins &= lp_output_pins[dev];

/* REMOVE */
   printf("set_pin dev=%d pins=0x%x lp_output_pins=0x%x\n",dev,pins,lp_output_pins[dev]); 

  /* is user trying to set pins high that are data-register controlled? */
  if (pins & LPBASE0_MASK)
    set_datareg(dev, pins & LPBASE0_MASK);

  /* is user trying to set pins high that are control-register controlled? */
  if (pins & LPBASE2_MASK)
    set_controlreg(dev, (pins & LPBASE2_MASK) >> 16);
}

/*
 * externally visible function: clear_pin(int pins)
 *
 * same interface as set_pin, except that it clears instead
 */
void clear_pin(int dev,int pins)
{
  /* make sure the user is only trying to set an output pin */
  pins &= lp_output_pins[dev];

  /* is user trying to clear pins that are data-register controlled? */
  if (pins & LPBASE0_MASK)
    clear_datareg(dev,pins & LPBASE0_MASK);

  /* is user trying to clear pins that are control-register controlled? */
  if (pins & LPBASE2_MASK)
    clear_controlreg(dev,(pins & LPBASE2_MASK) >> 16);
}


/*
 * a different interface to set_pin and clear_pin;
 *
 * change_pin(X, LP_SET) is the same as set_pin(X);
 * change_pin(X, LP_CLEAR) is the same as clear_pin(X);
 */
void change_pin(int dev,int pins, int mode)
{
  if (mode == LP_SET)
    set_pin(dev,pins);
  else if (mode == LP_CLEAR)
    clear_pin(dev,pins);
}


/* pin_is_set: takes any number of pins to check, and returns a
 * corresponding bitvector with 1's set on pins that are electrically
 * high. */
int pin_is_set(int dev,int pins)
{
  int result = 0;

  /* make sure the user is only trying to read an output pin */
  pins &= lp_input_pins[dev];

  if (pins & LPBASE0_MASK) {
    result |= (read_register(dev,0) & (pins & LPBASE0_MASK));
  }

  if (pins & LPBASE1_MASK) {
    result |= ((read_register(dev,1) & ((pins & LPBASE1_MASK) >> 8)) << 8);
  }

  if (pins & LPBASE2_MASK) {
    result |= ((read_register(dev,2) & ((pins & LPBASE2_MASK) >> 16)) << 16);
  }

  return result;
}



/************************* Direction Changing *****************************/

/* change the data pins (pins 2-9) to input mode */
static void dataline_input_mode(int dev)
{
#ifdef DEBUG
  printf("setting input mode on data pins\n");
#endif
  lp_input_pins[dev] |= LP_DATA_PINS;
  lp_output_pins[dev] &= (~LP_DATA_PINS);
  set_pin(dev,LP_INPUT_MODE);
}


static void dataline_output_mode(int dev)
{
#ifdef DEBUG
  printf("setting output mode on data pins\n");
#endif
  lp_input_pins[dev] &= (~LP_DATA_PINS);
  lp_output_pins[dev] |= LP_DATA_PINS;
  clear_pin(dev,LP_INPUT_MODE);
}


static void controlreg_input_mode(int dev,int pins)
{
#ifdef DEBUG
  printf("setting control-reg input mode\n");
#endif
  lp_input_pins[dev] |= pins;
  lp_output_pins[dev] &= (~pins);
  set_controlreg(dev,0);
}

static void controlreg_output_mode(int dev,int pins)
{
#ifdef DEBUG
  printf("setting control-reg output mode\n");
#endif
  lp_input_pins[dev] &= (~pins);
  lp_output_pins[dev] |= pins;
  set_controlreg(dev,0);
}


/* user-visible function to change pins to input mode */
void pin_input_mode(int dev,int pins)
{
  if (pins & LP_DATA_PINS)
    dataline_input_mode(dev);
  if (pins & LP_SWITCHABLE_PINS)
    controlreg_input_mode(dev,pins & LP_SWITCHABLE_PINS);
}

/* user-visible function to change pins to output mode */
void pin_output_mode(int dev,int pins)
{
  if (pins & LP_DATA_PINS)
    dataline_output_mode(dev);
  if (pins & LP_SWITCHABLE_PINS)
    controlreg_output_mode(dev,pins & LP_SWITCHABLE_PINS);
}

/* another interface to pin_input_mode and pin_output_mode */
void pin_mode(int dev,int pins, int mode)
{
  if (mode == LP_INPUT)
    pin_input_mode(dev,pins);
  if (mode == LP_OUTPUT)
    pin_output_mode(dev,pins);
}

