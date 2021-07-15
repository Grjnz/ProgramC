#include <cmath>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// 建立具許多共同data members的model instance
// 透過model instance (proto) 的複製, 再用setter更改非共同的data members
// 進而產生完整的product instance

// Ordinary Copy Prototype

// component class: 具有許多共同data members
// 一般性的類別設定
class University {
   private:
    int grad;
    string college;
    string department;

   public:
    University(int grad, string college, string department) {
        this->grad = grad;
        this->college = college;
        this->department = department;
    }
    void setGrad(int g) {
        grad = g;
    }
    void setCollege(string c) {
        college = c;
    }
    void setDepart(string d) {
        department = d;
    }
    int getGrad() {
        return grad;
    }
    string getCollege() {
        return college;
    }
    string getDepartment() {
        return department;
    }
};

// product class: 包含component instance
// 定義夠用的copy constructor, 用來複製model instance
// 定義夠用的setters, 用來更改複製來的model instance, 進而產生完整的product instance
class Student {
   private:
    int id;
    University* univ;

   public:
    // 用來產生model instance的constructor
    Student(int id, int grad, string college, string department) {
        this->id = id;
        this->univ = new University(grad, college, department);
    }
    Student(const Student& s) {
        this->id = s.id;
        // 呼叫component class的copy constructor來設定component-instance data member
        this->univ = new University(s.univ->getGrad(), s.univ->getCollege(), s.univ->getDepartment());
    }
    int getID() {
        return id;
    }
    void setID(int id) {
        this->id = id;
    }
    University* getUniv() {
        return univ;
    }
};

// 定義Global static model instance
static Student protoEnvironment(0, 1, "Science", "Environment");
static Student protoPhysics(0, 1, "Science", "Physics");

int main() {
    // 呼叫copy constructor: 複製model instance (protoEnvironment)來產生新物件
    Student s1 = protoEnvironment;
    // 呼叫setter更改物件的data member
    s1.setID(123456);
    s1.getUniv()->setGrad(3);
    Student s2 = protoPhysics;
    s2.setID(654321);
    s2.getUniv()->setGrad(4);    
    cout << "ID: " << s1.getID() << "; Grad: " << s1.getUniv()->getGrad()
         << "; College: " << s1.getUniv()->getCollege() << "; Department: " 
         << s1.getUniv()->getDepartment() << endl;
    cout << "ID: " << s2.getID() << "; Grad: " << s2.getUniv()->getGrad()
         << "; College: " << s2.getUniv()->getCollege() << "; Department: " 
         << s2.getUniv()->getDepartment() << endl; 
    system("PAUSE");
    return EXIT_SUCCESS;
}