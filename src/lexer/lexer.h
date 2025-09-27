#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include "../token/token.h"

typedef struct {
  char *input;
  int position;
  int readPosition;
  char ch;
} Lexer;

void read_char(Lexer *lexer);

char peek_char(Lexer *lexer);

Lexer *new_lexer(char *input);

Token *new_token(TokenType type, char ch);

Token *new_token_str(TokenType type, char *str);

Token *make_two_char_token(Lexer *lexer, TokenType type, char first);

void skip_white_space(Lexer *lexer);

Token *next_token(Lexer *lexer);

int is_ident_start(char c);

int is_ident_char(char c);

char *read_identifier(Lexer *lexer);

char *read_number(Lexer *lexer);

#endif