#include "evaluate.h"

f64 evaluateExpr(ExprNode *node) {
    switch(node->type) {
        case NodeType_Number: {
            return node->number;
        } break;
        case NodeType_Positive: {
            return evaluateExpr(node->unary.operand);
        } break;
        case NodeType_Negative: {
            return -evaluateExpr(node->unary.operand);
        } break;
        case NodeType_Add: {
            return evaluateExpr(node->binary.left) + evaluateExpr(node->binary.right);
        } break;
        case NodeType_Sub: {
            return evaluateExpr(node->binary.left) - evaluateExpr(node->binary.right);
        } break;
        case NodeType_Mul: {
            return evaluateExpr(node->binary.left) * evaluateExpr(node->binary.right);
        } break;
        case NodeType_Div: {
            return evaluateExpr(node->binary.left) / evaluateExpr(node->binary.right);
        } break;
        case NodeType_Pow: {
            return std::pow(evaluateExpr(node->binary.left), evaluateExpr(node->binary.right));
        } break;
        default: {
            printf("evaluateExpr: ERR\n");
            return 0;
        } break;
    }
}

void printTree(ExprNode *tree, u32 depth = 0) {
    for(u32 i = 0; i < depth; i++) {
        if (i == depth - 1) {
            printf(" |-");
        } else {
            printf(" | ");
        }
    }
    switch(tree->type) {
        case NodeType_Number: {
            printf("Number: %f\n", tree->number);
        } break;
        case NodeType_Positive: {
            printf("Positive:\n");
            printTree(tree->unary.operand, depth + 1);
        } break;
        case NodeType_Negative: {
            printf("Negative:\n");
            printTree(tree->unary.operand, depth + 1);
        } break;
        case NodeType_Add: {
            printf("Add:\n");
            printTree(tree->binary.left, depth + 1);
            printTree(tree->binary.right, depth + 1);
        } break;
        case NodeType_Sub: {
            printf("Sub:\n");
            printTree(tree->binary.left, depth + 1);
            printTree(tree->binary.right, depth + 1);
        } break;
        case NodeType_Mul: {
            printf("Mul:\n");
            printTree(tree->binary.left, depth + 1);
            printTree(tree->binary.right, depth + 1);
        } break;
        case NodeType_Div: {
            printf("Div:\n");
            printTree(tree->binary.left, depth + 1);
            printTree(tree->binary.right, depth + 1);
        } break;
        case NodeType_Pow: {
            printf("Pow:\n");
            printTree(tree->binary.left, depth + 1);
            printTree(tree->binary.right, depth + 1);
        } break;
        default: {
            printf("printTree: ERR\n");
        } break;
    }
}

f64 evaluate(const char *expression, bool print_tree) {
    Parser parser(expression);
    ExprNode *tree = parser.parseExpression(Precedence_Min);
    if (print_tree) printTree(tree);
    return evaluateExpr(tree);
}
