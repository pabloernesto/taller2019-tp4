#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <stdio.h>

int main(){
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir ("folder")) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      printf ("%s\n", ent->d_name);
      std::cout << ent->d_name; 
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return 1;
  }
  return 0;
}