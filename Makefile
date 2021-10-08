CFLAGS := -g -Wall -pedantic-errors
targets := AVL max_heap 
SRCDIR := ./includes

run: ${targets}

%: ${SRCDIR}/%.h
	g++ ${CFLAGS} main.cpp -o $@

commit:
	git add ./*
	read -p "Enter message: " message
	git commit -m "${message}"
	git push origin master

