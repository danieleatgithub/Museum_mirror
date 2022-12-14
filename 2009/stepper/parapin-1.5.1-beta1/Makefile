#    This file is part of the package "parapin".
#
#    The parapin package is free software; you can redistribute it
#    and/or modify it under the terms of the GNU Library General Public
#    License (LGPL) as published by the Free Software Foundation.
#
#    The parapin package is distributed in the hope that it will be
#    useful, but WITHOUT ANY WARRANTY; without even the implied
#    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#    See the GNU Library General Public License for more details.
#
#    You should have received a copy of the GNU Library General Public
#    License along with parapin; if not, write to the Free
#    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
#    02111-1307 USA
#
#
#    For futher information on the parapin package, please refer to the
#    project information hosted on Sourceforge --
#
#    http://sourceforge.net/projects/parapin/
#
#
#
# Parapin Makefile-2.6 -- build parapin for 2.6 kernels
#
# original author Jeremy Elson, First released 30 March 2000
#
# Currently maintained by Al Hooton (al@hootons.org)
#
# $Id: Makefile-2.6,v 1.10 2007/12/16 17:38:17 ahooton Exp $
#

# Set this to be the location of your Linux kernel header files (and
# modules, if you're using the kernel modules).  If you are building
# for the kernel you are running, the lines below with "uname" in the
# paths will usually work.  If you're installing the libs or kernel modules,
# you will have to run make as root.  If you are building for a
# different kernel than you are running, you will need to edit these
# paths to explicitly point to the target kernel source and lib trees.
# You may also need to edit these if you're running an SMP
# kernel on some distros.
LINUX_SRC = /usr/src/linux-headers-`uname -r`/
LINUX_MODULES := /lib/modules/`uname -r`/kernel/

LIBPARAPIN_OBJS := parapin.o

EXAMPLE_DIR := examples
EXAMPLE_PROGRAMS := \
	$(EXAMPLE_DIR)/inputtest\
	$(EXAMPLE_DIR)/outputtest\
	$(EXAMPLE_DIR)/adc0831\
	$(EXAMPLE_DIR)/ppdrv-test

### Determine if we have a linux/config.h file or not
findCmd=find $(LINUX_SRC) -maxdepth 1 -name config.h

ifeq ($(strip  $(shell $(findCmd))), )
	CONFIG_H=
	unexport CONFIG_H
else
	CONFIG_H=-DCONFIG_H
	export CONFIG_H
endif

CFLAGS += -O2 -g -Wall $(CONFIG_H)


###########################################################################

default: libparapin.a $(EXAMPLE_PROGRAMS)

install: libparapin.a
	/usr/bin/install -o bin -g bin -m 644 libparapin.a /usr/local/lib/
	/usr/bin/install -o bin -g bin -m 444 parapin.h /usr/local/include/

modules:
	make -C $(LINUX_SRC) M=`pwd` modules

modulesinstall: modules
	/usr/bin/install -o root -g root -m 644 kparapin/kparapin.ko $(LINUX_MODULES)
	/usr/bin/install -o root -g root -m 644 parapindriver/parapindriver.ko $(LINUX_MODULES)
	/usr/bin/install -o root -g root -m 644 parapindriver.h /usr/local/include/
	/usr/bin/install -o root -g root -m 744 ppdrv_load.sh /usr/local/bin/
	depmod -q

all: libparapin.a modules $(EXAMPLE_PROGRAMS)

allinstall: all install modulesinstall

##### libraries

libparapin.a: $(LIBPARAPIN_OBJS)
	ar -cr libparapin.a $(LIBPARAPIN_OBJS)

parapin.o: parapin.c parapin.h parapin-linux.h
	$(CC) $(CFLAGS) -c parapin.c;

# Example programs and the test suite
$(EXAMPLE_DIR)/%: $(EXAMPLE_DIR)/%.c libparapin.a parapin.h parapin-linux.h
	$(CC) $(CFLAGS) -I. -L. $< -o $@ -lparapin


# Clean target
clean:
	rm -f *.[oa] *.ko $(EXAMPLE_PROGRAMS)
	make -C $(LINUX_SRC) M=`pwd` clean


#####################################

# Language binding targets, must be invoked explicitly as
# "make parapin_<binding-name>-<target>".  Note that all
# the clean targets are also invoked from the main clean target
# above

parapin_%-build: libparapin.a
	make -C $(subst -build,,$@) build

parapin_%-install: libparapin.a
	make -C $(subst -install,,$@) install

parapin_%-clean:
	make -C $(subst -clean,,$@) clean
