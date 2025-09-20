#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
  char *input;
  int position;
  int readPosition;
  char ch;
} Lexer;

void readChar(Lexer *lexer);
Lexer *NewLexer(char *input);
Token *newToken(TokenType type, char ch);
Token *NextToken(Lexer *lexer);

#endif