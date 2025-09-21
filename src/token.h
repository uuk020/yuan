#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  ILLEGAL,
  ENDOF,

  IDENT,
  INT,
  FLOAT,

  ASSIGN,
  PLUS,
  MINUS,
  BANG,
  ASTERISK,
  SLASH,

  LT,
  GT,

  EQ,
  NOT_EQ,

  SEMICOLON,
  COMMA,

  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,

  FUNCTION,
  LET,
  TRUE,
  FALSE,
  IF,
  ELSE,
  RETURN,

} TokenKeywords;

typedef struct {
  TokenKeywords index;
  char* value;
} TokenType;

typedef struct {
  TokenType type;
  char *Literal;
} Token;

TokenType lookupIdent(char *ident);

#endif