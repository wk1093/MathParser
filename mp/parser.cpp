#include "parser.h"

void Parser::advance() {
    curr = lexer.next_token();
}

ExprNode *Parser::parseNumber() {
    auto *node = new ExprNode();
    node->type = NodeType_Number;
    node->number = std::stod(curr.lexeme);
    advance();
    return node;
}

ExprNode *Parser::parseInfixExpr(const Token& op, ExprNode *left) {
    auto *node = new ExprNode();
    switch (op.type) {
        case TokenType_Plus: node->type = NodeType_Add; break;
        case TokenType_Minus: node->type = NodeType_Sub; break;
        case TokenType_Star: node->type = NodeType_Mul; break;
        case TokenType_Slash: node->type = NodeType_Div; break;
        case TokenType_Caret: node->type = NodeType_Pow; break;
        default: node->type = NodeType_Error; printf("parseInfixExpr: ERR\n"); break;
    }
    node->binary.left = left;
    node->binary.right = parseExpression(precedenceLookup[op.type]);
    return node;
}

ExprNode *Parser::parseTerminalExpr() {
    ExprNode *node;
    if (curr.type == TokenType_Number) {
        node = parseNumber();
    } else if (curr.type == TokenType_OpenParen) {
        advance();
        node = parseExpression(Precedence_Min);
        if (curr.type == TokenType_CloseParen) {
            advance();
        }
    } else if (curr.type == TokenType_Plus) {
        advance();
        node = new ExprNode();
        node->type = NodeType_Positive;
        node->unary.operand = parseTerminalExpr();
    } else if (curr.type == TokenType_Minus) {
        advance();
        node = new ExprNode();
        node->type = NodeType_Negative;
        node->unary.operand = parseTerminalExpr();
    } else {
        node = new ExprNode();
        node->type = NodeType_Error;
        printf("parseTerminalExpr: ERR\n");
    }
    if (curr.type == TokenType_Number || curr.type == TokenType_OpenParen) {
        auto *next = new ExprNode();
        next->type = NodeType_Mul;
        next->binary.left = node;
        next->binary.right = parseExpression(Precedence_Factor);
        node = next;
    }
    return node;
}

ExprNode *Parser::parseExpression(Precedence prevP=Precedence_Min) {
    // Recursive
    ExprNode *left = parseTerminalExpr();
    Token currOp = curr;
    Precedence currP = precedenceLookup[currOp.type];
    while (currP != Precedence_Min) {
        if (prevP >= currP) {
            break;
        } else {
            advance();
            left = parseInfixExpr(currOp, left);
            currOp = curr;
            currP = precedenceLookup[currOp.type];
        }
    }
    return left;
}

Parser::Parser(const char* expression) : lexer(Lexer(expression)) {
    advance();
}