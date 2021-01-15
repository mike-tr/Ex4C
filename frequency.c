#include "reader.h"
#include "trie.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pInputReader reader = createReader();
    pTrie trie = CreateTrie();

    while (ReaderDone(reader) == False) {
        TrieAddWord(trie, readSLNextWord(reader));
    }

    for (int i = 0; i < argc; i++) {
        printf("%d %s\n", i, argv[i]);
    }

    if (argc > 1 && strcmp(argv[1], "r") == 0) {
        printf("???");
        TriePrint(trie, True);
    } else {
        TriePrint(trie, False);
    }

    DestroyReader(reader);
    TrieDestroy(trie);
    return 0;
}
