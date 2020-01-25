%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Cade McNiven 
// cade.mcniven@oit.edu
//
// Date: Jan. 23 2020
//

    // comment out the other line to generate debug info
#include "tokens.h"
#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

%%

"{".*"}"
[()+\-*/=;\[\]]               DO_RETURN(yytext[0]);
"end"                       DO_RETURN(END);
"while"                     DO_RETURN(WHILE);
[0-9]+                      DO_RETURN(NUM);
[a-zA-Z][a-zA-Z0-9]*        DO_RETURN(VAR);
[ \n\t\r]
.                           DO_RETURN(JUNK);

%%

int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

