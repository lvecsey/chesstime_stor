
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

  long int num_moves = argc>1 ? strtol(argv[1],NULL,10) : 40;

  long int n;

  struct timespec now, before, start;

  clock_gettime(CLOCK_MONOTONIC, &start);

  now.tv_sec = 0;
  now.tv_nsec = 0;
  write(1, &now, sizeof(struct timespec));

  for (n = 0; n < num_moves; n++) {

    clock_gettime(CLOCK_MONOTONIC, &now);
    write(1, &now, sizeof(struct timespec));

  }

  return 0;

}
