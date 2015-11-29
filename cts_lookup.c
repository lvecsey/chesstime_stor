
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/time.h>
#include <string.h>

#include "readfile.h"

#include "cts_stor.h"

int main(int argc, char *argv[]) {

  unsigned char buf[4096];

  u_int16_t cmd;

  size_t offset = argc>1 ? strtol(argv[1],NULL,10) : 0;
  long int indexno = argc>2 ? strtol(argv[2],NULL,10) : 0;

  ssize_t bytes_sent;
  ssize_t bytes_read;

  ssize_t bytes_written;

  long int n;

  {
    u_int64_t offset;
    u_int16_t indexno;

    unsigned char outbuf[12];
    
    cmd = CTS_LOOKUP;

    memcpy(outbuf, &cmd, 2);
    memcpy(outbuf+2, &offset, 8);
    memcpy(outbuf+10, &indexno, 2);
    bytes_sent = write(7, outbuf, sizeof(outbuf));
    if (bytes_sent != sizeof(outbuf)) {
      fprintf(stderr, "%s: Expected write of %ld bytes, got %ld.\n", __FUNCTION__, sizeof(outbuf), bytes_sent);
      return -1;
    }

    bytes_read = read(6, buf, sizeof(buf));
    if (bytes_read > 0) {
      struct timespec *ptr;
      printf("Retrieved %ld timestamps.\n", bytes_read / sizeof(struct timespec));
      ptr = (struct timespec*) buf;
      for (n = 0; n < bytes_read / sizeof(struct timespec); n++) {
	printf("%ld %ld\n", ptr->tv_sec, ptr->tv_nsec);
	ptr++;
	if (ptr->tv_sec == 0 && ptr->tv_nsec==0) break;
      }
      
    }

  }

  printf("COMPLETE\n");

  return 0;

}
