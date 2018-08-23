.PHONY: clean 

CC=gcc
INCLUDE=./wwwroot/online_tools/
SRCPATH=./src
EXEC=./bin/httpd

$(EXEC): $(SRCPATH)/main.c $(SRCPATH)/http.c $(SRCPATH)/error_respond.c $(SRCPATH)/exec_cgi.c
	$(CC) -g -o $@ $^ -I$(INCLUDE) -lpthread

clean:
	rm -f $(EXEC) 
