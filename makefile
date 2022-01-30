CC = gcc
C_FLAGS = -Wall -pedantic -Iinclude -O3

SRC_DIR = src

TARGET  = coni
SRCS    = $(wildcard $(SRC_DIR)/*.c)


.PHONY: all	
all: clean $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $^ $(C_FLAGS) -o $@


run: 
	./$(TARGET)

.PHONY: clean
clean:
	-rm -f $(TARGET)
