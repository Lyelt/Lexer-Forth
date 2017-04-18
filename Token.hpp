#pragma once
#include "tools.hpp"

enum TokenT {
    UNKNOWN,
    NUMBER,
    WORD,
    STRING
};

class Token
{
    private:
        TokenT type;
        string text;

    public:
        Token ( ) { } // Empty constructor for creating arrays.
        Token( TokenT, string );
        string getText ( ) { return text; }
};
