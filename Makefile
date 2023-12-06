# Compiler settings - Can change to cc or clang if needed
CC = gcc

# Compiler flags, e.g. -Wall for extra warnings, -g for debugging
CFLAGS = -Wall -g

# Linker flags, e.g. -lm for linking with math library (if needed)
LDFLAGS = 

# Define your source files here
SOURCES = ChessLibrary.c ChessLibraryTester.c Firmware.c GameEngine.c

# Define your header files here
HEADERS = ChessLibrary.h GameEngine.h

# Define the object files from the source files (automatic)
OBJECTS = $(SOURCES:.c=.o) 

# Define your target executable
TARGET = ChessLibraryTester

# Default target
all: $(TARGET)

# Rule for linking the final executable
# Depends on the object files (not source files directly)
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule for compiling source files to object files
# Generic rule, which uses automatic variables:
# $< refers to the sourcd ce file, $@ refers to the output file
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	del $(OBJECTS) $(TARGET)
	

# Rule to run the program
run: all
	./$(TARGET)