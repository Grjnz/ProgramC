#include <iostream>
#include <string>
using namespace std;

// Virtual Proxy: 用來代表一個佔用大量資源的物件
// 包含一個實際物件類別(realSubject class)與一個代理物件類別(proxySubject class)
// 代理物件類別在需要實際物件時才產生實際物件
// 代理物年類別亦可進行有助提升效率的外取(caching)等工作

// Abstract class of Subject
class Image {
   public:
    // 覆寫在代理物件中會產生實際物件的函式
    virtual void display() = 0;
};

// Concrete class of realSubject
class RealImage : public Image {
   private:
    string fileName;

   public:
    RealImage(string fileName) {
        this->fileName = fileName;
        cout << "load image here" << endl;
    }

    // 在realSubject class裡, 覆寫函式不產生實際物件
    void display() {
        cout << "Displaying image here" << endl;
    }
};

class ProxyImage : public Image {
   private:
    RealImage* realImage;
    string fileName;

   public:
    ProxyImage(string fileName) {
        this->fileName = fileName;
        // 在proxySubject的constructor中, 不產生realSubject instance
        realImage = nullptr;
    }

    // 在proxySubject class裡, 覆寫函式產生實際物件
    void display() {
        if (realImage == nullptr) {
            realImage = new RealImage(fileName);
        }
        realImage->display();
    }
};

int main() {
    Image* image = new ProxyImage("test.jpg");
    image->display();
    system("PAUSE");
    return 0;
}