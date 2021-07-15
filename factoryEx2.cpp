#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

// Factory design pattern: 產生不同型態的product instances
// 與builder類似, product instance的產生、設值、取值, 均在factory裡處理

// Classical Factory: 使用factory class
// 將factory class設為product class的friend

enum class PointType { cartesian,
                       polar };

// product class
class Point {
   private:
    float m_x;
    float m_y;
    PointType m_type;
    // private constructor: 避免直接產生product instance
    // 用來被friend factory class裡的public static method呼叫.
    // 必須透過公有的static method來產生product instance.
    // constructor"不包含"product type變數來識別產生何種product instance.
    Point(const float x, const float y) : m_x{x}, m_y{y} {}

   public:
    // product class中不定義public setter, getter, 避免外部直接運作product
    // 將factory class宣告為friend class, 藉以直接存取product class裡的所有成員.
    friend class PointFactory;
};

// factory class
class PointFactory {
   public:
    // static method: 用來呼叫product class裡的private constructor
    // 針對不同的product type撰寫不同的static method
    static Point NewCartesian(float x, float y) {
        return Point(x, y);
    }
    // 針對不同的product type撰寫不同的static method
    // 所以factory class裡必需包含能產生所有product type的static method
    // 需寫死, 無彈性
    static Point NewPolar(float r, float theta) {
        return Point(r * cos(theta), r * sin(theta));
    }
    //將product class的setter, getter放在factory class內的static method中處理
    static float getX(Point& p){
        return p.m_x;
    }
    static float getY(Point& p){
        return p.m_y;
    }
    static void setCartesianXY(Point& p, float x, float y){
        p.m_type = PointType::cartesian;
        p.m_x = x;
        p.m_y = y;
    }
    static void setPolarXY(Point& p, float r, float theta){
        p.m_type = PointType::polar;
        p.m_x = r * cos(theta);
        p.m_y = r * sin(theta);
    }
};

int main() {
    auto p = PointFactory::NewPolar(5, M_PI_4);
    cout << "x: " << PointFactory::getX(p) << " y: " << PointFactory::getY(p) << endl; 
    PointFactory::setPolarXY(p, 2, M_PI_4);
    cout << "x: " << PointFactory::getX(p) << " y: " << PointFactory::getY(p) << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}