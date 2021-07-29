#include <iostream>
using namespace std;

// Decorator design pattern: 包含component class與decorator class
// 透過decorator class包裹component instance或conrete decorators
// 產生"疊加包裹"的效果
// component與decorator classes均繼承Abstract component class
// component class為核心類別
// decorator class為包裹類別, 除繼承abstract component class以外,
// 另透過內含abstract component instance(多形),
// 來包裹concrete component instance或concrete decorators
// decorator class本身無多形功能, 定義上不屬interface
// 但因decorator class為所有concrete decorator的母類別,
// 且具有abstract component instance,
// 所以有類似interface的功能, 可整合component與decorator

// Abstract component class
class PlanInterface {
   public:
    virtual ~PlanInterface() = default;
    virtual float cost() = 0;
};

// Concrete component class
class BasicPlanA : public PlanInterface {
   private:
    float fee;

   public:
    BasicPlanA() {
        fee = 100.0;
    }
    ~BasicPlanA() {
        cout << "deleting BasicPlanA" << endl;
    };
    virtual float cost() { return fee; }
};

// Concrete component class
class BasicPlanB : public PlanInterface {
   private:
    float fee;

   public:
    BasicPlanB() {
        fee = 200.0;
    }
    ~BasicPlanB() {
        cout << "deleting BasicPlanB" << endl;
    }
    virtual float cost() { return fee; }
};

// Decorator class: 所有concrete decorators的母類別
// 繼承abstract component interface
// 包含abstract component instance: wrapper的架構
class BasicPlanWrapper : public PlanInterface {
   private:
    // abstract component instance, 多形, 為被包裹的核心
    // ***可接受各種不同的component instance與concrete decorators***
    PlanInterface* basicPlan;

   public:
    // 引數即為要被包裹的component instance或concrete decorators
    BasicPlanWrapper(PlanInterface* bp) {
        basicPlan = bp;
    }
    virtual ~BasicPlanWrapper() {
        delete basicPlan;
    }
    virtual float cost() {
        // 回傳被包裹核心的性質, 以便形成疊加的效果
        return basicPlan->cost();
    }
};

// concrete decorator class
// 繼承decorator class (wrapper), 所以也包裹了核心
// 同時也可被另一個concrete decorator class包裹
// 或包裹另一個concrete decorator, 形成疊加效果
class SurplusVoice : public BasicPlanWrapper {
    private:
    float fee;
   public:
    // 需被包裹的component isntance或concrete decorator: PlanInterface* bp,
    // 來設定decorator class的核心: BasicPlanWrapper(bp)
    SurplusVoice(PlanInterface* bp) : BasicPlanWrapper(bp){
        fee = 1000.0;
    };
    ~SurplusVoice() {
        cout << "deleting Surplus Voice Service" << endl;
    }
    float cost() {
        // 呼叫decorator class的包裹物件性質: BasicPlanWrapper::cost
        // 進行疊加
        return BasicPlanWrapper::cost() + fee;
    }
};

class SurplusInternet : public BasicPlanWrapper {
    private:
    float fee;
   public:
    SurplusInternet(PlanInterface* bp) : BasicPlanWrapper(bp) {
        fee = 10000.0;
    }
    ~SurplusInternet() {
        cout << "deleting Surplus Internet Service" << endl;
    }
    float cost() {
        return BasicPlanWrapper::cost() + fee;
    }
};

class SurplusMessage : public BasicPlanWrapper {
    private:
    float fee;
   public:
    SurplusMessage(PlanInterface* bp) : BasicPlanWrapper(bp) {
        fee = 100000.0;
    }
    ~SurplusMessage() {
        cout << "deleting Surplus Message Service" << endl;
    }
    float cost() {
        return BasicPlanWrapper::cost() + fee;
    }
};

int main(void) {
    PlanInterface* planX = new SurplusVoice(new BasicPlanA);
    PlanInterface* planXY = new SurplusInternet(new SurplusVoice(new BasicPlanA));
    PlanInterface* planXYZ = new SurplusMessage(new SurplusInternet(new SurplusVoice(new BasicPlanA)));
    cout << planX->cost() << endl;
    cout << planXY->cost() << endl;
    cout << planXYZ->cost() << endl;
    delete planX;
    delete planXY;
    delete planXYZ;
    system("PAUSE");
    return 0;
}