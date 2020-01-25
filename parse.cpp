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

#include <iostream>
#include <string>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

#include <unordered_set>
using std::unordered_set;

static unordered_set<int> FirstPROG = {VAR, WHILE, '['};
static unordered_set<int> FirstSTMTS = {VAR, WHILE, '['};
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
    FindSTMTS();

    if (PeekToken() == END) return true;

    Error("Program");
    return false;
}

//**************************************************************
// STMTS -> STMT STMTS
//           -> null
bool FindSTMTS()
{
    while (FindSTMT())
    {
        std::cout << "Found a statement\n";
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
        return FindSymbol(';');
    }
    //STMT -> while ( EXPR ) STMT
    else if (token == WHILE)
    {
        AdvanceToken();
        if (!FindSymbol('(')) return false;
        if (!FindEXPR()) return false;
        if (!FindSymbol(')')) return false;
        if (!FindSTMT()) return false;

        std::cout << "Found a statement\n";
        return true;
    }
    //STMT -> [ STMTS ]
    else if (token == '[')
    {
        AdvanceToken();
        FindSTMTS();
        return FindSymbol(']');
    }

    return false;
}

//**************************************************************
// EXPR -> OP EXPR EXPR
//          -> num
//          -> var
bool FindEXPR()
{
    int token = PeekToken();
    if (!IsIn(FirstEXPR, token)) return false;
    
    //EXPR -> OP EXPR EXPR
    if (FindOP())
    {
        if (!FindEXPR()) return false;
        if (!FindEXPR()) return false;

        return true;
    }
    //EXPR -> num
    else if (token == NUM)
    {
        AdvanceToken();
        return true;
    }
    //EXPR -> var
    else if (token == VAR)
    {
        AdvanceToken();
        return true;
    }

    return false;
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
