
Timestamp data for chess games can be stored in flat files, with new games appended to the end.
In this way the timestamp data for roughly 12 billion chess games can be stored on a single 8TB hard drive.

<p>output a newgame identifier along with a set of timestamps for the given number of moves</p>

<code>
./cts-gen_moves 55
</code>

<p>output a newgame identifier along with a set of timestamps for the average length of a chess game</p>

<code>
./cts-gen_moves 40
</code>

<p>count the number of games in a given storage file</p>

<code>
./cts-count_games < /tmp/timestamps_index0.dat
</code>

--

./cts_lookup and ./cts_insert and programs which work with tcpclient to access the microservice

<code>
  tcpclient 192.168.1.75 4250 ./cts_lookup 656 0

  DEBUG=1 tcpclient 192.168.1.75 4250 ./cts_insert < sample_times.txt
</code>

The insertion is expected to give a response: a file offset in bytes, and file number.
The above example specifies a DEBUG environment variable which means some textual output
for the response will be displayed.

Before any of the above tcpclient commands will connect, you need to establish a server.
For production use Specify the path to the index files, such as /mnt/disk0_timestamps

<code>
  tcpserver -vRHl0 192.168.1.75 4250 ./chesstime_stor /tmp
</code>

This will run the server instance and access files such as timestamps_index0.dat, timestamps_index1.dat, etc.



