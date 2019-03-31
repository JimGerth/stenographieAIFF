typedef struct {
  char offset[4];
  char blockSize[4];
  char *soundData;
} ssndBody;

typedef struct {
  char numChannels[2];
  unsigned int numSampleFrames;
  char sampleSize[2];
  char sampleRate[10];
} commBody;

typedef struct {
  char formType[4];
  void *chunks[10];
} formBody;

typedef union {
  formBody form;
  commBody comm;
  ssndBody ssnd;
} ckBody;

typedef struct {
  char ckID[4];
  char ckSize[4];
} ckHead;

typedef struct {
  ckHead head;
  ckBody body;
} chunk;
