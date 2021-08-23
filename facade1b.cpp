#include <fstream>
#include <iostream>
#include <memory>
using namespace std;

// Facade design pattern: 利用一個facade class將幾個獨立但有相關聯的次系統,
// 在facade class內統一運作
// 包含: 各個次系統類別 (可多形), 與一個包含所有次系統資料成員的facade class

// 次系統A的abstract class
class ContentInterface {
   public:
    virtual string outputContent() = 0;
};

// 次系統A的concrete class
class ContentText : public ContentInterface {
   private:
    string text;

   public:
    ContentText(string s) {
        text = s;
    }
    string outputContent() {
        return text;
    }
};

// 次系統A的concrete class
class ContentInt : public ContentInterface {
   private:
    int number;

   public:
    ContentInt(int i) {
        number = i;
    }
    string outputContent() {
        return to_string(number);
    }
};

// 次系統B的abstract class
// 在此例中接收次系統A的資料
class DeviceInterface {
   public:
    // 接收次系統A的資料: ContentInterface* ci
    virtual void output(shared_ptr<ContentInterface> ci) = 0;
};

// 次系統B的concrete class
class MonitorDevice : public DeviceInterface {
   public:
    MonitorDevice() = default;
    void output(shared_ptr<ContentInterface> ci) {
        cout << ci->outputContent() << endl;
    }
};

// 次系統B的concrete class
class FileDevice : public DeviceInterface {
   private:
    string filename;

   public:
    FileDevice(string s) {
        filename = s;
    }
    void output(shared_ptr<ContentInterface> ci) {
        cout << "Output to file: " << filename << endl;
        ofstream file(filename.c_str());
        file << ci->outputContent();
        file.close();
    }
};

// Facade class: 包含所有次系統的資料成員
// 資料可在Facade class內自由傳遞
class Facade {
   private:
    shared_ptr<ContentInterface> content;
    shared_ptr<DeviceInterface> device;

   public:
    Facade(shared_ptr<ContentInterface> ci, shared_ptr<DeviceInterface> di) {
        device = di;
        content = ci;
    }
    void output() {
        device->output(content);
    }
};

int main() {
    shared_ptr<ContentInterface> numbers = make_shared<ContentInt>(54321);
    // shared_ptr<ContentInterface> texts = make_shared<ContentText>("C++");
    shared_ptr<DeviceInterface> monitor = make_shared<MonitorDevice>();
    shared_ptr<DeviceInterface> file = make_shared<FileDevice>("structFacadeEx1b.txt");
    unique_ptr<Facade> facadeMonitor = make_unique<Facade>(numbers, monitor);
    facadeMonitor->output();
    unique_ptr<Facade> facadeFile = make_unique<Facade>(numbers, file);
    facadeFile->output();
    system("PAUSE");
    return 0;
}