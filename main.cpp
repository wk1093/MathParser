#include "mp/evaluate.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#define LIMIT 65536

// random expression generator
struct TreeNode {
    char op;
    f64 val;
    TreeNode *left;
    TreeNode *right;

    std::string toString() {
        if (op == ' ') {
            return std::to_string(val);
        } else {
            return "(" + left->toString() + " " + op + " " + right->toString() + ")";
        }
    }
};

f64 randf(f64 min, f64 max) {
    return min + (max - min) * (f64)rand() / RAND_MAX;
}

#define NUM_OPS 4
char ops[] = {'+', '-', '*', '/'};

TreeNode *newNode(char op, f64 val) {
    auto *node = new TreeNode;
    node->op = op;
    node->val = val;
    node->left = node->right = nullptr;
    return node;
}

TreeNode *newNode(char op, TreeNode *left, TreeNode *right) {
    auto *node = new TreeNode;
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

TreeNode *buildTree(i32 numNodes) {
    if (numNodes == 1) {
        return newNode(' ', randf(-100, 100));
    }

    // floor(numNodes / 2)
    i32 numLeft = numNodes >> 1;
    // ceil(numNodes / 2)
    i32 numRight = numNodes - numLeft;
    TreeNode *left = buildTree(numLeft);
    TreeNode *right = buildTree(numRight);

    f64 m = randf(0, NUM_OPS);
    char op = ops[(i32)m];
    return newNode(op, left, right);
}



int main() {
    srand(time(nullptr));
//    printf("Enter expression: ");
//    char buf[LIMIT] = {0};
//    fgets(buf, LIMIT, stdin);

    TreeNode *root = buildTree(20);
    std::string expr = root->toString();
    printf("expr: %s\n", expr.c_str());


    f64 result = evaluate(expr.c_str());
    printf("result: %f\n", result);

    return 0;
}
