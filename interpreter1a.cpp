// Interpreter design pattern用來處理語法轉換問題, 例如:
// 單位換算, 羅馬數字, 四則運算等等, 通常包括以下類別:
// context class (可有可無): 語法的前處理
// expression class: 分為terminal與non-terminal expression兩種
// terminal expression: 處理不需interpret的context, 類似leaf class
// non-terminal expression: 處理需要interpret的context, 類似composite class
// 例如: 四則運算中, 運算式用context class做前處理, 
// context可區分為運算子與數字兩大類, 
// 運算子為non-terminal expression, 需定義運算子如何運作
// 數字為terminal expression, 不需處理
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// abstract expression class
class Expression {
   public:
    virtual int interpret() = 0;
};

// Terminal Expression
// 只將字串轉換成整數, 不需做其他處理
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
    // 單純回傳整數 => terminal expression
    int interpret() {
        return number;
    }
};

// Non-terminal Expression
// 需定義 + - * / 的運算
class Addition : public Expression {
   private:
    Expression* leftOperand;
    Expression* rightOperand;

   public:
    Addition(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }
    // 定義 + - * / 之運算
    int interpret() {
        return leftOperand->interpret() + rightOperand->interpret();
    }
};

class Subtraction : public Expression {
   private:
    Expression* leftOperand;
    Expression* rightOperand;

   public:
    Subtraction(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }

    int interpret() {
        return leftOperand->interpret() - rightOperand->interpret();
    }
};

class Multiply : public Expression {
   private:
    Expression* leftOperand;
    Expression* rightOperand;

   public:
    Multiply(Expression* leftOp, Expression* rightOp) {
        this->leftOperand = leftOp;
        this->rightOperand = rightOp;
    }

    int interpret() {
        return leftOperand->interpret() * rightOperand->interpret();
    }
};

class Divide : public Expression {
   private:
    Expression* leftOperand;
    Expression* rightOperand;

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
};

bool isOperatorString(string str) {
    if ((str == "+") || (str == "-") || (str == "*") || (str == "/"))
        return true;
    else
        return false;
}

int main() {
    vector<string> vecPost;
    vector<Expression*> vecNum;
    string postFix = "5 3 * 2 + 1 - 4 /";
    string t;
    // 把運算式用" "split變成個別單一字串, 存到vecPost中
    istringstream sFix(postFix);
    while (sFix >> t) {
        vecPost.push_back(t);
    }
    for (string s : vecPost) {
        // 判斷是terminal expression還是non-terminal expression
        // 如果是數字就加到vecNum中, 
        // 如果是運算子就把vecNum中的數字拿出來(且清空), 
        // 傳入相對運算子的non-terminal class中進行運算
        // 將結果存入vecNum, 繼續下一輪的運算
        if (isOperatorString(s)) {
            Expression* rightOp = vecNum.back();
            vecNum.pop_back();
            Expression* leftOp = vecNum.back();
            Expression* op;
            vecNum.pop_back();
            if (s == "+") {
                op = new Addition(leftOp, rightOp);
            }
            if (s == "-") {
                op = new Subtraction(leftOp, rightOp);
            }
            if (s == "*") {
                op = new Multiply(leftOp, rightOp);
            }
            if (s == "/") {
                op = new Divide(leftOp, rightOp);
            }
            int result = op->interpret();
            vecNum.push_back(new WholeNumber(result));
        } else {
            Expression* num = new WholeNumber(s);
            vecNum.push_back(num);
        }
    }
    for (Expression* s : vecNum) {
        cout << s->interpret() << endl;
    }
    system("PAUSE");
    return 0;
}