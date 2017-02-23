#This is yhe sample make file

EXEC = myexe


OBJS = ownlibMain.o cVowels.o cWords.o libmy.a

ownlibMain.o : ownlibMain.c libmy.a
	cc -c ownlibMain.c

cVowels.o : cVowels.c
	cc -c cVowels.c

cWords.o : cWords.c
	cc -c cWords.c

$(EXEC): $(OBJS)
	cc -o $(OBJS)

install:
	cp  $(EXEC) /home/venugopalv/session1/exe


clean:
	rm *.o


