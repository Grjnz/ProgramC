#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <memory>
using namespace std;

// Generic Abstract Factory

// Abstract Product class: 與Ex4相同
class IPoint {
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

// concrete product class: 與EX4相同
class CartesianPoint : public IPoint {
   public:
    CartesianPoint(float x=0.0, float y=0.0){
        m_x = x;
        m_y = y;
    }
};

class PolarPoint : public IPoint {
   public:
    PolarPoint(float r=0.0, float theta=0.0){
        m_x = r * cos(theta);
        m_y = r * sin(theta);
    }
};

// 使用generic factory class來替代EX4中的多形, 可將abstract factory class省略
// 將不同的concrete product classes設定為T
template <typename T>
class PointFactory {
   public:
    // 將不同的concrete product classes設定為T
    unique_ptr<T> create(float x, float y) {
        return make_unique<T>(x, y);
    }
};

int main() {
    // 使用generic factory class
    PointFactory<PolarPoint> pF;
    unique_ptr<PolarPoint> p = pF.create(5, M_PI_4);
    cout << "x: " << p->getX() << " y: " << p->getY() << endl;  // x: 3.53553 y: 3.53553
    system("PAUSE");
    return EXIT_SUCCESS;
}