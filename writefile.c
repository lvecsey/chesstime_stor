
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int writefile(int fd, void *p, size_t len) {

  unsigned char *adv_p = (unsigned char*) p;
  size_t remaining = len;
  ssize_t bytes_written;

  while (remaining > 0) {
    bytes_written = write(fd, adv_p + len - remaining, remaining);
    if (bytes_written <= 0) return -1;
    remaining -= bytes_written;
  }

  return 0;

}


