/*
Name: Dylan Zuber
Assignment: PA 3
Course/Semester: CS343/Fall2020
Lab Section: N/A
Sources Conculted: N/A
*/
#include "Lexer.h"
#include <iostream>

/*
Driver program for a Lexical Analyzer (Lexer.cpp, Lexer.h)
 - prints out lexical tokens in parenthesis followed by the lexeme it corresponds to 
*/
int main() {
  
  // Create the Lexer object
  Lexer lex{ "test.txt" };

  do {
    
    int tok = lex.lex();   // Retrieve next token
    std::string text = lex.getLexeme();  // Get corresponding lexeme

    // Print the token code and lexeme
    std::cout << "(" << tok << ") " << text << "\n";

  } while( lex.getNextToken() != END_OF_INPUT );

}