#pragma once
//**************************************
// parse.h
//
// Declares parse routines for top-down recursive-descent parser
// Use in CST 320 Lab3
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

// Functions for finding non-terminals that are part of the calc grammar
// The functions return true if the non-terminal was found, false otherwise.
//
// These functions can be called recursively to any depth supported by 
// available memory.
bool FindPROG();
bool FindSTMTS();
bool FindSTMT();
bool FindEXPR();
bool FindOP();
bool FindSymbol(char symbol);
