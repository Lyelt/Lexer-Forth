#ifndef LEXER_HPP_INCLUDED
#define LEXER_HPP_INCLUDED
#include "tools.hpp"
#include "Token.hpp"
#include <map>

class Lexer
{
    private:
        ifstream inFile;
        ofstream outFile;
        vector<Token> symbolTable;
        map<string, int> tokenMap;

    public:
        Lexer( string );
        void lex( );
        void print( );
        int start( string, int );
        int acquiringSymbol( string, int );
        void acquiringString( string, int );
        void foundToken( string, int );
        bool isNumber ( string );

};

#endif // LEXER_HPP_INCLUDED
