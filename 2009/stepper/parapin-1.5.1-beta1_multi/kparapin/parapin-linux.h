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
    project information hosted on Sourceforge:
    
    http://sourceforge.net/projects/parapin/


    $Id: parapin-linux.h,v 1.17 2007/12/16 17:38:17 ahooton Exp $

*/
 
#define MAX_PARPIN 2

/*
 * System-specific include files for Linux
 */


/* Enable the use of KERNEL_VERSION(). */
#include <linux/version.h>

/* Warn about 2.4 support being deprecated and vanishing in the next release */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#warning Parapin support for kernels older than 2.6.0 is deprecated and will be removed in the near future.  If you must use older kernels please plan to stay on old versions of parapin.  Seriously consider migrating to 2.6.x kernels.
#endif

/* ioport.h is needed for both userspace and kernel/module personalities,
   but only for kernels before 2.6 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#include <linux/ioport.h>
#endif

/* Stuff needed only when building for kernel contexts. */
#ifdef __KERNEL__

/* The Makefile determined if config.h exists or not, act accordingly */
#ifdef CONFIG_H
//#include <linux/config.h>
#endif

#include <linux/kernel.h>

/* module.h is needed if this will be a kernel modules as opposed to
   being linked-in to the kernel. */
#ifdef MODULE
#include <linux/module.h>
#endif /* MODULE */

#include <linux/stddef.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <linux/delay.h>

#include <linux/parport.h>
#include <linux/parport_pc.h>
#include <linux/interrupt.h>

#define printf printk


/* parallel port we found and device we registered */
struct parport *parapin_port[MAX_PARPIN] = { NULL, NULL };
struct pardevice *parapin_dev[MAX_PARPIN] = { NULL, NULL };

/* was the system configured to use the interrupt before we got here? */
static int old_irq_mode[MAX_PARPIN] = { 0,0 };
static int have_irq_handler[MAX_PARPIN] = { 0,0 };

#else /* __KERNEL__ */

/* Includes needed when building as the userspace personality. */
#include <stdio.h>
#include <sys/io.h>

#endif /* __KERNEL__ */


/***************** Linux-Specific inb() and outb() *************************/

/* base address of parallel port I/O */
static int lp_base[MAX_PARPIN];

#define INB(dev_number,register_number) inb(lp_base[dev_number] + register_number)
#define OUTB(dev_number,value, register_number) outb(value, lp_base[dev_number] + register_number)

/**************** Linux-specific Initialization Functions *******************/


#ifdef __KERNEL__

/* kernel-mode parallel port initialization.  the 'lpt' argument is
 * the LP number of the port that you want.  this code will
 * EXCLUSIVELY claim the parallel port; i.e., so that other devices
 * connected to the same parallel port will not be able to use it
 * until you call the corresponding pin_release().  */

int pin_init_kernel(int lpt, void (*irq_func)(int, void *, struct pt_regs *))
{

  /* Check if device is free */
  if (parapin_port[lpt] != NULL) {
	 printk("parapin: init failed, lp%d is busy\n", lpt);
	return -EBUSY;
  } 

  /* Get the enumeration number for this port */
  parapin_port[lpt] = parport_find_number(lpt);


  if (parapin_port[lpt] == NULL) {
    printk("parapin: init failed, lp%d not found\n", lpt);
    return -ENODEV;
  }


  /* NOTE: For a brief time sometime in the middle of the 2.6.x kernel
     series, the definition of parport_register_device() was changed
     briefly such that the 5th argument (the irq handler) did not have
     the "struct pt_regs() *" argument explicitly declared, which was
     an error.  It appears that at least one Debian distro went out to
     the world with this change in place.  In this case gcc will emit a
     warning about incompatible arguments being passed, but everything will
     work correctly.  If you get this warning on the 5th argument in the
     following call, and it bothers you, take a look at your
     include/linux/parport.h kernel header file to see if it has the
     incorrect function prototype for parport_register_device().   */

  /* REMOVE */
  {
  int val0;
  val0=inb(0x27a);
  printk("ctrl before parport_register_device 0x%x\n",val0);
  }
  /* Register the device on the port for exclusive access */
  parapin_dev[lpt] = parport_register_device(parapin_port[lpt],
					"parapin", /* name for debugging */
					NULL, /* preemption callback */
					NULL, /* wakeup callback */
					irq_func, /* interrupt callback */
					PARPORT_DEV_EXCL, /* flags */
					(void *)NULL); /* user data */

  /* REMOVE */
  {
  int val1;
  val1=inb(0x27a);
  printk("ctrl after parport_register_device 0x%x\n",val1);
  }
  if (parapin_dev[lpt] == NULL) {
    printk("parapin: init failed, lp%d not found\n", lpt);
    parapin_port[lpt] = NULL; 
    return -ENODEV;
  }

  /* ok - all systems go.  claim the parallel port. */
  parport_claim(parapin_dev[lpt]);
  /* REMOVE */
  {
  int val3;
  val3=inb(0x27a);
  printk("ctrl after parport_claim 0x%x\n",val3);
  }

  /* remember the LP base of our parallel port */
  lp_base[lpt] = parapin_port[lpt]->base;

  /* put us into bidir mode if we have an ECR */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
  if (parapin_port[lpt]->modes & PARPORT_MODE_PCECR)
    parport_pc_write_econtrol(parapin_port[lpt], 0x20);
#else
  {
    struct parport_pc_private *priv = parapin_port[lpt]->private_data;
    if (priv->ecr) {
      printk("parapin: ecr supported out x20\n"); /* REMOVE */
      outb(0x20, ECONTROL(parapin_port[lpt]));
    }
  }
#endif

  /* initialize the state of the registers */
  pin_init_internal(lpt);
  /* REMOVE */
  {
  int val4;
  val4=inb(0x27a);
  printk("ctrl after pin_init_internal 0x%x\n",val4);
  }

  /* remember the current state of the interrupt enable flag */
  old_irq_mode[lpt] = pin_is_set(lpt,LP_IRQ_MODE);
  /* REMOVE */
  {
  int val5;
  val5=inb(0x27a);
  printk("ctrl after pin_is_set 0x%x\n",val5);
  }
  have_irq_handler[lpt] = (irq_func != NULL);

  /* disable interrupts */
  pin_disable_irq(lpt);
  /* REMOVE */
  {
  int val6;
  val6=inb(0x27a);
  printk("ctrl after pin_disable_irq 0x%x\n",val6);
  }

  /* tell the user what's happening */
  printk("parapin: claiming %s at 0x%lx, irq %d\n", parapin_port[lpt]->name,
         parapin_port[lpt]->base, parapin_port[lpt]->irq);

  return 0;
}


/* this must be called by kernel programs when you're done using the
   parallel port.  it releases the port to be used by other apps. */
void pin_release(int lpt)
{
  /* restore interrupts to their former state */
  change_pin(lpt,LP_IRQ_MODE, old_irq_mode[lpt] ? LP_SET : LP_CLEAR);

  /* release and unregister the parallel port */
  parport_release(parapin_dev[lpt]);
  parport_unregister_device(parapin_dev[lpt]);


  parport_put_port(parapin_port[lpt]);

  /* Reset all lpt driver data */
  old_irq_mode[lpt]     = 0;
  have_irq_handler[lpt] = 0;
  parapin_dev[lpt]      = NULL;
  parapin_port[lpt]     = NULL; 
  lp_base[lpt]          = 0;
  printk("parapin: release %d\n", lpt);


}


/* are interrupts available? */
int pin_have_irq(int lpt)
{
  return (parapin_port[lpt] && have_irq_handler[lpt] && (parapin_port[lpt]->irq >= 0));
}

/* turn interrupts on */
void pin_enable_irq(int lpt)
{
  if (pin_have_irq(lpt)) {
    set_pin(lpt,LP_IRQ_MODE);
    udelay(10); /* wait for the spurious interrupt (if any) to pass */
    enable_irq(parapin_port[lpt]->irq);
  } else {
    printk("parapin: trying to enable interrupts without proper prereqs");
  }
}

/* turn interrupts off */
void pin_disable_irq(int lpt)
{
  if (parapin_port[lpt] && parapin_port[lpt]->irq >= 0)
    disable_irq(parapin_port[lpt]->irq);
  clear_pin(lpt,LP_IRQ_MODE);
}


#else  /* user-space-only functions */

/* user-land initialization */
int pin_init_user(int lpt,int base)
{
  lp_base[lpt] = base;

  /* get write permission to the I/O port */
  if (ioperm(lp_base[lpt], 3, 1) < 0) {
    perror("can't get IO permissions!");
    return -1;
  }

  pin_init_internal(lpt);
  return 0;
}

#endif /* __KERNEL__ */


/* If this is 2.6 or later, and we're building kparapin, we need to
   explicitly export symbols that are to be used by other modules. */
#ifdef __KERNEL__
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,0)
EXPORT_SYMBOL(set_pin);
EXPORT_SYMBOL(clear_pin);
EXPORT_SYMBOL(change_pin);
EXPORT_SYMBOL(pin_is_set);
EXPORT_SYMBOL(pin_input_mode);
EXPORT_SYMBOL(pin_output_mode);
EXPORT_SYMBOL(pin_mode);
EXPORT_SYMBOL(pin_release);
EXPORT_SYMBOL(pin_init_kernel);
EXPORT_SYMBOL(pin_have_irq);
EXPORT_SYMBOL(pin_enable_irq);
EXPORT_SYMBOL(pin_disable_irq);
#endif /* LINUX_VERSION_CODE */
#endif /* __KERNEL__ */



