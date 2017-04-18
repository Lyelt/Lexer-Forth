#include "tools.hpp"
#include "Token.hpp"
#include "Lexer.hpp"

// Normal Token Constructor.
Token::Token ( TokenT t, string s )
    {
        type = t;
        text = s;
    }
