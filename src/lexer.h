#ifndef LEXER_H
#define LEXER_H

#include <string.h>
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

Token *newTokenStr(TokenType type, char *str);

Token *makeTwoCharToken(Lexer *lexer, TokenType type, char first);

void skipWhitespace(Lexer *lexer);

Token *NextToken(Lexer *lexer);

int isIdentStart(char c);

int isIdentChar(char c);

char *readIdentifier(Lexer *lexer);


char *readNumber(Lexer *lexer);

#endif