CC = gcc
CFLAGS = -g -Wall
TARGET = reminder

all: $(TARGET)

$(TARGET): main.o reminder.o linked_list.o interact.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o reminder.o linked_list.o interact.o

main.o: main.c reminder.h interact.h
	$(CC) $(CFLAGS) -c main.c

reminder.o: reminder.c reminder.h linked_list.h
	$(CC) $(CFLAGS) -c reminder.c

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

interact.o: interact.c interact.h reminder.h
	$(CC) $(CFLAGS) -c interact.c

clean:
	rm -f *.o $(TARGET)
