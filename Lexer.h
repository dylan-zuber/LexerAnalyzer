/*
Name: Dylan Zuber
Assignment: PA 3
Course/Semester: CS343/Fall2020
Lab Section: N/A
Sources Conculted: N/A
*/

// Method comments/descriptions are in the .cpp file
#ifndef _LEXER_H
#define _LEXER_H

#include <fstream>
#include <string>

// Character classes
#define LETTER 0
#define DIGIT 1
#define QUOTATION 3
#define DOT 4
#define UNKNOWN 99

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LEFT_CURLY 27
#define RIGHT_CURLY 28
#define STRING_LITERAL 40
#define FLOAT_LITERAL 41
#define RESERVED_WORD 50
#define COMMA 60
#define SEMI 100
#define END_OF_INPUT 1000

/* 
 * This is a C++ version of the lexer provided in the Sebesta
 * text in Section 4.2
 */
class Lexer {

private:
  std::string lexeme;    // The current lexeme
  int nextToken;         // The token code for the current lexeme
  int charClass;         // The character class for the current character
  char nextChar;         // The current character
  std::ifstream inputStream;  // The input stream

public:
  /**
   * Attempts to open the file.  If successful, sets the lexer to the beginning of the
   * file.  It does not begin reading the file until you call lex.  Initially, (before
   * calling lex() for the first time, getNextToken() will return END_OF_INPUT.
   */
  Lexer( const std::string & fileName );

  /**
   * Closes the input file.
   */
  ~Lexer();

  /**
   * Moves the lexer forward: reads the next token from the input file and stops
   * reading.  
   *
   * @return the token code for the token that was read, or END_OF_INPUT when the end of file
   *         has been reached.
   */
  int lex();

  /**
   * @return the most recent token code.
   */
  int getNextToken() const;

  /**
   * @return the lexeme corresponding to the most recently read token.
   */
  std::string getLexeme() const;

private:
  /**
   * Internal helper function that consumes characters from the input until a non-blank
   * character is reached.
   */
  void getNonBlank();

  /**
   * Gets the next character from the input file, determines the character class, and 
   * sets the variable charClass to the appropriate class for the character.
   */
  void getChar();

  /**
   * Adds the current character to the lexeme.
   */
  void addChar();
  
  /**
   * Helper function that is used when we suspect that a character is a single-character
   * lexeme.  This function returns the appropriate token code for the single-character lexeme.
   *
   * @return the token code, or END_OF_INPUT
   */
  int lookup(char ch);

  int buildString();

  void buildFloat();

  void error();

  bool isReservedWord();
};
#endif

