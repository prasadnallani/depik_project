CC=cc
LD=ld
AR=ar
RM=@rm
NM=@nm
OC=@objcopy
CP=@cp

UDPOBJS= rtldrv.o iface.o pktbuf.o arp.o icmp.o nwutil.o nwstk.o \
	ip.o udp.o tcp.o tcp1.o  timer.o socket.o

APPOBJS=sysInit.o usrcfg.o app.o symtable.o udpSrv.o tcpsrv.o

INCDIR         = -I/usr/local/dpk220r3
LIBDIR         = -L/usr/local/dpk220r3
CFLAGS         = $(INCDIR) -c  
LIBS           = -ldpk

symbols: $(APPOBJS) $(UDPOBJS) 
	$(LD) -N -Ttext 0x100000 -e sysInit -nostdlib -o ram.out \
	$(APPOBJS) $(UDPOBJS) $(LIBDIR) $(LIBS) 
	$(CP) symtable.c tempSym
	@makeSymTab ram.out symtable.c
	$(CC) $(CFLAGS) symtable.c
	$(LD) -N -Ttext 0x100000 -e sysInit -nostdlib -o ram.out \
	$(APPOBJS) $(UDPOBJS) $(LIBDIR) $(LIBS) 
	$(OC)  -O srec ram.out ram.hex
	$(OC)  -O binary ram.out ram.bin
	$(NM) ram.out > symbols
	$(CP) tempSym symtable.c
	$(RM) tempSym
	cp ram.bin /tftpboot/venu

sysInit.o:sysInit.S
	$(CC)  -c sysInit.S

%.o:%.c
	$(CC) $(CFLAGS) $<

clean:
	$(RM) *.o
	$(RM) *.bin
	$(RM) *.out
	$(RM) symbols

