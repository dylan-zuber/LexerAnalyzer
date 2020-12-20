/*
Name: Dylan Zuber
Assignment: PA 3
Course/Semester: CS343/Fall2020
Lab Section: N/A
Sources Conculted: N/A
*/

#include "Lexer.h"
using std::string;
#include <iostream>
#include <cctype>
#include <cstdlib>

/*
Constrcutor called to initialize the Lexer object
@param fileName string containing the name of the file to read input
*/
Lexer::Lexer( const string & fileName ): 
    nextToken{END_OF_INPUT}, charClass{UNKNOWN}, nextChar{' '} {
  inputStream.open( fileName.c_str(), std::ifstream::in ); 
  if( !inputStream ) {
    std::cout << "Unable to open file: " << fileName << "\n";
    exit(1);
  }
}

// Destrcutor for Lexer object
Lexer::~Lexer() {
  inputStream.close();
}

/*
Gives access to nextToken, the next token in the input stream
@return nextToken int value representing the token codes
*/
int Lexer::getNextToken() const {
  return nextToken;
}

/*
Gives access to the lexeme, the string value representing the next lexeme in the input string
@return lexeme string value representing a lexeme
*/
string Lexer::getLexeme() const {
  return lexeme;
}

/*
Takes a char value and calls the addChar() function for every case in a switch statement and changes the nextToken value to the token code corresponding to the parameter
@param ch character value representing a special character
@return int integer value representing the toke code corresponding to the parameter
*/
int Lexer::lookup(char ch)
{
  switch( ch )
  {
    case '(': 
      addChar(); 
      nextToken=LEFT_PAREN; 
      break;
    case ')': 
      addChar(); 
      nextToken=RIGHT_PAREN; 
      break;
    case '+': 
      addChar(); 
      nextToken=ADD_OP; 
      break;
    case '-': 
      addChar(); 
      nextToken=SUB_OP; 
      break;
    case '*': 
      addChar(); 
      nextToken=MULT_OP; 
      break;
    case '/': 
      addChar(); 
      nextToken=DIV_OP; 
      break;
    case '{':
      addChar();
      nextToken=LEFT_CURLY;
      break;
    case '}':
      addChar();
      nextToken=RIGHT_CURLY;
      break;
    case ';':
      addChar();
      nextToken=SEMI;
      break;
    case ',':
      addChar();
      nextToken=COMMA;
      break;
    case '=':
      addChar();
      nextToken=ASSIGN_OP;
      break;
    default:  
      addChar(); 
      nextToken=END_OF_INPUT; 
      break;
  }
  return nextToken;
}

// Add the global nextChar variable to the end of the global lexeme variable
void Lexer::addChar() {
  lexeme.push_back(nextChar);
}

/*
Updates the nextChar, the next character in the lexeme or to start a new lexeme, and changes to the charClass to the specific charatcer class
*/
void Lexer::getChar() {
  nextChar = inputStream.get();

  if( inputStream.good() ) {
    if( isalpha(nextChar) && nextChar != '.') charClass=LETTER;
    else if( isdigit(nextChar) || nextChar == '.') charClass=DIGIT;
    else if( nextChar == '"') {
      charClass=QUOTATION;
    } else {
      charClass=UNKNOWN; 
    }  
  } else {
    charClass = END_OF_INPUT;
  }
}

// Eliminates blank characters and gets the next non-blank character
void Lexer::getNonBlank() {
  while( isspace(nextChar) ) {
    getChar();
  }
}

/*
Creates a lexeme and returns the token code of the next token to be read
  will exit if certain cases if a string literal doesn't end in a quotation mark or a float doesn't have digits following a '.'
@return int integer for the corresponding next token code
*/
int Lexer::lex() {
  getNonBlank();
  lexeme = "";

  switch( charClass )
  {
    case LETTER: 
        addChar(); 
        getChar(); 
        while( charClass == LETTER || charClass == DIGIT ){ 
          addChar(); 
          getChar(); 
        }
        if(isReservedWord()) {
          nextToken=RESERVED_WORD;
        } else {
          nextToken=IDENT;
        } 
        break; // identifiers
    case DIGIT: 
      {
        bool flo = false;
        addChar(); 
        getChar(); 
        while( charClass == DIGIT ){ 
          if(lexeme.at(lexeme.length() - 1) == '.') {
            addChar();
            buildFloat();
            flo = true;
            break;
          }
          addChar(); 
          getChar(); 
        } 
        if(flo) {
          nextToken=FLOAT_LITERAL;
        } else {
           nextToken=INT_LIT; 
        }
        if(lexeme.at(lexeme.length() - 1) == '.') {
          std::cout << "Error :-( no digits following DOT" << '\n';
          exit(EXIT_FAILURE);
        }
        break; 
        
      }// integers
    case QUOTATION:
        nextToken=buildString();
        if(lexeme.at(lexeme.length() - 1) == '"') {
          std::cout << "Error :-( no second quotation" << '\n';
          exit(EXIT_FAILURE);
        }
        break;
    case UNKNOWN: 
        lookup(nextChar); 
        getChar(); 
        break; // Other characters
    case END_OF_INPUT: 
        nextToken=END_OF_INPUT; 
        lexeme = "END_OF_INPUT";
        break;
  }

  return nextToken;
}

/*
When called from lex(), builds a string (lexeme that begins with a quotation mark and ends with a quotation mark)
@return int integer for the token code of a string literal
*/
int Lexer::buildString() {
  addChar();
  getChar();
  while(charClass != QUOTATION) {
    addChar();
    getChar();
  }
  addChar();
  getChar();
  return STRING_LITERAL;
}

/*
When called from lex() builds a float literal value (zero or more digits followed by a '.' followed my one or more digits and an optional 'f' or 'F')
*/
void Lexer::buildFloat() {
  getChar();
  while (charClass == DIGIT) {
    addChar();
    getChar();
  }
  if (nextChar == 'f' || nextChar == 'F') {
    addChar();
    getChar();
  }
}

/*
Once the lexeme has been created made purely of letters, checks to see if the lexeme is a reserved word
@return bool true if lexeme is equal to a reserved word, false if not
*/
bool Lexer::isReservedWord() {
  bool result = false;
  if(lexeme == "if" ||
     lexeme == "else" ||
     lexeme == "for" || 
     lexeme == "do" ||
     lexeme == "while" || 
     lexeme == "switch" || 
     lexeme == "case" || 
     lexeme == "default" || 
     lexeme == "break" || 
     lexeme == "void" || 
     lexeme == "return") {
       result = true;
     }
     return result;
}
