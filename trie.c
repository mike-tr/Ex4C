#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTERS 26
#define WORD 100

typedef struct Node {
    char letter;                    // the node letter
    long unsigned int count;        // number of words that contain this node
    long unsigned int ends;         // number of words that ends with that node
    struct Node *children[LETTERS]; // the children of this node
} * pNode, Node;

pTrie CreateTrie() {
    pTrie trie = (pTrie)malloc(sizeof(Node));
    if (trie == NULL) {
    }
    trie->letter = '\0';
    trie->count = 0;
    trie->ends = 0;
    for (int i = 0; i < LETTERS; i++) {
        trie->children[i] = NULL;
    }
    return trie;
}

pNode CreateNode(char letter) {
    pNode node = (pNode)malloc(sizeof(Node));
    if (node == NULL) {
        printf("something went wrong! coudn't create Node");
        return NULL;
    }
    node->count = 0;
    node->letter = letter;
    node->ends = 0;
    for (int i = 0; i < LETTERS; i++) {
        node->children[i] = NULL;
    }
    return node;
}

boolean TrieAddWord(pTrie trie, char *word) {
    // we assume the word doesn't contain any letter that is not from a to z lowercase.
    if (*word == 0) {
        return True;
    }

    trie->count++;
    pNode node = trie;
    while (*word) {
        int index = *word - 'a';
        if (node->children[index]) {
            node = node->children[index];
            node->count++;
        } else {
            node->children[index] = CreateNode(*word);
            node = node->children[index];
            if (node == NULL) {
                return False;
            }
            node->count++;
        }
        word++;
    }
    node->ends++;
    return True;
}

void NodeDestroy(pNode node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < LETTERS; i++) {
        NodeDestroy(node->children[i]);
    }
    free(node);
}

void TrieDestroy(pTrie trie) {
    NodeDestroy(trie);
}

boolean NodeExtractWord(pNode node, char **words, int *counts, int *index, const char *parent, int size) {
    char *word = (char *)malloc(sizeof(char) * (size + 2));
    if (word == NULL) {
        return False;
    }

    if (size > 0) {
        strcpy(word, parent);
    }
    word[size] = node->letter;
    word[size + 1] = '\0';

    if (node->ends > 0) {
        words[*index] = word;
        counts[*index] = node->ends;
        (*index)++;
    }

    pNode current = NULL;
    for (int i = 0; i < LETTERS; i++) {
        current = node->children[i];
        if (current != NULL) {
            NodeExtractWord(current, words, counts, index, word, size + 1);
        }
    }

    if (node->ends == 0) {
        // if the number of words ending with this prefix is 0
        // then we are not using this prefix and can discard it.
        // a.k.a we will forget the point to it after closing this fucntion so we must free it.
        free(word);
    }
    return True;
}

char **ExtractWords(pTrie trie, int counts[]) {
    char **words = (char **)calloc(sizeof(char *), trie->count);
    if (words == NULL) {
        return NULL;
    }
    pNode current = NULL;
    int index = 0;
    for (int i = 0; i < LETTERS; i++) {
        current = trie->children[i];
        if (current != NULL) {
            NodeExtractWord(current, words, counts, &index, NULL, 0);
        }
    }
    return words;
}

void freeArrs(char **words, int *count, int size) {
    free(count);
    for (int i = 0; i < size; i++) {
        if (words[i] != NULL) {
            free(words[i]);
        }
    }
    free(words);
}

boolean TriePrint(pTrie trie, boolean reveresed) {
    int *counts = (int *)calloc(sizeof(int), trie->count);
    if (counts == NULL) {
        printf("something went wrong while prining error in allocation");
        return False;
    }
    char **words = ExtractWords(trie, counts);
    if (words == NULL) {
        printf("something went wrong while prining error in allocation");
        return False;
    }

    if (reveresed) {
        for (int i = trie->count - 1; i >= 0; i--) {
            if (counts[i] > 0) {
                printf("%s %d\n", words[i], counts[i]);
            }
        }
    } else {
        for (int i = 0; i < trie->count; i++) {
            if (counts[i] > 0) {
                printf("%s %d\n", words[i], counts[i]);
            }
        }
    }

    freeArrs(words, counts, trie->count);
    return True;
}
