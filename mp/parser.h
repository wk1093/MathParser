#pragma once

#include <unordered_map>
#include "lexer.h"

typedef u32 ExprNodeType;
enum {
    NodeType_Error,
    NodeType_Number,
    NodeType_Positive,
    NodeType_Negative,
    NodeType_Add,
    NodeType_Sub,
    NodeType_Mul,
    NodeType_Div,
    NodeType_Pow
};

typedef struct ExprNode {
    ExprNodeType type;

    union {
        f64 number;
        struct { ExprNode* operand; } unary;
        struct { ExprNode* left; ExprNode* right; } binary;
    };
} ExprNode;

typedef u32 Precedence;
enum {
    Precedence_Min,
    Precedence_Term,
    Precedence_Factor,
    Precedence_Exp,
    Precedence_Max
};

//static Precedence precedenceLookup[TokenType_Max] = {
//        [TokenType_Plus] = Precedence_Term,
//        [TokenType_Minus] = Precedence_Term,
//        [TokenType_Star] = Precedence_Factor,
//        [TokenType_Slash] = Precedence_Factor,
//        [TokenType_Caret] = Precedence_Exp
//};

// ^ C way of doing it
// v C++ way of doing it
static std::unordered_map<TokenType, Precedence> precedenceLookup = {
        {TokenType_Plus, Precedence_Term},
        {TokenType_Minus, Precedence_Term},
        {TokenType_Star, Precedence_Factor},
        {TokenType_Slash, Precedence_Factor},
        {TokenType_Caret, Precedence_Exp}
};

typedef struct Parser {
    Lexer lexer;
    Token curr;

    explicit Parser(const char* expression);

    void advance();

    ExprNode *parseNumber();

    ExprNode *parseInfixExpr(const Token& op, ExprNode *left);

    ExprNode *parseTerminalExpr();

    ExprNode *parseExpression(Precedence prevP);

} Parser;