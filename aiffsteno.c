#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "int.h"

typedef struct {
  char ckID[4];
  unsigned int ckSize;
} ckHead;

typedef struct {
  ckHead ckHead;
  char formType[4];
  char chunks[];
} FORM;

int hide(FILE *aiffFile, FILE *textFile) {

  FORM formChunk;
  fread(&formChunk, 12, 1, aiffFile);

  printf("chunkID == 'FORM'? ");
  if (streq(formChunk.ckHead.ckID, "FORM")) { printf("yes!\n"); } else { printf("no!\n"); }

  printf("formType == 'AIFF'? ");
  if (streq(formChunk.formType, "AIFF")) { printf("yes!\n"); } else { printf("no!\n"); }

  printf("size of file: %u\n", flipEndianess(formChunk.ckHead.ckSize) + 8);

  return -1;
}

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("correct usage: aiffsteno [path to .aiff file] [path to .txt file to hide]\n");
    return -1;
  }

  char *aiffPath = *(argv + 1);
  FILE *aiffFile = fopen(aiffPath, "rb");
  if (!aiffFile) {
    printf("error: problem with opening aiff file\n");
    return -1;
  }

  char *textPath = *(argv + 2);
  FILE *textFile = fopen(textPath, "r");
  if (!textFile) {
    printf("error: problem with opening text file\n");
    return -1;
  }

  if (hide(aiffFile, textFile)) {
    printf("error while trying to hide message\n");
    return -1;
  }

  printf("successfully hidden message in aiff file (%s)\n", aiffPath);

  fclose(aiffFile);
  fclose(textFile);

  return 0;
}
