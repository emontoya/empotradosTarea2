.PHONY: all clean

all: programa1 programa2


programa1:
	gcc -Wall -g -o programa2 programa1.c tarea2Utilis.c

programa2: programa2.c tarea2Utils.c
	gcc -Wall -g -o programa2 programa2.c tarea2Utils.c

clean:
	rm -f *.o
