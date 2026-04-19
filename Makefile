CC = gcc
CFLAGS = -Wall -g
TARGET = myshell

# Source files are inside the src/ directory
SRCS = src/advanced.c src/builtin.c src/executor.c src/main.c src/parser.c
# Object files will be created in the same src/ directory
OBJS = $(SRCS:.c=.o)
# The header file location
DEPS = src/shell.h

all: $(TARGET)

# Links the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiles each .c file into a .o file
# It depends on the .c file AND the shell.h header
src/%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
