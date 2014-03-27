include ../../make/common.in

PHONY: all
CC=gcc
INC=-Iinclude
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(SRC))

all: client

client: $(OBJ)
	@echo "Linking client..."
	$(CC) -o $(BIN_PATH)/$@ $^

OBJ: %.o

obj/%.o:src/%.c 
	@mkdir -p obj
	@echo "Compiling file $<"
	$(CC) -c $(INC) $< -o $@

clean:
	rm -rf $(all) client obj
