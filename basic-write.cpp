#include <unistd.h>
#include <stdlib.h>
#include <cstring>

/**
 * The most basic version of write from the blog post that doesn't attempt to
 * open a handle for perf, which seems to fail if perf hasn't been run
 */
int main() {
  size_t buf_size = 1 << 18; // 256KiB
  char* buf = (char*) malloc(buf_size);
  memset((void*)buf, 'X', buf_size); // output Xs
  while (true) {
    size_t remaining = buf_size;
    while (remaining > 0) {
      // Keep invoking `write` until we've written the entirety
      // of the buffer. Remember that write returns how much
      // it could write into the destination -- in this case,
      // our pipe.
      ssize_t written = write(
        STDOUT_FILENO, buf + (buf_size - remaining), remaining
      );
      remaining -= written;
    }
  }
}
