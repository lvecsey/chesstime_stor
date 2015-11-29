
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <time.h>

#include "cts_stor.h"

#define DEFAULT_BASEPATH "/mnt/disk0_timestamps"

#define MAX_FILESZ 94489280512

#include "readfile.h"
#include "writefile.h"

int main(int argc, char *argv[]) {

  char *basepath = argc>1 ? argv[1] : DEFAULT_BASEPATH;

  u_int16_t cmd;

  u_int64_t offset;
  u_int16_t indexno;

  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  long int num_indexes = 1;

  void *m;
  int fd;

  unsigned char buf[4096];

  ssize_t bytes_read;
  ssize_t bytes_written;

  struct timespec current;
  int retval;

  char filename[255];

  sprintf(filename, "%s/timestamps_index%ld.dat", basepath, 0L); 

  fd = open(filename, O_RDWR | O_APPEND | O_CREAT, mode);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  for (;;) {

    bytes_read = read(0, &cmd, sizeof(cmd));
    if (bytes_read != sizeof(cmd)) return -1;

    switch (cmd) {

    case CTS_LOOKUP:

      bytes_read = read(0, &offset, sizeof(offset));
      if (bytes_read != sizeof(offset)) return -1;

      bytes_read = read(0, &indexno, sizeof(indexno));
      if (bytes_read != sizeof(indexno)) return -1;

      bytes_read = pread(fd, buf, sizeof(buf), offset);
      if (bytes_read > 0) {
	bytes_written = write(1, buf, bytes_read);
      }

      break;

    case CTS_INSERT:

      {
	struct stat buf;
	retval = fstat(fd, &buf);
	if (retval==-1) {
	  perror("fstat");
	  return -1;
	}
	offset = buf.st_size;
	indexno = 0;
      }

      do {

	bytes_read = readfile(0, &current, sizeof(current));
	if (bytes_read < 0) {
          fprintf(stderr, "%s: Trouble reading timestamp.\n", __FUNCTION__);
          return -1;
        }

	if (current.tv_sec == 0 && current.tv_nsec == 0) {

	  bytes_written = writefile(fd, &offset, sizeof(offset));
	  if (bytes_read < 0) {
	    fprintf(stderr, "%s: Trouble returning the file offset.\n", __FUNCTION__);
	    return -1;
	  }

	  bytes_written = writefile(fd, &indexno, sizeof(indexno));
	  if (bytes_written < 0) {
	    fprintf(stderr, "%s: Trouble returning the file index number.\n", __FUNCTION__);
	    return -1;	  
	  }

	}

	else {

	  bytes_written = writefile(fd, &current, sizeof(current));
	  if (bytes_written < 0) {
            fprintf(stderr, "%s: Trouble appending timestamp data to index file.\n", __FUNCTION__);
            return -1;
          }

	}

      } while (current.tv_sec != 0);
      
      break;

    }

  }

  return 0;

}
