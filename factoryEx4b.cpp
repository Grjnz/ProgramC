#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <memory>
using namespace std;

// Abstract Factory : unique_ptr version

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
    void setX(float x) {
        m_x = x;
    }
    void setY(float y) {
        m_y = y;
    }
};

class CartesianPoint : public IPoint {
   public:
    CartesianPoint(float x = 0.0, float y = 0.0) {
        m_x = x;
        m_y = y;
    }
};

class PolarPoint : public IPoint {
   public:
    PolarPoint(float r = 0.0, float theta = 0.0) {
        m_x = r * cos(theta);
        m_y = r * sin(theta);
    }
};

class IFactory {
   public:
    virtual unique_ptr<IPoint> create(float, float) = 0;
};

class CartesianFactory : public IFactory {
   public:
    // 使用unique_ptr
    unique_ptr<IPoint> create(float x, float y) {
        return make_unique<CartesianPoint>(x, y);
    }
};

class PolarFactory : public IFactory {
   public:
    PolarFactory() = default;
    unique_ptr<IPoint> create(float x, float y) {
        unique_ptr<IPoint> p = make_unique<PolarPoint>(x, y);
        cout << p.get() << endl;
        return p;
    }
};

int main() {
    PolarFactory pF;
    // 使用unique_ptr
    unique_ptr<IPoint> p = pF.create(5, M_PI_4);
    // unique_ptr需使用get()來取用instance address
    cout << p.get() << endl;
    cout << "x: " << p->getX() << " y: " << p->getY() << endl;  // x: 3.53553 y: 3.53553
    system("PAUSE");
    return EXIT_SUCCESS;
}