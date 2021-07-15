#include <cmath>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Prototype Factory

// Component Class: 與Ex1相同
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

// Product class: 與Ex1相同
class Student {
   private:
    int id;
    University* univ;

   public:
    Student(int id, int grad, string college, string department) {
        this->id = id;
        this->univ = new University(grad, college, department);
    }
    Student(const Student& s) {
        this->id = s.id;
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
    friend class StudentFactory;
};

// Factory class: 用來定義不同的model instances
// 包含private static model instance
// 包含private static method, 用來產生完整的product instance
// 包含public static method, 用來產生不同的model instance

class StudentFactory {
   private:
    // static model instance必需在類別外初始化
    static Student Environment;
    static Student Physics;
    // 用來產生完整的product instance, 要傳入需變更的data, model instance
    // 此為共用的method, 透過傳進來的model instance來產生不同的product
    // 此method設定為private, 避免被直接呼叫, 產生product
    // 此method用來被public static method (類似factory method) 呼叫 
    static unique_ptr<Student> NewStudent(int id, int grad, Student& proto) {
        // 先呼叫copy constructor複製model instance
        auto s = make_unique<Student>(proto);
        // 隨後呼叫setters設定需變更的data members
        s->id = id;
        s->getUniv()->setGrad(grad);
        return s;
    }

   public:
    // public static method: 用來產生完整的product instance
    // 不同的method會利用不同model instance來產生product instance, 所以只需傳入需要變更的data
    // 呼叫共用的method來產生特定model instance的product instance
    static unique_ptr<Student> NewEnvironmentStudent(int id, int grad) {
        return NewStudent(id, grad, Environment);
    }
    // 需針對不同的model instance定義不同的public static method
    static unique_ptr<Student> NewPhysicsStudent(int id, int grad) {
        return NewStudent(id, grad, Physics);
    }
};

// 類別內的static data member, 必需在類別外被初始化 (compile time被初始化)
// static data member無法在類別內被初始化

Student StudentFactory::Environment{0, 1, "Science", "Environment"};
Student StudentFactory::Physics{0, 1, "Science", "Physics"};

int main() {
    // 呼叫特定的(為某種特定的model instance)public static method來產生完整的product instance
    auto s1 = StudentFactory::NewEnvironmentStudent(123456, 3);
    auto s2 = StudentFactory::NewPhysicsStudent(654321, 4);
    cout << "ID: " << s1->getID() << "; Grad: " << s1->getUniv()->getGrad()
         << "; College: " << s1->getUniv()->getCollege() << "; Department: " 
         << s1->getUniv()->getDepartment() << endl;
    cout << "ID: " << s2->getID() << "; Grad: " << s2->getUniv()->getGrad()
         << "; College: " << s2->getUniv()->getCollege() << "; Department: " 
         << s2->getUniv()->getDepartment() << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}