#ifndef TRIE_H
#define TRIE_H
#define LETTERS 26

#include "mybool.h"

typedef struct Node *pTrie;

pTrie CreateTrie();
boolean TrieAddWord(pTrie trie, char *word);
void TrieDestroy(pTrie trie);
boolean TriePrint(pTrie trie, boolean reveresed);
#endif