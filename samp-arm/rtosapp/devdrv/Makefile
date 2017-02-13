CC=/usr/local/arm/3.4.1/bin/arm-linux-gcc
LD=/usr/local/arm/3.4.1/bin/arm-linux-ld
AR=/usr/local/arm/3.4.1/bin/arm-linux-ar
NM=/usr/local/arm/3.4.1/bin/arm-linux-nm
OC=/usr/local/arm/3.4.1/bin/arm-linux-objcopy
RM=rm
CP=cp
LIBS=-ldpk 
DPKDIR=/usr/local/armdpk1.0

OBJS= sysInit.o usrcfg.o  symtable.o app.o myserdrv.o 
 
CC_INCLUDE     = -I$(DPKDIR)
LIBRARY        = -L$(DPKDIR)
CFLAGS         = $(CC_INCLUDE) -c
symbols: $(OBJS) 
	$(LD) -N -Ttext 0x100000 -e sysInit -nostdlib -o ram.out \
        $(OBJS) $(LIBRARY)  $(LIBS) /usr/local/arm/3.4.1/lib/gcc/arm-linux/3.4.1/libgcc.a
	$(CP) symtable.c tempSym
	makeSymTab ram.out symtable.c 1000
	cp symtable.c tempsymtbl.c
	$(CC) $(CFLAGS) -c symtable.c
	$(LD) -N -Ttext 0x100000 -e sysInit -nostdlib -o ram.out \
	$(OBJS) $(LIBRARY)  $(LIBS) /usr/local/arm/3.4.1/lib/gcc/arm-linux/3.4.1/libgcc.a
	$(OC)  -O srec ram.out ram.hex
	$(OC)  -O binary ram.out ram.bin
	$(NM) ram.out > symbols
	$(CP) tempSym symtable.c
	$(RM) tempSym
	$(CP) ram.bin /home/dsl/

sysInit.o:   sysInit.S
	$(CC)  -c sysInit.S
symtable.o: symtable.c
	$(CC) $(CFLAGS)  symtable.c
usrcfg.o: usrcfg.c
	$(CC) $(CFLAGS)  usrcfg.c

app.o: app.c
	$(CC) $(CFLAGS)  app.c

clean:
	$(RM) *.o ram.out ram.bin ram.hex
	$(RM) symbols
	$(RM) *~
	$(RM) *.hex
	$(RM) *.bin
	$(RM) *.out

