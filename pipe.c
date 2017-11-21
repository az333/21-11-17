#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

int main () {
  srand(time(NULL));

  int READ = 0;
  int WRITE = 1;

  int parent[2], child[2];

  pipe(parent);
  pipe(child);

  //forked off child
  int parentprocess = fork();


  if (parentprocess) {
    close(parent[READ]);
    close(child[WRITE]);
    int i = rand() % 10;
    write(parent[WRITE], &i, sizeof(i));
    printf("[parent] sending: %d\n", i);
   } else {
     close(parent[WRITE]);
     close(child[READ]);
     int i;
     read(parent[READ], &i, sizeof(i));
     printf("[child] doing maths on: %d\n", i);
     i = i*i + 12;
     write(child[WRITE], &i, sizeof(i));
   }
  if (parentprocess) {
    int i;
    read(child[READ], &i, sizeof(i));
    printf("[parent] received: %d\n", i);
  }
}
