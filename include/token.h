#ifndef TOKEN_H__
#define TOKEN_H__

#define MAX_TOKEN_LEN 1500
#include <stdbool.h>

typedef struct token {
    struct token *next;
    bool is_tag;
    char str[1];
} Token;

static Token *create_token(size_t off_start, size_t off_end, bool is_tag, const char *str);
Token *token_get_all(const char *str);
int token_mark_all(const Token *root, char *dst, size_t dst_len, Trie *trie);
int token_free_all(Token *root);

#endif
