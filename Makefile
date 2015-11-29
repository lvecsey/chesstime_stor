
CC=gcc

all : chesstime_stor cts-gen_moves cts-count_games cts_lookup cts_insert

chesstime_stor : chesstime_stor.o readfile.o writefile.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

cts-gen_moves : LIBS=-lrt

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

cts_lookup : cts_lookup.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

cts_insert : cts_insert.o readfile.o writefile.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
