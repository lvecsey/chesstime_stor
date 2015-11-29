
Timestamp data for chess games can be stored in flat files, with new games appended to the end.
In this way the timestamp data for roughly 12 billion chess games can be stored on a single 8TB hard drive.

# output a newgame identifier along with a set of timestamps for the given number of moves
./cts-gen_moves 55

# output a newgame identifier along with a set of timestamps for the average length of a chess game
./cts-gen_moves 40

# count the number of games in a given storage file
./cts-count_games < /tmp/timestamps_index0.dat

--

./cts_lookup and ./cts_insert and programs which work with tcpclient to access the microservice

  tcpclient 192.168.1.75 4250 ./cts_lookup 656 0

  DEBUG=1 tcpclient 192.168.1.75 4250 ./cts_insert < sample_times.txt

The insertion is expected to give a response: a file offset in bytes, and file number.
The above example specifies a DEBUG environment variable which means some textual output
for the response will be displayed.

Before any of the above tcpclient commands will connect, you need to establish a server.
For production use Specify the path to the index files, such as /mnt/disk0_timestamps

  tcpserver -vRHl0 192.168.1.75 4250 ./chesstime_stor /tmp

This will run the server instance and access files such as timestamps_index0.dat, timestamps_index1.dat, etc.



