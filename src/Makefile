obj-m := module.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) modules

clean:
	rm -rvf *.o *.ko *.mod.c *.mod *.cmd *.symvers *.order .*.cmd