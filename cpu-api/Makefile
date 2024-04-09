all: 1c 2c 3c 3c-nowait

clean:
	rm -rf 1c 2c 2.txt 3c 3.txt
1c: 1.c
	gcc -o 1c 1.c

2c: 2.c
	gcc -o 2c 2.c

3c: 3.c
	gcc -o 3c 3.c

3c-nowait: 3-nowait.c
	gcc -o 3c 3-nowait.c