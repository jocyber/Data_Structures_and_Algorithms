CFLAGS := -g -Wall -pedantic-errors
targets := AVL max_heap 
SRCDIR := ./includes

run: ${targets}

%: ${SRCDIR}/%.h
	g++ ${CFLAGS} main.cpp -o $@

