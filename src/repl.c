#include "repl.h"

void StartRepl(FILE *in, FILE *out) {
    char buf[1024];

    while (1) {
        fprintf(out, "%s", PROMPT);
        fflush(out);

        if (!fgets(buf, sizeof(buf), in)) {
            return; 
        }

        buf[strcspn(buf, "\n")] = 0;

        Lexer *lexer = NewLexer(buf);
        if (lexer == NULL) {
            return;
        }
        Token *tok = NextToken(lexer);

        while (tok->type.index != ENDOF) {
            fprintf(out, "INDEX: %d, VALUE: %s, LITERAL: %s\n", tok->type.index, tok->type.value, tok->Literal);
            free(tok->Literal);
            free(tok);
            tok = NextToken(lexer);
        }
        free(tok->Literal);
        free(tok);
        free((char *)lexer->input);
        free(lexer);
    }
}
