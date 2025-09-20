#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  ILLEGAL,
  ENDOF,

  IDENT,
  INT,

  ASSIGN,
  PLUS,

  COMMA,
  SEMICOLON,

  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,

  FUNCTION,
  LET,

} TokenKeywords;

typedef struct {
  TokenKeywords index;
  char* value;
} TokenType;

typedef struct {
  TokenType type;
  char *Literal;
} Token;

#endif