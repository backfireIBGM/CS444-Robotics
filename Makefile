# Compiler
CC = g++ 

# Compiler flags
CFLAGS = -Wall 

# Source files
SRCS = calib.cc readParams.cc readData.cc

# Object files (replace .cc with .o)
OBJS = $(SRCS:.cc=.o)

# Output executable
TARGET = calibTest

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule for Windows
clean:
	del /Q $(OBJS) $(TARGET).exe 2>nul

# Run the program
run: $(TARGET)
	./$(TARGET)