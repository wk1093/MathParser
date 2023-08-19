#pragma once

#include <cstdio>
#include <cstdint>
#include <string>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef int32_t i32;



typedef u32 TokenType;
enum {
    TokenType_EOF, TokenType_Error,
    TokenType_Ident, TokenType_Number,
    TokenType_Plus, TokenType_Minus,
    TokenType_Star, TokenType_Slash,
    TokenType_Caret,
    TokenType_OpenParen,
    TokenType_CloseParen,
    TokenType_Max
};

typedef struct Token {
    TokenType type;
    std::string lexeme;
} Token;

bool is_whitespace(u8 c);

bool is_number(u8 c);

typedef struct Lexer {
    u8 *start;
    u8 *current;

    explicit Lexer(const char* expression);

    Token next_token();

    Token number();

    Token identifier();

    Token make_token(TokenType type);
} Lexer;