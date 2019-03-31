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
    printf("error: not an AIFF file\n");
    return 0;
  }

  formBody *formBody = malloc(sizeof(formBody));
  if (!formBody) {
    printf("error while trying to read file\n");
    return 0;
  }
  fread(formBody, sizeof(formBody->formType), 1, fp);
  if(!streq(formBody->formType, "AIFF")) {
    printf("error: not an AIFF file\n");
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
    // parse ckHead


    // parse appropriate ckBody


    // if body has data[] -> malloc(ckSize), dump data there in form of char[ckSize] and add pointer to that data to ckBody


    // also put rest of data on heap
    fseek(fp, 1, SEEK_CUR);
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

  if (hide(aiffFile, textFile)) {
    printf("error while trying to hide message\n");
    return -1;
  }

  printf("successfully hidden message in aiff file (%s)\n", aiffPath);

  fclose(aiffFile);
  fclose(textFile);

  return 0;
}
