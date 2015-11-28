
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>

int main(int argc, char *argv[]) {

  struct timespec current;
  ssize_t bytes_read;

  long int num_games = 0;
  long int num_timestamps = 0;

  for (;;) {

    bytes_read = read(0, &current, sizeof(struct timespec));
    if (!bytes_read || bytes_read == -1) break;

    if (bytes_read != sizeof(struct timespec)) {
      printf("Expected %ld bytes but read returned %ld.\n", sizeof(struct timespec), bytes_read);
      return -1;
    }

    if (current.tv_sec == 0 && current.tv_nsec == 0) {
      num_games++;
      continue;
    }

    num_timestamps++;

  }

  printf("%ld", num_games);

  return 0;

}
