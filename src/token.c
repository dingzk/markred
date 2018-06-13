#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "trie.h"
#include "token.h"

//#define DEBUG

Token *create_token(size_t off_start, size_t off_end, bool is_tag, const char *str) 
{
    size_t len, copylen;
    if (off_end < off_start) {
        return NULL;
    }
    copylen = off_end - off_start + 1;
    Token *node = (Token *)malloc(sizeof(Token) + copylen);
    node->is_tag = is_tag;
    strncpy(node->str, str + off_start, copylen);
    *(node->str + copylen) = '\0';
    node->next = NULL;

    return node;
}

Token *token_get_all(const char *str)
{
    size_t str_len = strlen(str);
    int off_start = 0, off_end = 0; 
    Token *root = create_token(0, 0, 0, str);
    Token *node, *curnode = root;
    bool flag = false, is_tag;
    int i;
    for (i = 0; i < str_len; i++) {
        off_end = i;
        if (off_end == str_len - 1) {
            flag = true;
            is_tag = 0;
        }
        if (str[i] == '<' && i != 0) {
            flag = true;
            is_tag = 0;
            off_end -= 1;
        } else if (str[i] == '>') {
            flag = true;
            is_tag = 1;
        }
        if (flag) {
            //printf("%d, %d, %d\n", off_start, off_end, is_tag);
            node = create_token(off_start, off_end, is_tag, str);
            if (node != NULL) {
                curnode->next = node;
                curnode = node;
            }
            flag = false;
            off_start = off_end + 1;
        }
    }

    return root;
}

int token_mark_all(Token *root, char *dst, Trie *trie)
{
    if (root == NULL) {
        return 1;
    } 
    Token *cur = root->next;
    Token *tmp;
    char *target;
    bool is_tag;
    char mark[MAX_TOKEN_LEN] = {0};
    while (cur != NULL) {
        //printf("str: %s, is_tag : %d\n", cur->str, cur->is_tag);
        target = cur->str;
        is_tag = cur->is_tag;
        if (!is_tag) {
            match_all(target, mark, trie);
            strcat(dst, mark);
            memset(mark, 0, MAX_TOKEN_LEN);
        } else {
            strcat(dst, target);
        }
        tmp = cur->next;
        free(cur);
        cur = tmp;
    } 

    return 0;
}

/*

#ifdef DEBUG
int main(void)
{
    Trie *root = create_trie('`', 0);

    create_trie("部队烧烤壮行宴", root);
    create_trie("部队", root);
    create_trie("烧烤", root);
    create_trie("壮行", root);
    char dst[20480] = {0};
    char *target = "【部队烧烤“壮行宴”了解一下<img src=\"//img.t.sinajs.cn/t4/appstyle/expression/ext/normal/fa/2018new_chanzui_org.png\" title=\"[馋嘴]\" alt=\"[馋嘴]\" class=\"face\" /><img src=\"//img.t.sinajs.cn/t4/appstyle/expression/ext/normal/fa/2018new_chanzui_org.png\" title=\"[馋嘴]\" alt=\"[馋嘴]\" class=\"face\" />】6月9日，正值周末，中部战区空军地导某营官兵齐聚篮球场，一场别开生面的烧烤晚会即将拉开序幕。在该营即将接换新装、赴华北某地执行任务之际，为让大家在紧张训练之余更好放松身心，这顿广大官兵期盼已久的集体“壮行宴”应运而生。（杨杰 任俊吉 谭巳成 ";

    Token *t = token_get_all(target);
    token_mark_all(t, dst, root);
    printf("%s\n", dst);

    free_trie(root);

    return 0;
}
#endif
*/
