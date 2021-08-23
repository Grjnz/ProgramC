#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// Abstract class of receiver
// 方便command class資料成員的多形宣告

class Receiver {
   public:
    virtual int operate(int currentValue) = 0;
    virtual int reverse(int currentValue) = 0;
};

class Add : public Receiver {
   public:
    int valueToAdd;

   public:
    Add(int v) {
        valueToAdd = v;
    }
    Add(const Add& a) {
        valueToAdd = a.valueToAdd;
    }
    int operate(int currentValue) {
        return currentValue + valueToAdd;
    }
    int reverse(int currentValue) {
        return currentValue - valueToAdd;
    }
};

class Multiply : public Receiver {
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

class Command {
   public:
    virtual int execute(int currenValue) = 0;
    virtual int undo(int currentValue) = 0;
};

class ConcreteComm : public Command {
   public:
    // 因新增receiver的abstract class, 在此可利用多形型式
    // 而不需用泛型
    Receiver* receiver;

   public:
    ConcreteComm(Receiver* r) {
        receiver = r;
    }
    int execute(int currentValue) {
        int result = receiver->operate(currentValue);
        return result;
    }
    int undo(int currentValue) {
        int result = receiver->reverse(currentValue);
        return result;
    }
};

// invoker class
class Calculator {
   public:
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
    Calculator calAdd(5);
    // 因receiver需要多形, 
    // 所以要透過單獨的陳述式才能宣告一個母類別指標指向子類別
    // 如果這樣寫:
    // calAdd.executeCommand(new ConcreteComm(new Add(10)));
    // new Add(10)會產生一個子類別(Add*)物件指標,
    // 這與ConcreteComm(Receiver*)的宣告不合
    Receiver* ar = new Add(10);
    calAdd.executeCommand(new ConcreteComm(ar));
    cout << calAdd.value << endl;
    calAdd.undoCommand();
    cout << calAdd.value << endl;
    //
    Calculator* calSequence = new Calculator(5);
    Receiver* mr = new Multiply(20);
    calSequence->executeCommand(new ConcreteComm(ar));
    calSequence->executeCommand(new ConcreteComm(mr));
    cout << calSequence->value << endl;
    calSequence->undoCommand();
    calSequence->undoCommand();
    cout << calSequence->value << endl;
    system("pause");
    return 0;
}
