
CC=gcc
LIBS=-lrt

all : cts-gen_moves cts-count_games

cts-gen_moves : cts-gen_moves.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

cts-count_moves : cts-count_games.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

/tmp/timestamps_index0.dat : cts-gen_moves
	./cts-gen_moves > $@
	./cts-gen_moves 20 >> $@
	./cts-gen_moves 17 >> $@
	./cts-gen_moves 55 >> $@
	./cts-gen_moves 33 >> $@
