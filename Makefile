libjournal.a : 
	gcc -c -Wall lib/journal.c
	ar rcs libjournal.a journal.o

