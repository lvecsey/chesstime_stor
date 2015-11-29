
Timestamp data for chess games can be stored in flat files, with new games appended to the end.
In this way the timestamp data for roughly 12 billion chess games can be stored on a single 8TB hard drive.

# output a newgame identifier along with a set of timestamps for the given number of moves
./cts-gen_moves 55

# output a newgame identifier along with a set of timestamps for the average length of a chess game
./cts-gen_moves 40

# count the number of games in a given storage file
./cts-count_games < /tmp/timestamps_index0.dat

