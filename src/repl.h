#ifndef REPL_H
#define REPL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#define PROMPT ">> "

void StartRepl(FILE *in, FILE *out);

#endif