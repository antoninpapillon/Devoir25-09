

libjournal.a : 
	gcc -c -Wall lib/journal.c
	ar rcs libjournal.a journal.o

libjournal.so.1.1.57 : 
	gcc -fPIC -c -Wall lib/journal.c
	gcc -shared -fPIC -Wl,-soname,libjournal.so.1 -o libjournal.so.1.1.57 journal.o -lc
	ln -sf libjournal.so.1.1.57 libjournal.so.1
	ln -sf libjournal.so.1.1.57 libjournal.so

clean : 
	rm -f *.o *libjournal* 


