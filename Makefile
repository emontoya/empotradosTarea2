.PHONY: all clean install uninstall

all: programa1 programa2

programa1: programa1.c libTarea2  
	gcc -Wall -L. -lTarea2 -o programa1 programa1.c 
	
programa2: programa2.c libTarea2 
	gcc -Wall -L. -lTarea2 -o programa2 programa2.c 


libTarea2: tarea2Utils.o
	gcc -shared -o libTarea2.so tarea2Utils.o

tarea2Utils.o: tarea2Utils.c
	gcc -Wall -fPIC -c tarea2Utils.c tarea2Utils.h

install:
	install ./libTarea2.so /usr/lib/libTarea2.so 
	install ./programa1 /usr/local/bin/programa1
	install ./programa2 /usr/local/bin/programa2

uninstall:
	rm -f /usr/lib/libTarea2.so 
	rm -f /usr/local/bin/programa1
	rm -f /usr/local/bin/programa2

clean:
	rm -f *.o *.so programa1 programa2
