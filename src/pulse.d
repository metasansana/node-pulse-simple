#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#define BUFSIZE 1024

int main(int argc, char*argv[]) {

  //Sample format to use:
  static const pa_sample_spec ss = {
      .format = PA_SAMPLE_S16LE,
      .rate = 44100,
      .channels = 2
  };

  pa_simple *s = NULL;
  int ret = 1;
  int error;

  if(argc > 1) {

    int fd;

    if((fd = open(argv[1], O_RDONLY)) < 0 ) {

      fprintf(stderr, __FILE__": open() failed: %s\n", strerror(errno));
      goto finish;

    }

    if (dup2(fd, STDIN_FILENO) < 0) {
      fprintf(stderr, __FILE__": dup2() failed: %s\n", strerror(errno));
      goto finish;
    }

    close(fd);

  }

  /* Create a new playback stream */
  if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, 
          "psychflow", &ss, NULL, NULL, &error))) {

    fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
    goto finish;

  }

  for (;;) {

    uint8_t buf[BUFSIZE];
    ssize_t r;

    // read the data.
    if((r = read(STDIN_FILENO, buf, sizeof(buf))) <= 0) {

      if(r == 0)
        break;

      fprintf(stderr, __FILE__": read() failed: %s \n", strerror(errno));
      goto finish;

    }

    //play the data to speaker.
    //the size_t cast is because ssize_t supports negative nums apparently.
    if(pa_simple_write(s, buf, (size_t) r, &error) < 0) {

      fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", 
          pa_strerror(error));

      goto finish;

    }

  }

  //ensures every sample was played
  if(pa_simple_drain(s, &error) < 0) {

    fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", 
        pa_strerror(error));
    goto finish;

  }

  ret = 0;

finish:

  if(s)
    pa_simple_free(s);

  return ret;

}
