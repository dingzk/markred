#ifndef TRIE_H__
#define TRIE_H__
#define TRIE_NODE_MAX 256
#define MAX_TRIE_WORD_LEN 200
#define MARK_TAG_OPEN "<em class=\"s-color-red\">"
#define MARK_TAG_OPEN_LEN 24
#define MARK_TAG_CLOSE "</em>"
#define MARK_TAG_CLOSE_LEN 5

#define COPY_AND_EXPAND(dst, src, len) do { \
    strncpy(dst, src, len);\
    dst += len;\
    *dst = '\0';\
} while(0);

#define STR_COPY(dst, src, len) do { \
    strncpy(dst, src, len);\
    *(dst + len) = '\0';\
} while(0);

typedef struct trie {
    uint8_t key;
    uint8_t is_end;
    struct trie *next[TRIE_NODE_MAX];
} Trie;

Trie *create_trie(uint8_t key, uint8_t is_end);
void append_trie(char *str, Trie *root);
static int match(const char *str, char *matched, Trie *root);
int match_all(const char *str, char *str_marked, size_t marked_len, Trie *root);
void free_trie(Trie *trie);

#endif
