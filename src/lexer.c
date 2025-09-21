#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

void read_char(Lexer *lexer) {
  if (lexer->input[lexer->readPosition] == '\0') {
    lexer->ch = '\0';
  } else {
    lexer->ch = lexer->input[lexer->readPosition];
    lexer->position = lexer->readPosition;
    lexer->readPosition += 1;
  }
}

char peek_char(Lexer *lexer) {
  if (lexer->input[lexer->readPosition] == '\0') {
    return '\0';
  } else {
    return lexer->input[lexer->readPosition];
  }
}

// Don't forget free
Lexer *new_lexer(char *input) {
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
  read_char(lexer);
  return lexer;
}

// Don't forget free
Token *new_token(TokenType type, char ch) {
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
Token *new_token_str(TokenType type, char *str) {
  Token *tok = (Token *)malloc(sizeof(Token));
  if (tok == NULL) {
    fprintf(stderr, "Failed to allocate `tok` memory\n");
    exit(1);
  }
  tok->type = type;
  tok->Literal = str;
  return tok;
}

Token* make_two_char_token(Lexer *lexer, TokenType type, char first) {
    char *literal = (char*)malloc(3);
    if (literal == NULL) {
      fprintf(stderr, "Failed to allocate `literal` memory\n");
      exit(1);
    }
    literal[0] = first;
    literal[1] = lexer->ch;
    literal[2] = '\0';
    return new_token_str(type, literal);
}

void skip_white_space(Lexer *lexer) {
  while (isspace(lexer->ch)) {
    read_char(lexer);
  }
}

Token *next_token(Lexer *lexer) {
  Token* tok;
  TokenType type;
  skip_white_space(lexer);
  switch (lexer->ch) {
  case '=':
    if (peek_char(lexer) == '=') {
      char ch = lexer->ch;
      read_char(lexer);
      char *literal = (char *)malloc(3 * sizeof(char));
      if (literal == NULL) {
        fprintf(stderr, "Failed to allocate `literal` memory\n");
        exit(1);
      }
      type.index = EQ;
      type.value = "EQ";
      tok = make_two_char_token(lexer, type, ch);
    } else {
      type.index = ASSIGN;
      type.value = "ASSIGN";
      tok = new_token(type, lexer->ch);
    }
    break;
  case '+':
    type.index = PLUS;
    type.value = "PLUS";
    tok = new_token(type, lexer->ch);
    break;
  case '-':
    type.index = MINUS;
    type.value = "MINUS";
    tok = new_token(type, lexer->ch);
    break;
  case '!':
    if (peek_char(lexer) == '=') {
      char ch = lexer->ch;
      read_char(lexer);
      char *literal = (char *)malloc(3 * sizeof(char));
      if (literal == NULL) {
        fprintf(stderr, "Failed to allocate `literal` memory\n");
        exit(1);
      }
      type.index = NOT_EQ;
      type.value = "NOT_EQ";
      tok = make_two_char_token(lexer, type, ch);
    } else {
      type.index = BANG;
      type.value = "BANG";
      tok = new_token(type, lexer->ch);
    }
    break;
  case '*':
    type.index = ASTERISK;
    type.value = "ASTERISK";
    tok = new_token(type, lexer->ch);
    break;
  case '/':
    type.index = SLASH;
    type.value = "SLASH";
    tok = new_token(type, lexer->ch);
    break;
  case '<':
    type.index = LT;
    type.value = "LT";
    tok = new_token(type, lexer->ch);
    break;
  case '>':
    type.index = GT;
    type.value = "GT";
    tok = new_token(type, lexer->ch);
    break;
  case ';':
    type.index = SEMICOLON;
    type.value = "SEMICOLON";
    tok = new_token(type, lexer->ch);
    break;
  case ',':
    type.index = COMMA;
    type.value = "COMMA";
    tok = new_token(type, lexer->ch);
    break;
  case '(':
    type.index = LPAREN;
    type.value = "LPAREN";
    tok = new_token(type, lexer->ch);
    break;
  case ')':
    type.index = RPAREN;
    type.value = "RPAREN";
    tok = new_token(type, lexer->ch);
    break;
  case '{':
    type.index = LBRACE;
    type.value = "LBRACE";
    tok = new_token(type, lexer->ch);
    break;
  case '}':
    type.index = RBRACE;
    type.value = "RBRACE";
    tok = new_token(type, lexer->ch);
    break;
  case '\0':
    type.index = ENDOF;
    type.value = "eof"; 
    tok = new_token(type, lexer->ch);
    break;
  default:
    if (is_ident_start(lexer->ch)) {
      char *str = read_identifier(lexer);
      if (str == NULL) {
        type.index = ILLEGAL;
        type.value = "ILLEGAL";
        tok = new_token(type, lexer->ch);
        return tok;
      }
      type = look_up_ident(str);
      tok = new_token_str(type, str);
      return tok; 
    } else if (isdigit(lexer->ch)) {
      char *str = read_number(lexer);
      if (str == NULL) {
        type.index = ILLEGAL;
        type.value = "ILLEGAL";
        tok = new_token(type, lexer->ch);
        return tok;
      }
      if (strchr(str, '.') != NULL) {
        type.index = FLOAT;
        type.value = "FLOAT";
      } else {
        type.index = INT;
        type.value = "INT";
      }
      tok = new_token_str(type, str);
      return tok;
    } else {
      type.index = ILLEGAL;
      type.value = "ILLEGAL";
      tok = new_token(type, lexer->ch);
    }
    break;
  }
  read_char(lexer);
  return tok;
}

int is_ident_start(char c) {
  return isalpha(c) || c == '_';
}

int is_ident_char(char c) {
  return isalnum((unsigned char)c) || c == '_';
}

// Don't forget free
char *read_identifier(Lexer *lexer) {
  if (!is_ident_start(lexer->ch)) {
    return NULL;
  }

  int position = lexer->position;
  while (is_ident_char(lexer->ch)) {
    read_char(lexer);
  }

  int length = lexer->position - position;

  char *str = (char *)malloc(length + 1);
  if (str == NULL) {
    fprintf(stderr, "Failed to allocate `str` memory\n");
    exit(1);
  }

  memcpy(str, lexer->input + position, length);
  str[length] = '\0';
  return str;
}

// Don't forget free
char *read_number(Lexer *lexer) {
  int position = lexer->position;
  while (isdigit(lexer->ch)) {
    read_char(lexer);
  }

  if (lexer->ch == '.') {
    read_char(lexer);
    while (isdigit(lexer->ch)) {
      read_char(lexer);
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
