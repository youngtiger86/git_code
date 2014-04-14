include ../../make/common.in

INC+= -Iinclude
CFLAGS+=-fPIC 
LINKAGE+=-shared
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(SRC))
TARGET=$(LIB_PATH)/libcommon.so

$(TARGET): $(OBJ)
	@echo "${LINK_PROMPT} libcommon.so..."
	@$(CC) $(LINKAGE) -o $(TARGET) $^

OBJ: %.o

obj/%.o:src/%.c 
	@mkdir -p obj
	@echo "${COMP_PROMPT} $<..."
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@

clean:
	@rm -rf $(TARGET) obj
