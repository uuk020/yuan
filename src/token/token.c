#include <string.h>
#include "token.h"


TokenType look_up_ident(char *identifier) {
    TokenType tokenType;

    if (identifier == NULL) {
        tokenType.index = ILLEGAL;
        tokenType.value = "ILLEGAL";
        return tokenType;
    }

    if (strcmp(identifier, "fn") == 0) {
        tokenType.index = FUNCTION;
        tokenType.value = "FUNCTION";
    } else if (strcmp(identifier, "let") == 0) {
        tokenType.index = LET;
        tokenType.value = "LET";
    } else if (strcmp(identifier, "true") == 0) {
        tokenType.index = TRUE;
        tokenType.value = "TRUE";
    } else if (strcmp(identifier, "false") == 0) {
        tokenType.index = FALSE;
        tokenType.value = "FALSE";
    } else if (strcmp(identifier, "if") == 0) {
        tokenType.index = IF;
        tokenType.value = "IF";
    } else if (strcmp(identifier, "else") == 0) {
        tokenType.index = ELSE;
        tokenType.value = "ELSE";
    } else if (strcmp(identifier, "return") == 0) {
        tokenType.index = RETURN;
        tokenType.value = "RETURN";
    } else {
        tokenType.index = IDENT;
        tokenType.value = "IDENT";
    }
    return tokenType;
}
