#include "visitor.h"
//TODO
void ExpressionPointer::Visit(NumberExpression* node)
{
    int num = node->Value;
    string temp = "";
    if (num < 0) {
        num = -num;
        temp = "-";
    } else {
        temp = "";
    }

    do {
        temp = static_cast<char>(num % 10 + '0') + temp;
        num /= 10;
    } while (num);

    this->result += temp;
    this->level = 2;//不懂
    return ;

}


void ExpressionPointer::Visit(BinaryExpression* node)
{
    ExpressionPointer visFirst, visSecond;
    switch (node->Op) {//判断操作符并给出优先级
        case BinaryOperator::Plus:
        case BinaryOperator::Minus:
            this->level = 0;
            break;
        case BinaryOperator::Multiply:
        case BinaryOperator::Divide:
            this->level = 1;
            break;
    }
    node->First->Accept(&visFirst);
    node->Second->Accept(&visSecond);//访问左右孩子

    //加必要的括号
    if (this->level > visFirst.level) {//左孩子
        visFirst.result = '(' + visFirst.result + ')';
    }

    this->result += GetOp(node->Op);
    
    if ((this->level > visSecond.level)
        || ((this->level == visSecond.level) && (node->Op == BinaryOperator::Minus | node->Op == BinaryOperator::Divide))) {
            visSecond.result = '(' + visSecond.result + ')';
        }

    this->result = visFirst.result + GetOp(node->Op) + visSecond.result;

	return;
}
