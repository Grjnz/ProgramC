#include <iostream>
#include <string>
using namespace std;

// Property Proxy: 利用一個subject class包含泛型變數(composite),
// 定義泛用的setter, getter等等
// proxy類別則用來定義實際確定資料型態的變數

// Subject class
template <typename T>
class Property {
   private:
    T m_value;

   public:
    Property(const T initialValue) { 
        *this = initialValue; 
    }
    // 重載把Property物件cast成T型態的物件或變數
    operator T() { 
        cout << "call overloading operator T" << endl;
        return m_value; 
    }
    T operator=(T newValue) {
        cout << "call overloading operator =" << endl;
        m_value = newValue;
        return m_value;
    }
};

// Proxy類別: 實際確定資料型態的容器
class PropertyProxy {
   public:
    // 呼叫重載的operator=函式
    Property<int32_t> m_strength{10};
    // 呼叫重載的operator=函式
    Property<int32_t> m_agility{5};
};

int main() {
    PropertyProxy proxy;
    // 呼叫重載的operator=函式
    proxy.m_agility = 20;
    // 呼叫重載的opertor T函式
    // 將Property轉換為<int32_t>才能cout, 因cout只支援內建資料型態的輸出,
    // 不支援自定義的資料型態輸出
    cout << proxy.m_agility << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}