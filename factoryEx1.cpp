#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

// Factory design pattern: 產生不同型態的product instances
// 與builder類似, product instance的產生、設值、取值, 均在factory裡處理

// Factory Method: Factory為product class內的static public method

enum class PointType { cartesian,
                       polar };

// product class
class Point {
   private:
    float m_x;
    float m_y;
    // 要產生不同型態的product instances, 需額外包含一個poduct type的變數
    PointType m_type;   

    // private constructor: 避免直接產生product instance
    // 用來被product class裡的public static method呼叫.
    // 必須透過公有的static method來產生product instance.
    // constructor包含product type變數來識別產生何種product instance.
    Point(const float x, const float y, PointType t) : m_x{x}, m_y{y}, m_type{t} {}

   public:
    // 包含在product class裡的public static method: 用來產生product instance
    static Point NewCartesian(float x, float y) {
        return Point(x, y, PointType::cartesian);
    }
    static Point NewPolar(float a, float b) {
        return Point(a * cos(b), a * sin(b), PointType::polar);
    }
    float getX(){
        return m_x;
    }
    float getY(){
        return m_y;
    }
};

int main() {
    // Point p{ 1,2 };  // 未提供public constructor
    auto p = Point::NewPolar(5, M_PI_4);
    cout << "x: " << p.getX() << " y: " << p.getY() << endl;  // x: 3.53553 y: 3.53553
    system("PAUSE");
    return EXIT_SUCCESS;
}