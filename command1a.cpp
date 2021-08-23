// Command design pattern: 包含command, receiver, invoker三種classes
// 整體而言, invoker class為client呼叫的介面, 
// receiver class定義實際的內容與動作,
// command class則連結receiver與invoker
// command class內含receiver物件的資料成員, 
// command class內含給invoker呼叫的功能, 通常是execute與undo
// execute與undo則是透過receiver物件資料成員來呼叫receiver的動作
// invoker class為給client(在此例為main)執行的介面,
// 通常包含記憶過去執行動作的容器, 便於undo,
// 包含執行command中execute, undo的函式
// receiver class為定義實際功能的類別,
// 為達成execute, undo的目的, 
// receiver內亦會定義類似的函式, 在此例中分別為operate, reverse
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

// receiver class
class Add {
   public:
    int valueToAdd;

   public:
    Add(int v) {
        valueToAdd = v;
    }
    Add(const Add& a) {
        valueToAdd = a.valueToAdd;
    }
    // 對應execute的函式
    int operate(int currentValue) {
        return currentValue + valueToAdd;
    }
    // 對應undo的函式
    int reverse(int currentValue) {
        return currentValue - valueToAdd;
    }
};

// receiver class
class Multiply {
   public:
    int valueToMultiply;

   public:
    Multiply(int v) {
        valueToMultiply = v;
    }
    Multiply(const Multiply& a) {
        valueToMultiply = a.valueToMultiply;
    }
    int operate(int currentValue) {
        return currentValue * valueToMultiply;
    }
    int reverse(int currentValue) {
        return currentValue / valueToMultiply;
    }
};

// Abstract class of command
// command最重要的工作為執行execute, undo的函式, 需宣告為虛擬
class Command {
   public:
    virtual int execute(int currenValue) = 0;
    virtual int undo(int currentValue) = 0;
};

// Concrete class of command
// 內含receiver物件, 用來執行receiver的動作
class AddComm : public Command {
   public:
    // receiver物件
    Add* add;

   public:
    AddComm(int a) {
        add = new Add(a);
    }
    AddComm(const AddComm& am) {
        add = am.add;
    }
    // 利用receiver物件呼叫欲執行的功能
    int execute(int currentValue) {
        int result = add->operate(currentValue);
        return result;
    }
    // 利用receiver物件呼叫欲執行的功能
    int undo(int currentValue) {
        int result = add->reverse(currentValue);
        return result;
    }
};

class MultiplyComm : public Command {
   public:
    Multiply* multiply;

   public:
    MultiplyComm(int a) {
        multiply = new Multiply(a);
    }
    MultiplyComm(const MultiplyComm& mm) {
        multiply = mm.multiply;
    }
    int execute(int currentValue) {
        int result = multiply->operate(currentValue);
        return result;
    }
    int undo(int currentValue) {
        int result = multiply->reverse(currentValue);
        return result;
    }
};

// 可定義複合性的command class
class AddMultiComm : public Command {
   public:
    // 包含兩個以上的receiver物件
    Add* add;
    Multiply* multi;

   public:
    AddMultiComm(int a, int m) {
        add = new Add(a);
        multi = new Multiply(m);
    }
    AddMultiComm(const AddMultiComm& am) {
        add = am.add;
        multi = am.multi;
    }
    int execute(int currentValue) {
        int first = add->operate(currentValue);
        int result = multi->operate(first);
        return result;
    }
    int undo(int currentValue) {
        int first = multi->reverse(currentValue);
        int result = add->reverse(first);
        return result;
    }
};

// invoker class: client的介面
class Calculator {
   public:
    // 此例中, value為初始值, 後續可四則運算其他值, 
    // 其他值則透過command class去設定其資料成員recevier
    // 例如: 5+10 => 5即value, 10則透過AddComm(5)去設定Add(5) 
    // vector用來記錄執行過的動作, 這些動作必經過command instance,
    // 所以vector宣告為command類別
    int value;
    vector<Command*> history;

   public:
    Calculator(int v) {
        value = v;
    }
    void executeCommand(Command* c) {
        value = c->execute(value);
        history.push_back(c);
    }
    void undoCommand() {
        Command* c = history.back();
        value = c->undo(value);
        history.pop_back();
    }
};

int main() {
    // 用invoker給定初始值5
    Calculator calAdd(5);
    // 先產生command instance
    // invoker呼叫execute執行command instanc的動作
    calAdd.executeCommand(new AddComm(10));
    cout << calAdd.value << endl;
    calAdd.undoCommand();
    cout << calAdd.value << endl;

    // 利用複合command class執行複合動作
    Calculator* calAddMulti = new Calculator(5);
    calAddMulti->executeCommand(new AddMultiComm(10, 20));
    cout << calAddMulti->value << endl;
    calAddMulti->undoCommand();
    cout << calAddMulti->value << endl;

    // 複合command也可以用序列動作來取
    Calculator* calSequence = new Calculator(5);
    calSequence->executeCommand(new AddComm(10));
    cout << calSequence->value << endl;
    calSequence->executeCommand(new MultiplyComm(20));
    cout << calSequence->value << endl;
    calSequence->undoCommand();
    cout << calSequence->value << endl;
    calSequence->undoCommand();
    cout << calSequence->value << endl;
    system("pause");
    return 0;
}