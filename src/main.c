#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include "repl.h"

int test() {
  typedef struct {
    char *type;
    char *literal;
  } TestToken;

  char *input = "let five = 5; "\
    "let ten = 10; "\
    "let add = fn(x, y) {"\
    "  x + y; "\
    "};"\
    "let result = add(five, ten); "\
    "!-/*5; "\
    "5 < 10 > 5; "\
    " if (5 < 10) { "\
    "  return true; "\
    "} else {      "\
    "  return false;"\
    " }             "\
    " 10 == 10; "\
    " 10 != 9;";

  TestToken tokens[] = {
    {"LET", "let"},
    {"IDENT", "five"},
    {"ASSIGN", "="},
    {"INT", "5"},
    {"SEMICOLON", ";"},
    {"LET", "let"},
    {"IDENT", "ten"},
    {"ASSIGN", "="},
    {"INT", "10"},
    {"SEMICOLON", ";"},
    {"LET", "let"},
    {"IDENT", "add"},
    {"ASSIGN", "="},
    {"FUNCTION", "fn"},
    {"LPAREN", "("},
    {"IDENT", "x"},
    {"COMMA", ","},
    {"IDENT", "y"},
    {"RPAREN", ")"},
    {"LBRACE", "{"},
    {"IDENT", "x"},
    {"PLUS", "+"},
    {"IDENT", "y"},
    {"RBRACE", "}"},
    {"SEMICOLON", ";"},
    {"LET", "let"},
    {"IDENT", "result"},
    {"ASSIGN", "="},
    {"IDENT", "add"},
    {"LPAREN", "("},
    {"IDENT", "five"},
    {"COMMA", ","},
    {"IDENT", "ten"},
    {"RPAREN", ")"},
    {"SEMICOLON", ";"},
    {"BANG", "!"},
    {"MINUS", "-"},
    {"SLASH", "/"},
    {"ASTERISK", "*"},
    {"INT", "5"},
    {"SEMICOLON", ";"},
    {"INT", "5"},
    {"LT", "<"},
    {"INT", "10"},
    {"GT", ">"},
    {"INT", "5"},
    {"SEMICOLON", ";"},
    {"IF", "if"},
    {"LPAREN", "("},
    {"INT", "5"},
    {"LT", "<"},
    {"INT", "10"},
    {"RPAREN", ")"},
    {"LBRACE", "{"},
    {"RETURN", "return"},
    {"TRUE", "true"},
    {"SEMICOLON", ";"},
    {"RBRACE", "}"},
    {"ELSE", "else"},
    {"LBRACE", "{"},
    {"RETURN", "return"},
    {"FALSE", "false"},
    {"SEMICOLON", ";"},
    {"RBRACE", "}"},
    {"INT", "10"},
    {"EQ", "=="},
    {"INT", "10"},
    {"SEMICOLON", ";"},
    {"INT", "10"},
    {"NOT_EQ", "!="},
    {"INT", "9"},
    {"SEMICOLON", ";"},
    {"ENDOF", ""},
  };

  Lexer *lexer = new_lexer(input);
  int len = sizeof(tokens) / sizeof(TestToken);
  for (int i = 0; i < len + 1; i++) {
    Token *tok = next_token(lexer);
    printf("%s %s\n", tok->type.value, tok->Literal);

    free(tok->Literal);
    tok->Literal = NULL;
    free(tok);
    tok = NULL;
  }
  free(lexer);
  lexer = NULL;
  return 0;
}

int main() {
  struct passwd *pw = getpwuid(getuid());
  if (!pw) {
    fprintf(stderr, "Failed to get username\n");
    exit(1);
  }

  printf("Hello %s! This is the yuan programming language!\n", pw->pw_name);
  printf("Feel free to type in commands\n");

  start_repl(stdin, stdout);
  return 0;
}