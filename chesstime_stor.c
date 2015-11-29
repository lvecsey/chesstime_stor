
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>

#define DEFAULT_BASEPATH "/mnt/disk0_timestamps"

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

  char filename[255];

  sprintf(filename, "%s/timestamps_index%ld.dat", basepath, 0L); 

  fd = open(filename, O_RDWR | O_APPEND | O_CREAT, mode);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  for (;;) {

    bytes_read = read(0, &cmd, sizeof(u_int16_t));
    if (bytes_read != sizeof(cmd)) return -1;

    bytes_read = read(0, &offset, sizeof(offset));
    if (bytes_read != sizeof(offset)) return -1;

    bytes_read = read(0, &indexno, sizeof(indexno));
    if (bytes_read != sizeof(indexno)) return -1;

    bytes_read = pread(fd, buf, sizeof(buf), offset);
    if (bytes_read > 0) {
      bytes_written = write(1, buf, bytes_read);
    }

  }

  return 0;

}