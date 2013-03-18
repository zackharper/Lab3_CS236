#ifndef TokenType_h
#define TokenType_h

#include <string>

/**
 * The token types declared as an enumerated type.
 */
enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, MULTIPLY, ADD, COLON, COLON_DASH, STRING, SCHEMES, FACTS, RULES, QUERIES, ID, COMMENT, WHITESPACE, UNDEFINED, END, NUL};
    
    /**
     * Converts a token type to a string.
     * 
     * Parameters: tokenType -- the token type to be converted to a string.
     * PreCondition: none
     * Postcondition: result = the string representation of the token type which
     *                         looks exactly like its TokenType name.
     */
    std::string TokenTypeToString(TokenType tokenType);
#endif
