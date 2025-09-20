#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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

char peekChar(Lexer *lexer) {
  if (lexer->input[lexer->readPosition] == '\0') {
    return '\0';
  } else {
    return lexer->input[lexer->readPosition];
  }
}

// Don't forget free
Lexer *NewLexer(char *input) {
  Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
  lexer->input = input;
  readChar(lexer);
  return lexer;
}

// Don't forget free
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

// Don't forget free
Token *newTokenStr(TokenType type, char *str) {
  Token *tok = (Token *)malloc(sizeof(Token));
  if (tok == NULL) {
    return NULL;
  }
  tok->type = type;
  tok->Literal = str;
  return tok;
}

void skipWhitespace(Lexer *lexer) {
  while (isspace(lexer->ch)) {
    readChar(lexer);
  }
}

Token *NextToken(Lexer *lexer) {
  Token* tok;
  TokenType type;
  skipWhitespace(lexer);
  switch (lexer->ch) {
  case '=':
    if (peekChar(lexer) == '=') {
      char ch = lexer->ch;
      readChar(lexer);
      char *literal = (char *)malloc(3 * sizeof(char));
      if (literal == NULL) {
        return NULL;
      }
      literal[0] = ch;
      literal[1] = lexer->ch;
      literal[2] = '\0';
      type.index = EQ;
      type.value = "EQ";
      tok = newTokenStr(type, literal);
    } else {
      type.index = ASSIGN;
      type.value = "ASSIGN";
      tok = newToken(type, lexer->ch);
    }
    break;
  case '+':
    type.index = PLUS;
    type.value = "PLUS";
    tok = newToken(type, lexer->ch);
    break;
  case '-':
    type.index = MINUS;
    type.value = "MINUS";
    tok = newToken(type, lexer->ch);
    break;
  case '!':
    if (peekChar(lexer) == '=') {
      char ch = lexer->ch;
      readChar(lexer);
      char *literal = (char *)malloc(3 * sizeof(char));
      if (literal == NULL) {
        return NULL;
      }
      literal[0] = ch;
      literal[1] = lexer->ch;
      literal[2] = '\0';
      type.index = NOT_EQ;
      type.value = "NOT_EQ";
      tok = newTokenStr(type, literal);
    } else {
      type.index = BANG;
      type.value = "BANG";
      tok = newToken(type, lexer->ch);
    }
    break;
  case '*':
    type.index = ASTERISK;
    type.value = "ASTERISK";
    tok = newToken(type, lexer->ch);
    break;
  case '/':
    type.index = SLASH;
    type.value = "SLASH";
    tok = newToken(type, lexer->ch);
    break;
  case '<':
    type.index = LT;
    type.value = "LT";
    tok = newToken(type, lexer->ch);
    break;
  case '>':
    type.index = GT;
    type.value = "GT";
    tok = newToken(type, lexer->ch);
    break;
  case ';':
    type.index = SEMICOLON;
    type.value = "SEMICOLON";
    tok = newToken(type, lexer->ch);
    break;
  case ',':
    type.index = COMMA;
    type.value = "COMMA";
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
    type.value = "eof"; 
    tok = newToken(type, lexer->ch);
    break;
  default:
    if (isalpha(lexer->ch)) {
      char *str = readIdentifier(lexer);
      type = lookupIdent(str);
      tok = newTokenStr(type, str);
      return tok; 
    } else if (isdigit(lexer->ch)) {
      char *str = readNumber(lexer);
      type.index = INT;
      type.value = "INT";
      tok = newTokenStr(type, str);
      return tok;
    } else {
      type.index = ILLEGAL;
      type.value = "ILLEGAL";
      tok = newToken(type, lexer->ch);
    }
    break;
  }
  readChar(lexer);
  return tok;
}

// Don't forget free
char *readIdentifier(Lexer *lexer) {
  int position = lexer->position;
  while (isalpha(lexer->ch)) {
    readChar(lexer);
  }
  
  int length = lexer->position - position;
  char *str = (char *)malloc(length + 1);
  if (str == NULL) {
      return NULL;
  }
  
  int i;
  for (i = 0; i < length; i++) {
    str[i] = lexer->input[position + i];
  }
  str[length] = '\0';
  return str; 
}

// Don't forget free
char *readNumber(Lexer *lexer) {
  int position = lexer->position;
  while (isdigit(lexer->ch)) {
    readChar(lexer);
  }
  
  int length = lexer->position - position;
  char *str = (char *)malloc(length + 1);
  if (str == NULL) {
      return NULL;
  }
  
  int i;
  for (i = 0; i < length; i++) {
    str[i] = lexer->input[position + i];
  }
  str[length] = '\0';
  return str; 
}
