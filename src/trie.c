#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

//#define DEBUG

inline Trie *create_trie(uint8_t key, uint8_t is_end)
{
    Trie *node = (Trie *)malloc(sizeof(Trie));
    if (node == NULL) {
        printf("malloc error for Trie\n");
        return NULL;
    }
    node->key = key;
    node->is_end = is_end;
    memset(node->next, 0, TRIE_NODE_MAX * sizeof(sizeof(Trie *)));

    return node;
}

void append_trie(char *str, Trie *root)
{
    Trie *cur = root;
    char key;
    uint8_t offset;
    size_t len = strlen(str);
    if (cur == NULL) {
        return ;
    }
    for (int i = 0; i < len; i++) {
        key = *(str + i);
        key = isalpha(key) ? tolower(key) : key; // convert alpha to lower
        offset = (uint8_t)key;
        if (cur->next[offset] == NULL) {
            cur->next[offset] = create_trie(key, 0); 
        }
        cur = cur->next[offset];
        if (i == len -1) {
            cur->is_end = 1;
        }
    }
}

int match(const char *str, char *matched, Trie *root)
{
    Trie *cur = root;
    size_t len = strlen(str);
    uint8_t offset = 0;
    char key;
    for (int i = 0; i < len; i++) {
        key = *(str + i);
        offset = isalpha(key) && isupper(key) ? tolower(key) : key;
        if (cur->next[offset] == NULL) {
            break;
        }
        cur = cur->next[offset];
        if (cur->is_end) {
            strncpy(matched, str, i + 1); // get the largest matched
        }
    }

    return strlen(matched) > 0 ? 1 : 0;
}

int match_all(const char *str, char *str_marked, Trie *root)
{
    size_t str_len = strlen(str), matched_len = 0;
    if (str_len <= 0) {
        return -1;
    }
    char matched[MAX_TRIE_WORD_LEN] = {0};
    char *marked = str_marked;
    int i = 0;
    while (i < str_len) {
        if (match(str + i, matched, root) == 1) {
            matched_len = strlen(matched); 
            //printf("matched:%s\n", matched);
            COPY_AND_EXPAND(marked, MARK_TAG_OPEN, MARK_TAG_OPEN_LEN)
            COPY_AND_EXPAND(marked, str + i, matched_len)
            COPY_AND_EXPAND(marked, MARK_TAG_CLOSE, MARK_TAG_CLOSE_LEN)
            i += matched_len;
            memset(matched, 0, sizeof(char) * MAX_TRIE_WORD_LEN);
        } else {
            *marked++ = str[i++];
        }
    }

    return 0;
}

void free_trie(Trie *cur)
{
    if (cur == NULL) {
        return;    
    }
     //printf("%d\n", cur->is_end);
    //printf("%d\n", cur->is_end);
    Trie **next = cur->next;
    for (int i = 0; i < TRIE_NODE_MAX; i++) {
        free_trie(*next++);
    }
    free(cur);
}

/*
#ifdef DEBUG
int main(void)
{
    Trie *root = create_trie('`', 0);
    
    append_trie("部队烧烤壮行宴", root);
    append_trie("部队", root);
    append_trie("烧烤", root);
    append_trie("壮行", root);
    append_trie("宴", root);
    char *target = "部队烧烤壮行晏abcdsjdjfjsdfoiajo";

    char marked[10240] = {0};
    match_all(target, marked, root);
    printf("%s\n", marked);
    free_trie(root);

    return 0;
}
#endif
*/
