obj-m = ioremap_fnd_dd.o ioremap_led_dd.o

KDIR = /root/work/kernel-2.6.35
PWD = $(shell pwd)
CC = arm-linux-gcc

all: module app
module:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
app:
	$(CC) -static -o main main.c -lpthread
clean:
	rm -rf *.ko *.o *.mod.* *.symvers
