#include "visitor.h"
//TODO
void ExpressionPointer::Visit(NumberExpression* node)
{
	ostringstream os;
    os << node->Value;
    this->result = os.str();
    this->level = 4;
    return ;
}


void ExpressionPointer::Visit(BinaryExpression* node)
{
    switch (node->Op) {
        case Plus: 
        case Minus: this->level = 1; break;
        case Multiply:
        case Divide: this->level = 2; break;
    }
	ExpressionPointer lexp_vis, rexp_vis;
    node->First->Accept(&lexp_vis);
    node->Second->Accept(&rexp_vis);
    if (lexp_vis.level < this->level) {
        lexp_vis.result = string("(") + lexp_vis.result + string(")");
    }
    if (rexp_vis.level < this->level) {
        rexp_vis.result = string("(") + rexp_vis.result + string(")");
    }
    if (rexp_vis.level == this->level && 
        (node->Second->op == Minus || node->Second->op == Divide)) {
        rexp_vis.result = string("(") + rexp_vis.result + string(")");
    }
    switch (node->Op) {
        case Plus: this->result =  lexp_vis.result + "+" + rexp_vis.result; break;
        case Minus: this->result =  lexp_vis.result + "-" + rexp_vis.result; break;
        case Multiply: this->result =  lexp_vis.result + "*" + rexp_vis.result; break;
        case Divide: this->result =  lexp_vis.result + "/" + rexp_vis.result; break;
    }
    return ;
}

