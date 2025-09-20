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

char peekChar(Lexer *lexer);

Lexer *NewLexer(char *input);

Token *newToken(TokenType type, char ch);

Token *NextToken(Lexer *lexer);

char *readIdentifier(Lexer *lexer);

void skipWhitespace(Lexer *lexer);

char *readNumber(Lexer *lexer);

#endif