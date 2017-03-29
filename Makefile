all: clean pri_main.o pri_q931.o pri_q921.o pri_func.o pri_syntax.o
	gcc -o pri_syntax pri_main.o pri_q931.o pri_q921.o pri_func.o pri_syntax.o
pri_main.o:
	gcc -c pri_main.c
pri_q931.o:
	gcc -c pri_q931.c
pri_q921.o:
	gcc -c pri_q921.c
pri_func.o:
	gcc -c pri_func.c
pri_syntax.o:
	gcc -c pri_syntax.c
clean:
	rm *.o
	rm pri_syntax
