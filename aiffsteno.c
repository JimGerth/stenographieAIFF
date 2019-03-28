#include <stdio.h>

int hide(FILE *aiffFile, FILE *textFile) {
  return 1;
}

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("correct usage: aiffsteno [path to .aiff file] [path to .txt file to hide]\n");
    return -1;
  }

  char *aiffPath = *(argv + 1);
  FILE *aiffFile;
  if (!fopen(aiffPath, "rb")) {
    printf("error: problem with opening aiff file\n");
    return -1;
  }

  char *textPath = *(argv + 2);
  FILE *textFile;
  if (!fopen(textPath, "r")) {
    printf("error: problem with opening text file\n");
    return -1;
  }

  if (!hide(aiffFile, textFile)) {
    printf("successfully hidden message in aiff file (%s)\n", aiffPath);
  } else {
    printf("error while trying to hide message\n");
    return -1;
  }

  fclose(aiffFile);
  fclose(textFile);

  return 0;
}
