#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

void readChar(Lexer *lexer) {
  if (lexer->input[lexer->readPosition] == '\0') {
    lexer->ch = '\0';
  } else {
    lexer->ch = lexer->input[lexer->readPosition];
  }
  lexer->position = lexer->readPosition;
  lexer->readPosition += 1;
}

// Don't forget free
Lexer *NewLexer(char *input) {
  Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
  lexer->input = input;
  readChar(lexer);
  return lexer;
}

Token *newToken(TokenType type, char ch) {
  Token *tok = (Token *)malloc(sizeof(Token));
  if (tok == NULL) {
    return NULL; // out of memory
  }

  tok->type = type;
  char *str = (char *)malloc(2 * sizeof(char));
  if (str == NULL) {
    free(tok);
    return NULL; // out of memory
  }
  str[0] = ch;
  str[1] = '\0';
  tok->Literal = str;

  return tok;
}

Token *NextToken(Lexer *lexer) {
  Token* tok;
  TokenType type;
  switch (lexer->ch) {
  case '=':
    type.index = ASSIGN;
    type.value = "ASSIGN";
    tok = newToken(type, lexer->ch);
    break;
  case ';':
    type.index = SEMICOLON;
    type.value = "SEMICOLON";
    tok = newToken(type, lexer->ch);
    break;
  case '(':
    type.index = LPAREN;
    type.value = "LPAREN";
    tok = newToken(type, lexer->ch);
    break;
  case ')':
    type.index = RPAREN;
    type.value = "RPAREN";
    tok = newToken(type, lexer->ch);
    break;
  case ',':
    type.index = COMMA;
    type.value = "COMMA";
    tok = newToken(type, lexer->ch);
    break;
  case '+':
    type.index = PLUS;
    type.value = "PLUS";
    tok = newToken(type, lexer->ch);
    break;
  case '{':
    type.index = LBRACE;
    type.value = "LBRACE";
    tok = newToken(type, lexer->ch);
    break;
  case '}':
    type.index = RBRACE;
    type.value = "RBRACE";
    tok = newToken(type, lexer->ch);
    break;
  case '\0':
    type.index = ENDOF;
    type.value = "ENDOF"; 
    tok = newToken(type, lexer->ch);
    break;
  }
  readChar(lexer);
  return tok;
}