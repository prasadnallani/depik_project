OBJS = mn.o mstrlen.o mstrcpy.o mstrcat.o cntvwls.o cntwords.o

strprg: $(OBJS)
	cc -o strprg $(OBJS)

mn.o: mn.c mystr.h
	cc -c mn.c
mystrlen.o: mystrlen.o mystr.h
	cc -c mystrlen.c
mystrcpy.o: mystrcpy.o mystr.h
	cc -c mystrcpy.c
mystrcat.o: mystrcat.o mystr.h
	cc -c mystrcat.c
cntvwls.o: cntvwls.c mystr.h
	cc -c cntvwls.c
cntwords.o: cntwords.c mystr.h
	cc -c cntwords.c	
