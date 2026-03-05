# Variables
CC = $(CROSS_COMPILE)gcc
CFLAGS = -g -Wall
TARGET = writer
OBJS = writer.o

# Default target,,,,
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

writer.o: writer.c
	$(CC) $(CFLAGS) -c writer.c

#target clean.....
clean:
	rm -f $(TARGET) $(OBJS)
