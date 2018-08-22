.PHONY: clean 

CC=gcc
INCLUDE=./wwwroot/online_tools/
EXEC=./bin/httpd

$(EXEC): src/main.c src/http.c src/error_respond.c
	$(CC) -g -o $@ $^ -I$(INCLUDE) -lpthread

clean:
	rm -f $(EXEC) 
