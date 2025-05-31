CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJS = main.o calendar.o input.o utils.o
TARGET = calendar

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c calendar.h input.h utils.h
	$(CC) $(CFLAGS) -c main.c

calendar.o: calendar.c calendar.h
	$(CC) $(CFLAGS) -c calendar.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJS) $(TARGET)