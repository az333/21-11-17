all: pipe.c
	gcc pipe.c

run: pipe
	./pipe

clean:
	rm *.out
	rm *~
