#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

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
    int operate(int currentValue) {
        return currentValue + valueToAdd;
    }
    int reverse(int currentValue) {
        return currentValue - valueToAdd;
    }
};

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

class Command {
   public:
    virtual int execute(int currenValue) = 0;
    virtual int undo(int currentValue) = 0;
};

// 將concrete command class改為泛型, 可大幅簡化程式碼
template <typename T>
class ConcreteComm : public Command {
   public:
    T* receiver;

   public:
    ConcreteComm(int a) {
        receiver = new T(a);
    }
    ConcreteComm(const T& rv) {
        receiver = rv.receiver;
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
    calAdd.executeCommand(new ConcreteComm<Add>(10));
    cout << calAdd.value << endl;
    calAdd.undoCommand();
    cout << calAdd.value << endl;
    //
    Calculator* calSequence = new Calculator(5);
    calSequence->executeCommand(new ConcreteComm<Add>(10));
    calSequence->executeCommand(new ConcreteComm<Multiply>(20));
    cout << calSequence->value << endl;
    calSequence->undoCommand();
    calSequence->undoCommand();
    cout << calSequence->value << endl;
    system("pause");
    return 0;
}
