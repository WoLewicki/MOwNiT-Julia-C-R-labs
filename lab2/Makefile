main:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/wojlewy/gsl/lib
	sudo ldconfig
	gcc -Wall -I/home/wojlewy/gsl/include -c main.c
	gcc -L/home/wojlewy/gsl/lib main.o -lgsl -lgslcblas -lm -o main
clean:
	rm -r main.o main
