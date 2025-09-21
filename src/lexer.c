#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

void readChar(Lexer *lexer) {
  if (lexer->input[lexer->readPosition] == '\0') {
    lexer->ch = '\0';
  } else {
    lexer->ch = lexer->input[lexer->readPosition];
    lexer->position = lexer->readPosition;
    lexer->readPosition += 1;
  }
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
  if (lexer == NULL) {
    fprintf(stderr, "Failed to allocate `lexer` memory\n");
    exit(1);
  }
  lexer->input = (char *)malloc(strlen(input) + 1);
  if (lexer->input == NULL) {
    free(lexer);
    fprintf(stderr, "Failed to allocate `input` memory\n");
    exit(1);
  }
  strcpy(lexer->input, input);
  lexer->position = 0;
  lexer->readPosition = 0;
  lexer->ch = '\0';
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
    fprintf(stderr, "Failed to alllocate `str` memory\n");
    free(tok);
    exit(1);
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
    fprintf(stderr, "Failed to allocate `tok` memory\n");
    exit(1);
  }
  tok->type = type;
  tok->Literal = str;
  return tok;
}

Token* makeTwoCharToken(Lexer *lexer, TokenType type, char first) {
    char *literal = (char*)malloc(3);
    if (literal == NULL) {
      fprintf(stderr, "Failed to allocate `literal` memory\n");
      exit(1);
    }
    literal[0] = first;
    literal[1] = lexer->ch;
    literal[2] = '\0';
    return newTokenStr(type, literal);
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
        fprintf(stderr, "Failed to allocate `literal` memory\n");
        exit(1);
      }
      type.index = EQ;
      type.value = "EQ";
      tok = makeTwoCharToken(lexer, type, ch);
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
        fprintf(stderr, "Failed to allocate `literal` memory\n");
        exit(1);
      }
      type.index = NOT_EQ;
      type.value = "NOT_EQ";
      tok = makeTwoCharToken(lexer, type, ch);
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
    if (isIdentStart(lexer->ch)) {
      char *str = readIdentifier(lexer);
      if (str == NULL) {
        type.index = ILLEGAL;
        type.value = "ILLEGAL";
        tok = newToken(type, lexer->ch);
        return tok;
      }
      type = lookupIdent(str);
      tok = newTokenStr(type, str);
      return tok; 
    } else if (isdigit(lexer->ch)) {
      char *str = readNumber(lexer);
      if (str == NULL) {
        type.index = ILLEGAL;
        type.value = "ILLEGAL";
        tok = newToken(type, lexer->ch);
        return tok;
      }
      if (strchr(str, '.') != NULL) {
        type.index = FLOAT;
        type.value = "FLOAT";
      } else {
        type.index = INT;
        type.value = "INT";
      }
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

int isIdentStart(char c) {
  return isalpha(c) || c == '_';
}

int isIdentChar(char c) {
  return isalnum((unsigned char)c) || c == '_';
}

// Don't forget free
char *readIdentifier(Lexer *lexer) {
  if (!isIdentStart(lexer->ch)) {
    return NULL;
  }

  int position = lexer->position;
  while (isIdentChar(lexer->ch)) {
    readChar(lexer);
  }

  int length = lexer->position - position;

  char *str = (char *)malloc(length + 1);
  if (!str) return NULL;

  memcpy(str, lexer->input + position, length);
  str[length] = '\0';
  return str;
}

// Don't forget free
char *readNumber(Lexer *lexer) {
  int position = lexer->position;
  while (isdigit(lexer->ch)) {
    readChar(lexer);
  }

  if (lexer->ch == '.') {
    readChar(lexer);
    while (isdigit(lexer->ch)) {
      readChar(lexer);
    }
  }
  
  int len = lexer->position - position;

  char *num = (char *)malloc(len + 1);
  if (num == NULL) {
    fprintf(stderr, "Failed to allocate `num` memory\n");
    exit(1);
  }

  strncpy(num, lexer->input + position, len);
  num[len] = '\0';
  return num;
  
}
