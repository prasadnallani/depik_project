LPATH =/usr/local/arm/3.4.1

CC = $(LPATH)/bin/arm-linux-gcc
LD = $(LPATH)/bin/arm-linux-ld
OC = $(LPATH)/bin/arm-linux-objcopy
NM = $(LPATH)/bin/arm-linux-nm
GCCLIB = $(LPATH)/lib/gcc/arm-linux/3.4.1/libgcc.a

CFLAGS  = -c  

OBJS = head.o app.o minclib.o

ram.bin: $(OBJS)
	$(LD) -p -X -T ld-script $(OBJS) $(GCCLIB) -o ram.out 
	$(OC) -O srec ram.out ram.hex
	$(OC) -O binary ram.out ram.bin
	$(NM) ram.out > symbols
	cp ram.bin /tftpboot

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

%.o:%.S
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o ram.out ram.bin ram.hex image symbols *~

