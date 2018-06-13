#ifndef TOKEN_H__
#define TOKEN_H__

#define MAX_TOKEN_LEN 1024
#include <stdbool.h>

typedef struct token {
    struct token *next;
    bool is_tag;
    char str[1];
} Token;

Token *create_token(size_t off_start, size_t off_end, bool is_tag, const char *str);
Token *token_get_all(const char *str);
int token_mark_all(Token *root, char *dst, Trie *trie);

#endif
