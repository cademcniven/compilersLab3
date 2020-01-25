//************************************************************
// utils.cpp
//
// Various utilities that are useful for top-down recursive-descent parsers
//
// Author: Phil Howard
// phil.howard@oit.edu
//

#include <iostream>
#include <string.h>
#include "lex.h"
#include "utils.h"

using std::cout;

// keep track of the last peeked token
static int g_token = -1;

//*******************************************
// print an error in a standard form.
void Error(std::string expecting)
{
    if (yytext != NULL && strlen(yytext) > 0)
        cout << "Found '" << yytext << "' when expecting a " << expecting;
    else
        cout << "Found End-Of-File when expecting a " << expecting;

    std::cout << " in line " << yylineno << std::endl;
}
//*******************************************
// Read the next token from the input
int GetToken()
{
    int token = g_token;
    if (token < 0) token = yylex();
    g_token = -1;

    return token;
}
//*******************************************
// Put the last-read token back into the input.
// Note: This only works as a one-level undo, not an N-level undo.
int UngetToken(int token)
{
    g_token = token;

    return g_token;
}

//*******************************************
// Look at the next token without consuming it
int PeekToken()
{
    if (g_token < 0) g_token = yylex();

    return g_token;
}
//*******************************************
// Read the next token from the input
int AdvanceToken()
{
    g_token = yylex();

    return g_token;
}
