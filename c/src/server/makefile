include ../../make/common.in

PHONY: all
CC=gcc
INC+= -Iinclude
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(SRC))
TARGET=$(BIN_PATH)/server

all:server 

server: $(OBJ)
	@echo "${LINK_PROMPT} server..."
	$(CC) -o $(TARGET) $^

OBJ: %.o

obj/%.o:src/%.c 
	@mkdir -p obj
	@echo "${COMP_PROMPT} $<..."
	@$(CC) -c $(INC) $< -o $@

clean:
	@rm -rf $(all) $(TARGET) obj
