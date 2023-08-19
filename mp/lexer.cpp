#include "lexer.h"

bool is_whitespace(u8 c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

bool is_number(u8 c) {
    return c >= '0' && c <= '9';
}


Token Lexer::next_token() {
    while (is_whitespace(*current)) current += 1;
    start = current;
    if (*current == '\0') return make_token(TokenType_EOF);
    current++;
    switch (*(current - 1)) {
        case '+': return make_token(TokenType_Plus);
        case '-': return make_token(TokenType_Minus);
        case '*': return make_token(TokenType_Star);
        case '/': return make_token(TokenType_Slash);
        case '^': return make_token(TokenType_Caret);

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return number();

        case '(': return make_token(TokenType_OpenParen);
        case ')': return make_token(TokenType_CloseParen);

        default: {
            if (isalpha(*current)) return identifier();
            return make_token(TokenType_Error);
        }
    }
}

Token Lexer::number() {
    while (is_number(*current)) current++;
    if (*current == '.') {
        current++;
        while (is_number(*current)) current++;
    }
    return make_token(TokenType_Number);
}

Token Lexer::identifier() {
    while (isalpha(*current)) current++;
    return make_token(TokenType_Ident);
}

Token Lexer::make_token(TokenType type) {
    Token token;
    token.type = type;
    token.lexeme = std::string((char *)start, (char *)current);
    return token;
}

Lexer::Lexer(const char *expression) {
    start = (u8 *)expression;
    current = start;
}
