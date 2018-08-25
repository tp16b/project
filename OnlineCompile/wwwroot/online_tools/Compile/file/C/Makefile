.PHONY: clean

DICT=/home/tp/project/OnlineCompile/wwwroot/online_tools/Compile
SRC=$(DICT)/file/edit.c
EXECFILE=$(DICT)/file/compile

$(EXECFILE):$(SRC)
	gcc -g -o $@ $^ 
clean:
	rm -rf $(EXECFILE) 
