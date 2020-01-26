//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab3
//
// Authors: Phil Howard, Cade McNiven
// phil.howard@oit.edu
// cade.mcniven@oit.edu
//

#define EOF 0

#include <iostream>
#include <string>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

#include <unordered_set>
using std::unordered_set;

static unordered_set<int> FirstSTMT = {VAR, WHILE, '['};
static unordered_set<int> FirstEXPR = {NUM, VAR, '+', '-', '*', '/'};
static unordered_set<int> FirstOP = {'+', '-', '*', '/'};

//**************************************************************
static bool IsIn(unordered_set<int>& set, int value)
{
    auto found = set.find(value);
    if (found != set.end()) return true;
    return false;
}

//**************************************************************
// Handles error correction for everything other than having
// a space ']' in the code
void CorrectError()
{
    int token = PeekToken();
    while (token != END && token != EOF &&
           token != ';' && token != ']')
    {
        AdvanceToken();
        token = PeekToken();
    }

    if (token == ';')
        AdvanceToken();
}

//**************************************************************
// Checks if symbol == PeekToken()
bool FindSymbol(char symbol)
{
    int token = PeekToken();
    if (token != symbol)
    {
        std::string error = "'";
        error += symbol;
        error += "'";
        Error(error);
        return false;
    }

    AdvanceToken();
    return true;
}

//**************************************************************
// PROG -> STMTS end
bool FindPROG()
{
    int token = PeekToken();
    //Call FindSTMTS until we find "end" or eof
    while (token != END && token != EOF)
    {
        FindSTMTS();
        token = PeekToken();

        //This happens if there is an extra ]
        //somewhere in the file
        if (token != END && token != EOF)
        {
            Error("Statment");
            AdvanceToken();
            token = PeekToken();
        }
    }

    if (token == END) return true;

    Error("Program");
    return false;
}

//**************************************************************
// STMTS -> STMT STMTS
//           -> null
bool FindSTMTS()
{
    int token = PeekToken();
    while (token != END && token != EOF && token != ']')
    {
        if (!FindSTMT()) 
            CorrectError();

        token = PeekToken();
    }

    return true;
}

//**************************************************************
// STMT -> var = EXPR ;
//          -> while ( EXPR ) STMT
//          -> [ STMTS ]
bool FindSTMT()
{
    int token = PeekToken();
    if (!IsIn(FirstSTMT, token)) return false;

    //STMT -> var = EXPR ;
    if (token == VAR)
    {
        AdvanceToken();
        if (!FindSymbol('=')) return false;
        if (!FindEXPR()) return false;
        if (!FindSymbol(';')) return false;
    }
    //STMT -> while ( EXPR ) STMT
    else if (token == WHILE)
    {
        AdvanceToken();
        if (!FindSymbol('(')) return false;
        if (!FindEXPR()) return false;
        if (!FindSymbol(')')) return false;
        if (!FindSTMT()) return false;
    }
    //STMT -> [ STMTS ]
    else if (token == '[')
    {
        AdvanceToken();
        FindSTMTS();
        if (!FindSymbol(']')) return false;
    }

    std::cout << "Found a statement\n";
    return true;
}

//**************************************************************
// EXPR -> OP EXPR EXPR
//          -> num
//          -> var
bool FindEXPR()
{
    int token = PeekToken();
    if (!IsIn(FirstEXPR, token))
    {
        Error("EXPR");
        return false;
    }
    
    //EXPR -> OP EXPR EXPR
    if (FindOP())
    {
        if (!FindEXPR()) return false;
        if (!FindEXPR()) return false;
    }
    //EXPR -> num
    //     -> var
    else if (token == NUM || token == VAR)
        AdvanceToken();

    return true;
}

//**************************************************************
// OP -> +
//      -> -
//      -> *
//      -> /
bool FindOP()
{
    if (!IsIn(FirstOP, PeekToken())) return false;
    
    AdvanceToken();
    return true;
}
