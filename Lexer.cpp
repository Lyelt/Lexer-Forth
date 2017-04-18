#include "Lexer.hpp"
#include "tools.hpp"
#define OUTFILE "output.txt"

Lexer::Lexer(string inFileName) : inFile(inFileName), outFile (OUTFILE)
{
    if (!inFile) fatal ("Could not open file for input.");
    if (!outFile) fatal ("Could not open 'output.txt' for output.");

    outFile << "Nicholas Ghobrial - Forth Lexer" << endl;
    outFile << "Lexing File: " << inFileName << endl;
    outFile << "Comments:" << endl;
}

//------------------------------------------------------------------------------

void Lexer::lex()
{
    char ch;
    int j = 0;
    int k = 0;
    string buffer = "";
    int state = 0;

    while (inFile >> noskipws >> ch)
    {
        // Add a character to the buffer and increment j
        buffer += ch;
        ++j;
        // If the character is whitespace and the state is 0, start processing
        // using the current contents of the buffer
        if (iswspace(ch) && state == 0){
            state = start( buffer, j );
        }
        // The state that returns from start tells us what type of token it was
        switch (state) {
            case (5):   // A token was just added.
                buffer = "";
            case (2):   // Whole line comment
                if (ch == '\n') {
                    outFile << buffer << endl;
                    buffer = "";
                    state = 0;
                    j = 0;
                }
                break;
            case (3):   // Block comment
                if (ch == ')') {
                    outFile << buffer << endl; // should be buffer[something]
                    buffer = "";
                    state = 0;
                    j = 0;
                }
                break;
            case (4):   // A string was found
                // Keep reading until we find a matching "
                if (ch == '"'){
                    acquiringString( buffer, j );
                    buffer = "";
                    state = 0;
                    j = 0;
                }
            default: break;
        }
    }
}

//------------------------------------------------------------------------------

void Lexer::print()
{
    outFile << "-------------------------------" << endl;
    for( int i=0; i < symbolTable.size(); ++i )
    {
        outFile << symbolTable[i].getText() << endl;
    }
}

//------------------------------------------------------------------------------

//Helper functions for each of the four states

int Lexer::start( string buffer, int j )
{
    // Eg. buffer == "\ ", j == 2, therefore the currentChar is '\' and
    // nextChar is '_'
    char currentChar = buffer[j-2];
    char nextChar = buffer[j-1];
    // If this is a whole line comment...
    if ( currentChar == '\\' && iswspace(nextChar)){
        return 2;
    }
    // If it is a block comment...
    else if (currentChar == '(' && iswspace(nextChar)){
        return 3;
    }
    // Otherwise, it belongs in the symbol table.
    else {
        // As long as it is not just a space
        if (!iswspace(currentChar)){
            // Find out what type of symbol it is
            return acquiringSymbol( buffer, j );
        }
        // If we are reading just a space, return 0 and keep going
        else return 0;
    }
}
//------------------------------------------------------------------------------
int Lexer::acquiringSymbol( string buffer, int j )
{
    // Eg. buffer == "fib_", j == 4, currentChar == b, nextChar == '_'
    char currentChar = buffer[j-2];
    char nextChar = buffer[j-1];
    // If the token is a ." you have found a STRING
    if (currentChar == '.' && nextChar == '"'){
        Token t(WORD, ".\"");
        symbolTable.push_back(t);
        return 4; // Found a string word
    }

    // Otherwise, find out what it is.
    else {
        foundToken( buffer, j );
        return 5; // Found a different token
    }
}
//------------------------------------------------------------------------------
void Lexer::acquiringString( string buffer, int j )
{
    Token t(STRING, buffer);
    cout << "String Found: " << buffer << endl;
    symbolTable.push_back(t);
}
//------------------------------------------------------------------------------
void Lexer::foundToken( string buffer, int j )
{
    // Get rid of the space, so we are just looking at the word itself
    buffer.pop_back();
    // If value is already in the map, increment
    if ( tokenMap.find(buffer) != tokenMap.end() ){
        tokenMap[buffer] += 1;
    }

    // Otherwise, add it
    else {
        bool isNum = isNumber(buffer);

        if (isNum) {
            Token t(NUMBER, buffer);
            cout << "Number Found: " << buffer << endl;
            symbolTable.push_back(t);
        }
        else {
            Token t(WORD, buffer);
            cout << "Token Word Found: " << buffer << endl;
            symbolTable.push_back(t);
        }
        tokenMap[buffer] = 1;
    }
}
//------------------------------------------------------------------------------
// Return false if any character in str is not a digit
bool Lexer::isNumber (string str)
{
    for (int i=0; i<strlen(str.c_str()); ++i){
        char c = str[i];
        if (!isdigit(c)) return false;
    }
    return true;
}
