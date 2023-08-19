#pragma once
#include "lexer.h"
#include "parser.h"
#include <cmath>
#include <cassert>


f64 evaluateExpr(ExprNode* node);

f64 evaluate(const char* expression, bool print_tree=false);