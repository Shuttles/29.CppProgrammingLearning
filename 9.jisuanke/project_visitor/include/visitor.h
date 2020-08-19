#pragma once
#include "Expression.h"
#include "utility.h"
#include <string>
#include <stack>
using std::string;
using std::stack;
using std::to_string;


class ExpressionPointer :public Expression::IVisior
{//解析语法树功能的访问者类
public:
	string result;

    int level;//优先级

	void Visit(NumberExpression* node);


	
	void Visit(BinaryExpression* node);
	
};

