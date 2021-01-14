#include "reader.h"
#include <stdio.h>
#include <stdlib.h>

#define OFFSET 'A' - 'a'

typedef struct InputReader {
    char *word;
    int size;
    boolean done;
} * pInputReader, Reader;

void mallocFailed() {
    printf("something went wrong malloc failed");
    // exit(1);
}

pInputReader createReader() {
    pInputReader reader = (pInputReader)malloc(sizeof(Reader));
    if (reader == NULL) {
        mallocFailed();
        return NULL;
    }
    reader->word = (char *)malloc(sizeof(char) * WORD);
    if (reader->word == NULL) {
        free(reader);
        mallocFailed();
        return NULL;
    }
    reader->done = False;
    reader->size = WORD;
    return reader;
}

boolean validateSize(pInputReader reader, int size) {
    if (size > reader->size) {
        reader->size *= 2;
        char *tmp = (char *)realloc(reader->word, reader->size);
        if (tmp == NULL) {
            DestroyReader(reader);
            printf("ops... something went wrong failed to realloc exiting");
            return False;
        }
        reader->word = tmp;
        return True;
    }
    return False;
}

boolean ReaderDone(pInputReader reader) {
    return reader->done;
}

char *readSLNextWord(pInputReader reader) {
    char *word = reader->word;
    char c = getchar();
    int size = 0;

    while (c != EOF) {
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            if (size > 0) {
                *word = '\0';
                return reader->word;
            }
        } else {
            if (c >= 'A' && c <= 'Z') {
                c -= OFFSET;
            }

            if (c >= 'a' && c <= 'z') {
                *word = c;
                word++;
                size++;
                if (validateSize(reader, size + 1)) {
                    word = reader->word + size;
                }
            }
        }
        c = getchar();
    }
    *word = '\0';
    reader->done = True;
    return reader->word;
}

void DestroyReader(pInputReader reader) {
    if (reader == NULL) {
        return;
    }
    free(reader->word);
    free(reader);
}