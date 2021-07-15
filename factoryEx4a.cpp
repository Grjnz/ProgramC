#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

// Abstract Factory : regular pointer version

// abstract product class (interface)
// 僅定義最基本的data members and member functions
// 不需定義constructor, constructor可在concrete product class裡定義
class IPoint {
    // protected data members: 可在concrete (derived) product class裡被直接調用
   protected:
    float m_x;
    float m_y;

   public:
    float getX() {
        return m_x;
    }
    float getY() {
        return m_y;
    }
    void setX(float x){
        m_x = x;
    }
    void setY(float y){
        m_y = y;
    }
};

// concrete product class: 並不直接用concrete product class產生物件
// 透過factory class產生物件
class CartesianPoint : public IPoint {
   private:
    // public constructor用來產生product instance.
    CartesianPoint(float x = 0.0, float y = 0.0) {
        m_x = x;
        m_y = y;
    }
    friend class CartesianFactory;
};

// 不同的concrete product class用來定義不同product type
// 可彈性新增concrete product class
class PolarPoint : public IPoint {
   public:
    PolarPoint(float r = 0.0, float theta = 0.0) {
        m_x = r * cos(theta);
        m_y = r * sin(theta);
    }
    friend class PolarFactory;
};

// abstract factory class (interface)
class IFactory {
   public:
    // 定義public virtual method讓後續產生product instance的method來override
    // 用abstract product pointer (IPoint*) 來使用polymorphism
    virtual IPoint* create(float, float) = 0;
};

// concrete factory class: 用來產生product instances
// 不同的concrete factory class可產生不同型態的product instance
class CartesianFactory : public IFactory {
   public:
    // 定義public overriding method來產生product instance
    // 用abstract product pointer (IPoint*) 來使用polymorphism
    IPoint* create(float x, float y) {
        return new CartesianPoint(x, y);
    }
};

class PolarFactory : public IFactory {
   public:
    PolarFactory() = default;
    IPoint* create(float x, float y) {
        IPoint* p = new PolarPoint(x, y);
        cout << p << endl;
        return p;
    }
};

int main() {
    PolarFactory pF;
    // Abstract factory具多形結構, 要使用abstract product pointer (IPoint*)
    IPoint* p = pF.create(4, M_PI_4);
    cout << p << endl;
    cout << "x: " << p->getX() << " y: " << p->getY() << endl;  // x: 3.53553 y: 3.53553
    system("PAUSE");
    return EXIT_SUCCESS;
}