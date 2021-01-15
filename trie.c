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

/**
 * public method for the user to create the root for the trie 
 **/
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

/**
 * create a new Node, where letter would represent this crossroad
 * returns the node if all godd, otherwise returns NULL 
 **/
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

/**
 * given a word to add, add it to the trie
 * this method is iterative, as we dont really need recursion in here
 * if allocation of children fails in any point returns false,
 * 
 * otherwise all good return true 
 **/
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
            // a.k.a this node doesn't exist so create a new one.
            node->children[index] = CreateNode(*word);
            node = node->children[index];
            if (node == NULL) {
                return False;
            }
            node->count++;
        }
        word++;
        // node->ends in general holds how many words ends with that prefix, but we use it in trie
        // as a counter to the "longest word".
        trie->ends++;
    }
    node->ends++;
    return True;
}

/**
 * hidden method that destroys the node and all its children by recursion 
 **/
void NodeDestroy(pNode node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < LETTERS; i++) {
        NodeDestroy(node->children[i]);
    }
    free(node);
}

/**
 * this is the public method that the used see from outside 
 **/
void TrieDestroy(pTrie trie) {
    NodeDestroy(trie);
}

/**
 * by recursion go over all the nodes in order,
 * and add the word to the array if the node represent a words ending.
 * 
 * in anycase pass the substring of the node to the children
 * and if the word not used free it at the end. 
 **/
boolean NodeExtractWord(pNode node, char **words, int *counts, int *index, char *parent, int size) {
    parent[size] = node->letter;
    parent[size + 1] = '\0';

    if (node->ends > 0) {
        // when we see that this prefix is a standalone word we want to save it in the array
        // hance we create a new string with this exact number of characters and it would hold the right word reference
        char *word = (char *)malloc(sizeof(char) * (size + 2));
        if (word == NULL) {
            return False;
        }
        strcpy(word, parent);

        words[*index] = word;
        counts[*index] = node->ends;
        (*index)++;
    }

    pNode current = NULL;
    for (int i = 0; i < LETTERS; i++) {
        current = node->children[i];
        if (current != NULL) {
            if (NodeExtractWord(current, words, counts, index, parent, size + 1) == False) {
                return False;
            }
        }
    }

    return True;
}

/**
 * free the array of strings and all the strings in the array 
 **/
void freeWords(char **words, int size) {
    // loop over all the words in the string array and free everyword that is not null
    for (int i = 0; i < size; i++) {
        if (words[i] != NULL) {
            free(words[i]);
        }
    }
    free(words);
}

/**
 * create the Array of strings
 * and populate it with the relative strings 
 **/
char **ExtractWords(pTrie trie, int counts[]) {
    char **words = (char **)calloc(sizeof(char *), trie->count);
    if (words == NULL) {
        return NULL;
    }

    // this is a temporary word that would hold the prefix of the parent node
    // hence we always know what was the "ending" of the word that our parent had.
    char *word = (char *)calloc(sizeof(char), trie->ends + 1);
    if (word == NULL) {
        free(words);
        return NULL;
    }
    pNode current = NULL;
    int index = 0;
    for (int i = 0; i < LETTERS; i++) {
        current = trie->children[i];
        if (current != NULL) {
            if (NodeExtractWord(current, words, counts, &index, word, 0) == False) {
                freeWords(words, trie->count);
                free(word);
                return NULL;
            }
        }
    }
    // when we finish we dont need the temp word anymore so free it.
    free(word);
    return words;
}

/**
 * this method prints the content of the trie, we instantiate an array of strings,
 * the array would at most contain  trie->count words that is trie->count counts how many words are in the trie,
 * but not unqiue words.
 * */
boolean TriePrint(pTrie trie, boolean reveresed) {
    // this overall sdtructure is as follows
    // we would create an array of strings and add each unique string in there
    // we also create an array of "counts" that represent how much of each word in the trie

    // overall we can dump the idea of the array and just print it mid flight,
    // but the downside would be that we would basically need to create a method for each possible sort we want
    // as right now we would have an array, and then we can sort it in anyway ( its already sorted from small to big )
    // so we can just print the array in reverse.
    int *counts = (int *)calloc(sizeof(int), trie->count);
    if (counts == NULL) {
        printf("something went wrong while prining error in allocation\n");
        return False;
    }
    char **words = ExtractWords(trie, counts);
    if (words == NULL) {
        free(counts);
        printf("something went wrong while prining error in allocation\n");
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

    free(counts);
    freeWords(words, trie->count);
    return True;
}
