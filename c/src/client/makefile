include ../../make/common.in

PHONY: all
CC=gcc
INC+= -Iinclude
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(SRC))
TARGET=$(BIN_PATH)/client

all: client

client: $(OBJ)
	@echo "${LINK_PROMPT} client..."
	@$(CC) -o $(TARGET) $^

OBJ: %.o

obj/%.o:src/%.c 
	@mkdir -p obj
	@echo "${COMP_PROMPT} $<..."
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@

clean:
	@rm -rf $(all) $(TARGET) obj
