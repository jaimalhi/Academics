# CFLAGS = -g -Wall -Werror -ggdb3 -Wextra -Wno-unused-parameter
CFLAGS = -Wall -Werror -Wextra

all: build

basic: 
	g++ q7.cpp -o x

build:
	g++ $(CFLAGS) q7.cpp -o x

run: build
	./x

clean:
	rm -f x *.o