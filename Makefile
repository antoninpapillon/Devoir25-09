libjournal.a : 
	gcc -c -Wall lib/journal.c
	ar rcs libjournal.a journal.o

libjournal.so.1.1.57 : 
	gcc -fPIC -c -Wall lib/journal.c
	gcc -shared -fPIC -Wl,-soname,libjournal.so.1 -o libjournal.so.1.1.57 journal.o -lc
	ln -sf libjournal.so.1.1.57 libjournal.so.1
	ln -sf libjournal.so.1.1.57 libjournal.so

journal : libjournal.so.1.1.57 libjournal.so.1
	gcc -c -Wall main.c
	gcc -o journal main.o -L. -ljournal
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./journal

clean : 
	rm -f *.o *libjournal*

