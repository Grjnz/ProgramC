#include <iostream>
#include <string>
#include <map>
using namespace std;

// Flyweight design pattern: 將product的內容分為共用與非共用, 
// 共用內容可共用, 可節省資源
// 包含: flyweight class, product class, factory class
// flyweight class: 處理共同內容, 可多形, 形成多種concrete flyweight class
// product class: 包含非共同與flyweight class內容, 為最終產物物件
// factory class: 用來產生product class, 重點工作在讓共同內容能共用
// 不見得需要有product class, 若非共用內容為一些不同的行為, 
// 則可將這些行為定義在concrete flyweight class的method裡, 或在factory class內處理

// Abastract flyweight class: 處理共同內容
// 多形: 衍生多種不同性質的
class StudentShared {
   protected:
    string college;
    string department;

   public:
    StudentShared(string c, string d) {
        college = c;
        department = d;
    }
};

// Concrete flyweight class: 特定內容的flyweight class
class StudentEnvironment : public StudentShared {
   public:
    StudentEnvironment(string c, string d): StudentShared(c, d){};
};

// Concrete flyweight class: 特定內容的flyweight class
class StudentPhysics : public StudentShared {
   public:
    StudentPhysics(string c, string d): StudentShared(c, d){};
};

// product class: 包含非共同內容與flyweight class內容
class Student {
   private:
    StudentShared* shared;
    string id;

   public:
    Student(StudentShared* s, string id) {
        shared = s;
        this->id = id;
    }
    // 共同內容部分必須使用shallow copy, 否則失去flyweight的意義
    Student(const Student& s){
        shared = s.shared;
        id = s.id;
    }
    // 僅用來證明共同內容的確共用
    void showSharedAddress(){
        cout << shared << endl;
    }
};

// Factory class: 用來產生product instance, 
// 同時處理共用concrete flyweight instance
class StudentFactory {
   private:
    // 需包含一個所有concrete flyweight instance的map
    // 陣列內必需是abstract flyweight的指標, 以便達到多形的目的
    // product instance的concrete flyweight instance指標,
    // map內的concrete flyweight instance指標 (shallow copy)
    map<string, StudentShared *> studentMap;

   public:
    // 產生product instance, 同時處理共用concrete flyweight instance
    Student createStudent(const string& type, string id) {
        // 欲產生的concrete flyweight instance(多形)
        StudentShared* studentS;
        // 檢查欲產生的concrete flyweight instance是否已存在map中,
        // 是: 共用(將指標指向map內相對應的instance pointer)
        // 否: 產生新的instance, 並加入map內
        if (studentMap.find(type) != studentMap.end()) {
            studentS = studentMap[type];
        } else {
            if (type == "Environment"){
                studentS = new StudentEnvironment("Science", "Environment");
            }
            if (type == "Physics"){
                studentS = new StudentEnvironment("Science", "Physics");
            }
            // 僅用來證明共同內容的確共用
            cout << studentS << endl;
            // 將concrete flyweight instance(StudentShared)加入map
            studentMap[type] = studentS;
        }
        // studentS用call by address的方式, 
        // 傳遞concrete flyweight instance (shallow copy)
        // 如此便能使所產生的product instance(Student)與factory instance,
        // 共用conrete flyweight instance(map的內容)
        return Student(studentS, id);
    }
};

int main() {
    // 初始factory instance內的map無任何concrete flyweight instance
    StudentFactory *factory = new StudentFactory;
    // 會將特定的conrete flyweight instance(StudentEnvironment)加入map
    Student ees1 = factory->createStudent("Environment", "1234567");
    ees1.showSharedAddress();
    // StudentEnvironment已存在, 共用
    Student ees2 = factory->createStudent("Environment", "7654321");
    ees2.showSharedAddress();
    Student phy1 = factory->createStudent("Physics", "1234567");
    phy1.showSharedAddress();
    system("PAUSE");
    return 0;
}