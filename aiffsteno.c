#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "int.h"
#include "typedefs.h"

unsigned long int fsize(FILE *fp) {
  unsigned long int current = ftell(fp);
	fseek(fp, 0, SEEK_END);
	unsigned long int fileSize = ftell(fp);
	fseek(fp, current, SEEK_SET);
	return fileSize;
}

// char *data;
// unsigned long int SSNDStart = 0;
//
// void readAIFF(FILE *aiffFile) {
//   data = malloc(fsize(aiffFile));
//   for (int i = 0; i < fsize(aiffFile); i++) {
//     fread(data + i, sizeof(char), 1, aiffFile);
//   }
//   int i = 3;
//   while (!(data[i - 3] == 'S' && data[i - 2] == 'S' && data[i-1] == 'N' && data[i] == 'D')) {
//     i++;
//   }
//   SSNDStart = i -3;
// }

chunk *parseAIFF(FILE *fp) {
  fseek(fp, 0, SEEK_SET);

  chunk *formChunk = malloc(sizeof(chunk));
  if (!formChunk) {
    printf("error while trying to read file\n");
    return 0;
  }

  fread(&(formChunk->head), sizeof(ckHead), 1, fp);
  if (!streq(formChunk->head.ckID, "FORM")) {
    printf("error: not a valid AIFF file\n");
    return 0;
  }

  fread(&(formChunk->body.form), sizeof(formChunk->body.form.formType), 1, fp);
  if(!streq(formChunk->body.form.formType, "AIFF")) {
    printf("error: not a valid AIFF file\n");
    return 0;
  }

  int numChunks = 0;
  const unsigned long int size = fsize(fp);
  while (ftell(fp) < size) {

    chunk *chunk = malloc(sizeof(chunk));
    if (!chunk) {
      printf("error while trying to read file\n");
      return 0;
    }
    fread(&(chunk->head), sizeof(ckHead), 1, fp);

    if (streq(chunk->head.ckID, "COMM")) {
      printf("found a comm chunk\n");
      fread(&(chunk->body.comm), sizeof(commBody), 1, fp);
    } else if (streq(chunk->head.ckID, "SSND")) {
      printf("found a ssnd chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "MARK")) {
      printf("found a mark chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "INST")) {
      printf("found a inst chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "MIDI")) {
      printf("found a midi chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "AESD")) {
      printf("found a aesd chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "APPL")) {
      printf("found a appl chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "COMT")) {
      printf("found a comt chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "NAME")) {
      printf("found a name chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "AUTH")) {
      printf("found a auth chunk\n");
      free(chunk);
    } else if (streq(chunk->head.ckID, "(c) ")) {
      printf("found a (c)  chunk\n");
    } else if (streq(chunk->head.ckID, "ANNO")) {
      printf("found a anno chunk\n");
      free(chunk);
    } else {
      printf("didn't recognize chunk\n");
      free(chunk);
      continue;
      // printf("error: not a valid AIFF file\n");
      // return 0;
    }

    // if body has data[] -> malloc(ckSize), dump data there in form of char[ckSize] and add pointer to that data to ckBody

    // add pointer to chunk in formChunk->chunks
    formChunk->body.form.chunks[numChunks] = chunk;
    numChunks++;
  }

  return formChunk;
}

int hide(FILE *aiffFile, FILE *textFile) {
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

  chunk *formChunk = parseAIFF(aiffFile);
  if (!formChunk) {
    return -1;
  }
  printf("ckID: %s\nckSize: %s\nformType: %s\n", formChunk->head.ckID, formChunk->head.ckSize, formChunk->body.form.formType);
  printf("chunks[1]: %p\nnumSampleFrames: %x\n", formChunk->body.form.chunks[1], flipEndianess(((chunk *)(formChunk->body.form.chunks[1]))->body.comm.numSampleFrames));
  // readAIFF(aiffFile);
  // printf("SSNDStart: %lu\n", SSNDStart);

  if (hide(aiffFile, textFile)) {
    printf("error while trying to hide message\n");
    return -1;
  }

  printf("successfully hidden message in aiff file (%s)\n", aiffPath);

  fclose(aiffFile);
  fclose(textFile);

  return 0;
}
