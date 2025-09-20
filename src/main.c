#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main() {
  char *input = "=+(){},;";
  Lexer *lexer = NewLexer(input);
  for (int i = 0; i < 9; i++) {
    Token *tok = NextToken(lexer);
    printf("%s %s\n", tok->type.value, tok->Literal);
    free(tok);
  }
  free(lexer);
  return 0;
}
