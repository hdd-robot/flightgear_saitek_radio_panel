CC = gcc
CFLAGS = -Wall -g
EXEC_NAME = saitek_fg
INCLUDES =
LIBS =
OBJ_FILES = saitek.o socket_fg.o stkmanager.o
INSTALL_DIR = /usr/bin

all : $(EXEC_NAME)

clean :
	rm -f *~
	rm -f $(EXEC_NAME) $(OBJ_FILES)
	rm -f *.o
	rm -f *.gch


$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME)  $(OBJ_FILES)  $(LIBS)
	cp $(EXEC_NAME) ../bin/

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

run :
	./saitek_fg

