#include <string.h>
#include "token.h"


TokenType keywords[] = {
    {LET, "LET"},
    {FUNCTION, "FUNCTION"},
    {TRUE, "TRUE"},
    {FALSE, "FALSE"},
    {IF, "IF"},
    {ELSE, "ELSE"},
    {RETURN, "RETURN"},
};

TokenType lookupIdent(char *identifier) {
    TokenType tokenType;

    if (identifier == NULL) {
        tokenType.index = ILLEGAL;
        tokenType.value = "ILLEGAL";
        return tokenType;
    }

    int len = sizeof(keywords) / sizeof(TokenType);
    for (int i = 0; i < len; i++) {
        if (strcmp(keywords[i].value, identifier) == 0) {
            tokenType.index = keywords[i].index;
            tokenType.value = keywords[i].value;
            return tokenType;
        }
    }
    tokenType.index = IDENT;
    tokenType.value = "IDENT";
    return tokenType;
}
