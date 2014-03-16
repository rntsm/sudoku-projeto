CC = gcc
CFLAGS = -Wall -g -pthread

PROGRAMS = verifica dicas resolucao/

all: $(PROGRAMS)

clean:
	rm -f *~ $(PROGRAMS)
