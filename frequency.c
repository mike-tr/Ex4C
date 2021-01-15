#include "reader.h"
#include "trie.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pInputReader reader = createReader();
    pTrie trie = CreateTrie();

    boolean all_good = False;
    while (ReaderDone(reader) == False) {
        all_good = TrieAddWord(trie, readSLNextWord(reader));
    }

    if (all_good) {
        if (argc > 1 && strcmp(argv[1], "r") == 0) {
            TriePrint(trie, True);
        } else {
            TriePrint(trie, False);
        }
    } else {
        printf("woops looks like there was an allocation problem... exiting...");
    }

    DestroyReader(reader);
    TrieDestroy(trie);
    return 0;
}
