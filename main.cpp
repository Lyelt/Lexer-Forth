#include "tools.hpp"
#include "Lexer.hpp"
#include "Token.hpp"

int main()
{
    banner();
    string inFileName;
    cout << "Enter the name of the file to lex." << endl;
    cin >> inFileName;

    Lexer lex( inFileName );
    lex.lex();
    lex.print();

    bye();
    return 0;
}
