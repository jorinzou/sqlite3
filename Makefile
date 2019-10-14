CC=gcc

OBJ=Sqlite
all:$(OBJ)

HERE=$(shell pwd)
SQLITE_LIB_DIR=$(HERE)/sqlite/
incs=-I$(HERE)
incs+=-I$(SQLITE_LIB_DIR)

files:=$(HERE)/src/main.c
files+=$(foreach dir,$(SQLITE_LIB_DIR),$(wildcard $(SQLITE_LIB_DIR)/*.c))

OBJS_C := $(patsubst %.c,%.o,$(files))


CFLAGS=-O0 -g 
CFLAGS+=$(incs) 

LDFLAGS=-lpthread 
LDFLAGS+=-ldl 

$(OBJ):$(OBJS_C)
	$(CC)  $(LDFLAGS) -o $@ $^ 
			
$(OBJS_C):%.o:%.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(HERE)/*.o
	rm -rf $(SQLITE_LIB_DIR)/*.o
	rm -rf $(HERE)/$(OBJ)