/**
 * this structure would be responsible for reading small letters and "remembering" the last word
 * that we have recieved.
 * 
 * also we would ignore anything that is not latters and convert big letters to small letters.
 * we would assume words are max 100 characters long if we need more we can always use realloc 
**/
#ifndef READER_H
#define READER_H
#define WORD 100

#include "mybool.h"

typedef struct InputReader *pInputReader;

pInputReader createReader();
char *readSLNextWord(pInputReader reader);
boolean ReaderDone(pInputReader reader);
void DestroyReader(pInputReader reader);

#endif