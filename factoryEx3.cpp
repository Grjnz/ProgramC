#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

// Inner Factory: factory class被包含在product class內部
enum class PointType { cartesian,
                       polar };

class Point {
   private:
    float m_x;
    float m_y;
    PointType m_type;
    // private constructor
    Point(const float x, const float y) : m_x{x}, m_y{y} {}
   
   //factory class已被包含在product class裡, 不需堅持用factory class method來做setter, getter
   public:
        float getX() {
            return m_x;
        }
        float getY() {
            return m_y;
        }
        void setCartesianXY(float x, float y) {
            m_type = PointType::cartesian;
            m_x = x;
            m_y = y;
        }
        void setPolarXY(float r, float theta) {
            m_type = PointType::polar;
            m_x = r * cos(theta);
            m_y = r * sin(theta);
        }
    // 被包含在product class裡的factory class
    // factory class包含static methods來產生不同型態的product instances
    // 需寫死, 無彈性
    class Factory {
       public:
        static Point NewCartesian(float x, float y) {
            return Point(x, y);
        }
        static Point NewPolar(float r, float theta) {
            return Point(r * cos(theta), r * sin(theta));
        }
    };
};

int main() {
    // 需藉由包含在product class裡的factory class來呼叫產生不同product instance的static method
    auto p = Point::Factory::NewPolar(5, M_PI_4);
    cout << "x: " << p.getX() << " y: " << p.getY() << endl;  // x: 3.53553 y: 3.53553
    system("PAUSE");
    return EXIT_SUCCESS;
}