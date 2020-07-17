# change application name here (executable output name)
TARGET=app

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O2
# warnings
WARN=-Wall

DOXFILE=dconfig

PTHREAD=-pthread

CCFLAGS= $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS= main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) && doxygen $(DOXFILE)

main.o: src/main.c
		$(CC) -c $(CCFLAGS) src/main.c  $(GTKLIB) -o main.o

# on_button_clicked_events.o: on_button_clicked_events.c
# 		$(CC) -c $(CCFLAGS) on_button_clicked_events.c  $(GTKLIB) -o on_button_clicked_events.o

clean:
		rm -f *.o $(TARGET)
