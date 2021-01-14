#include "reader.h"
#include "trie.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    pInputReader reader = createReader();
    pTrie trie = CreateTrie();

    while (ReaderDone(reader) == False) {
        TrieAddWord(trie, readSLNextWord(reader));
    }

    TriePrint(trie, False);
    printf("\nnow in reverse\n\n");
    TriePrint(trie, True);

    DestroyReader(reader);
    TrieDestroy(trie);
    return 0;
}
