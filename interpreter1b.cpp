#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Expression {
   public:
    virtual int interpret() = 0;
    virtual void setLR(Expression* leftOp, Expression* rightOp) = 0;
    virtual string className() = 0;
};

class WholeNumber : public Expression {
   private:
    int number;

   public:
    WholeNumber(int number) {
        this->number = number;
    }

    WholeNumber(string str) {
        this->number = atoi(str.c_str());
    }

    int interpret() {
        return number;
    }

    void setLR(Expression* leftOp, Expression* rightOp){};
    string className() {
        return "WholeNumber";
    }
};

// 新增一個abstract Non-terminal Expression class,
// 運算子的類別繼承這個abstract class, 但用處不大
// 因為Non-terminal與terminal class本來就要有多形,
// 新增這個abstract class只會增加困擾而已, 用不上
class NonterminalExpression : public Expression {
   protected:
    Expression* leftOperand;
    Expression* rightOperand;

   public:
    virtual int interpret() = 0;
    virtual void setLR(Expression* leftOp, Expression* rightOp) = 0;
    virtual string className() = 0;
};

class Addition : public NonterminalExpression {
   public:
    Addition(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }

    int interpret() {
        return leftOperand->interpret() + rightOperand->interpret();
    }

    void setLR(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }
    string className() {
        return "Addition";
    }
};

class Subtraction : public NonterminalExpression {
   public:
    Subtraction(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }

    int interpret() {
        return leftOperand->interpret() - rightOperand->interpret();
    }

    void setLR(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }
    string className() {
        return "Subtraction";
    }
};

class Multiply : public NonterminalExpression {
   public:
    Multiply(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }

    int interpret() {
        return leftOperand->interpret() * rightOperand->interpret();
    }

    void setLR(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }
    string className() {
        return "Multiply";
    }
};

class Divide : public NonterminalExpression {
   public:
    Divide(Expression* numerator, Expression* denominator) {
        this->leftOperand = numerator;
        this->rightOperand = denominator;
    }

    int interpret() {
        if (rightOperand->interpret() == 0) {
            cout << "Division by Zero Exception" << endl;
            return 0;
        } else {
            return leftOperand->interpret() / rightOperand->interpret();
        }
    }

    void setLR(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }
    string className() {
        return "Divide";
    }
};

// 新增一個context類別用來處理語法, 內容一個Expression class的資料成員
// 用來儲存現在的Expression instance
class context {
   private:
    Expression* ctx;

   public:
    context(string str) {
        if (str == "+")
            ctx = new Addition(nullptr, nullptr);
        else if (str == "-")
            ctx = new Subtraction(nullptr, nullptr);
        else if (str == "*")
            ctx = new Multiply(nullptr, nullptr);
        else if (str == "/")
            ctx = new Divide(nullptr, nullptr);
        else
            ctx = new WholeNumber(str);
    }
    Expression* getCtx() {
        return ctx;
    }
};

int main() {
    vector<string> vecContext;
    vector<Expression*> vecNum;
    string postFix = "5 3 * 2 + 1 - 4 /";
    string t;
    istringstream sFix(postFix);
    while (sFix >> t) {
        vecContext.push_back(t);
    }
    for (string s : vecContext) {
        Expression* expr = context(s).getCtx();
        string className = expr->className();
        if (className == "WholeNumber")
            vecNum.push_back(expr);
        else {
            Expression* rightOp = vecNum.back();
            vecNum.pop_back();
            Expression* leftOp = vecNum.back();
            vecNum.pop_back();
            expr->setLR(leftOp, rightOp);
            int result = expr->interpret();
            vecNum.push_back(new WholeNumber(result));
        }
    }
    for (Expression* s : vecNum) {
        cout << s->interpret() << endl;
    }
    system("PAUSE");
    return 0;
}