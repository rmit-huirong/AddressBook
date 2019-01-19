SOURCES=addressbook.c addressbook_list.c addressbook_array.c commands.c helpers.c
HEADERS=addressbook.h addressbook_list.h addressbook_array.h commands.h helpers.h
PROGRAM=addressbook
FLAGS=-ansi -pedantic -Wall
OBJECTS=$(SOURCES:.c=.o)

all: $(PROGRAM)

addressbook: $(OBJECTS)
	gcc -o $@ $^
	
%.o: %.c
	gcc $(FLAGS) -c $^
	
clean:
	rm $(PROGRAM)
	rm $(OBJECTS)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile
