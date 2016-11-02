try: 2048.o 
	cc 2048.o -o try
2048.o: 2048.c
	cc -Wall -c 2048.c

