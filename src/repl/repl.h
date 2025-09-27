#ifndef REPL_H
#define REPL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lexer/lexer.h"
#define PROMPT ">> "

void start_repl(FILE *in, FILE *out);

#endif