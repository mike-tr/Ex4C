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

    if (argc > 1 && strcmp(argv[1], "r") == 0) {
        TriePrint(trie, True);
    } else {
        TriePrint(trie, False);
    }

    DestroyReader(reader);
    TrieDestroy(trie);
    return 0;
}
