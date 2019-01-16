.PHONY:clean 

INCLUDE=./include
SRCPATH=./src
MYLIB=/usr/local/mysql/lib/

main: $(SRCPATH)/main.cc $(SRCPATH)/admin.cc  $(SRCPATH)/student.cc $(SRCPATH)/teacher.cc $(SRCPATH)/course.cc $(SRCPATH)/grade.cc 
	g++ -std=c++11 -g -o $@ $^ -I$(INCLUDE) -L/$(MYLIB)  -lmysqlclient

clean: 
	rm -rf main

