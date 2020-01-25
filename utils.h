#pragma once
//**********************************************
// Various utilities that might be useful for a top-down recursive-descent p
// parser
//
// Author: Phil Howard
//

// Print an error message in a standard format
void Error(std::string expecting);

// PeekToken looks at a token without advancing the input
// AdvanceToken advances the input and then does a Peek
// NOTE: These routines are incompatible with Get/Unget
int PeekToken();
int AdvanceToken();

// GetToken gets the next token from the input
// UngetToken returns a token to the input. 
//      NOTE: the put-back is only one deep. You can only unget a single token
// NOTE: These routines are incompatible with Peek/Advance
int GetToken();
int UngetToken(int token);
