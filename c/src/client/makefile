include ../../make/common.in

PHONY: all
CC=gcc
INC+= -Iinclude
LINKAGE+=-L$(LIB_PATH) -lcommon
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(SRC))
TARGET=$(BIN_PATH)/client

all: client

client: $(OBJ)
	@echo "${LINK_PROMPT} client..."
	$(CC) -o $(TARGET) $^ $(LINKAGE)

OBJ: %.o

obj/%.o:src/%.c 
	@mkdir -p obj
	@echo "${COMP_PROMPT} $<..."
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@

clean:
	@rm -rf $(all) $(TARGET) obj
