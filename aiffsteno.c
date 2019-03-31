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

chunk *parseAIFF(FILE *fp) {
  fseek(fp, 0, SEEK_SET);

  ckHead *formHead = malloc(sizeof(ckHead));
  if (!formHead) {
    printf("error while trying to read file\n");
    return 0;
  }
  fread(formHead, sizeof(ckHead), 1, fp);
  if (!streq(formHead->ckID, "FORM")) {
    printf("error: not a valid AIFF file\n");
    return 0;
  }

  formBody *formBody = malloc(sizeof(formBody));
  if (!formBody) {
    printf("error while trying to read file\n");
    return 0;
  }
  fread(formBody, sizeof(formBody->formType), 1, fp);
  if(!streq(formBody->formType, "AIFF")) {
    printf("error: not a valid AIFF file\n");
    return 0;
  }

  ckBody *formBodyWrapper = malloc(sizeof(ckBody));
  formBodyWrapper->form = *formBody;
  free(formBody);

  chunk *formChunk = malloc(sizeof(chunk));
  formChunk->head = *formHead;
  free(formHead);
  formChunk->body = *formBodyWrapper;
  free(formBodyWrapper);

  while (ftell(fp) < fsize(fp)) {

    chunk *chunk = malloc(sizeof(chunk));
    if (!chunk) {
      printf("error while trying to read file\n");
      return 0;
    }
    fread(&(chunk->head), sizeof(ckHead), 1, fp);
    if (streq(chunk->head.ckID, "COMM")) {
      printf("found a comm chunk\n");
      fread(&(chunk->body), sizeof(commBody), 1, fp);
    // } else if (streq(chunk->head.ckID, "SSND")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "MARK")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "INST")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "MIDI")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "AESD")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "APPL")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "COMT")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "NAME")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "AUTH")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "(c) ")) {
    //   free(chunk);
    // } else if (streq(chunk->head.ckID, "ANNO")) {
    //   free(chunk);
    } else {
      free(chunk);
      continue;
      // printf("error: not a valid AIFF file\n");
      // return 0;
    }

    // if body has data[] -> malloc(ckSize), dump data there in form of char[ckSize] and add pointer to that data to ckBody

    // add pointer to chunk in formChunk->chunks
    formChunk->body.form.chunks[0] = chunk;
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
  printf("chunks[0]: %p\nnumSampleFrames: %x\n", formChunk->body.form.chunks[0], flipEndianess(((chunk *)(formChunk->body.form.chunks[0]))->body.comm.numSampleFrames));

  if (hide(aiffFile, textFile)) {
    printf("error while trying to hide message\n");
    return -1;
  }

  printf("successfully hidden message in aiff file (%s)\n", aiffPath);

  fclose(aiffFile);
  fclose(textFile);

  return 0;
}
