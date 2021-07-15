#include <iostream>
#include <string>
using namespace std;

// Builder design pattern
// 如果一個product有十幾個private data members, 
// 要產生一個product物件, 那就要寫很多constructors, 
// 因為有時某些data members還不要設值, 這會造成寫constructor的困擾
// 此時可用builder design pattern
// Builder design pattern包含product class與builder class
// product class僅包含基本的getter給builder class呼叫.
// 建立與設值product class的工作則由builder class負責

// Product class
// 因建立product class的工作要由builder class負責,
// 因此, 要避免client端直接呼叫product class的建構子
// 所以, product class要宣告private constructor
// 在constructor, setter被宣告為private之下,
// 需要宣告builder class為product class的友誼類別
// 一般product class只需default constructor, 給定最簡化的初始值即可
// 複雜的設值由builder class處理
class UserData {  // product class
   private:
    int userID = 0;
    string name;
    // private default constructor, 只提供最簡版本的constructor
    // 設值則由builder來處理, 較彈性
    // 當有十幾個data members, constructor的排列組合太多, 難處理
    // 要避免直接由product class產生物件, 需宣告為private
    UserData() = default;

    // builder class裡的build()函式call by value, 需copy constructor
    // builder class是product class的friend, 所以build()函式可呼叫copy constructor
    // 要避免直接由product class產生物件, 需宣告為private
    UserData(const UserData& u) = default;
    
   public:
    ~UserData() = default;  // Explicit is better than implicit
    void show() {
        cout << "\nUser{"
             << "\n"
             << "  id        = " << userID
             << "\n"
             << "  name      = " << name
             << "}\n";
    }
    // constructor被宣告為private, 需要宣告builder class為friend
    // 若不宣告builder class, 就要在product class裡定義public setter, constructors
    // 那就無法避免直接用product class產生product
    friend class UserBuilder;
};

// builder class負責product instance的產生、設值、取值等所有運作
// 因被宣告為Product class的friend, 所以可以直接存取私有資料成員
// 因此不需在product class內定義setter, 而在builder class裡定義product class的setter
// builder class包含product class的物件
class UserBuilder {
   private:
    // product class的物件
    UserData* data;

   public:
    UserBuilder() {
        data = new UserData();
    }
    // 定義product class的setter
    // return *this可達到fluent structure的目的
    // 把product class setter定義在builder class裡的原因是:
    // 避免由product class來設定product
    // 但應該也可以把product class setter定義在product class裡, 
    // 但宣告為private, 在此被呼叫
    UserBuilder& setID(int userID) {
        data->userID = userID;
        return *this;
    }
    UserBuilder& setName(const string& name) {
        data->name = name;
        return *this;
    }
    // 呼叫copy constructor, 回傳product instance的複製 (call by value)
    // 避免主函式的product instance與builder裡的product instance共用
    UserData build() {
        return *(this->data);
    }
};

int main() {
    // 透過builder instance產生一個最簡product instance (builder class的data member)
    // 利用builder class定義的setter(for product instance), 進行彈性的設值
    // 最後回傳builder內的product instance的複製(call by value)來產生物件
    // product class的copy constructor被宣告為私有, 所以無法以:
    // UserData user = ....build()的語法為call by value, 回傳一個沒有名子的物件
    // 為了避免再一次呼叫複製建構子, 所以宣告rvalue reference
    UserData&& user =
        UserBuilder()
            .setID(2065)
            .setName("John")
            .build();
    user.show();
    system("PAUSE");
    return EXIT_SUCCESS;
}