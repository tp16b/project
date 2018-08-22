.PHONY: all clean

all:select test  
select: select.c
	gcc -std=c99 -o $@ $^ -I/usr/include/mysql   -L/usr/lib64/mysql/      -lmysqlclient

test: test.c
	g++ -o $@ $^
clean:
	rm -rf select
