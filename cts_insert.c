
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

int main(int argc, char *argv[]) {

  struct timespec current;

  FILE *fp = stdin;
  char *line = NULL;
  size_t len = 0;
  ssize_t bytes_read;
  ssize_t bytes_written;

  long int debug = getenv("DEBUG") != NULL;

  while ((bytes_read = getline(&line, &len, fp)) != -1) {

    if (len>0) {
      sscanf(line, "%ld %ld", &current.tv_sec, &current.tv_nsec);
      bytes_written = write(7, &current, sizeof(struct timespec));
      if (bytes_written != sizeof(struct timespec)) return -1;
    }

  }

  close(1);

  {
    u_int64_t offset;
    u_int16_t indexno;

    unsigned char buf[10];

    bytes_read = read(6, buf, 10);
    if (bytes_read != 10) return -1;

    memcpy(&offset, buf, sizeof(u_int64_t));
    memcpy(&indexno, buf, sizeof(u_int16_t));

    if (debug) {
      printf("%ld %u\n", offset, indexno);
    }
    else write(1, buf, 10);

  }

  free(line);

  return 0;

}
