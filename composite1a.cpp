#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Abstract component class: leaf class與composite class的母類別
// leaf為個別物件, composite為包含許多leaf或composite instances的container
// 如此可形成無深度限制的樹狀結構, 所有的樹狀結構均可利用composite pattern
// leaf class與composite class均繼承component class, 
// 如此可使用相同的操作介面, 如add, insert, delete等,
// 不必在乎是composite還是leaf instance
// 再者, 也能利用遞迴拜訪composite內的所有的composite與leaf物件

// Abstract component class: 內容共同的資料成員與成員函式
class FileSystem {
   protected:
    string tab(int indent) {
        return string(indent * 4, ' ');
    }
    string name;

   public:
    FileSystem(): name(""){};
    virtual ~FileSystem(){};
    // 當設為純虛擬函式時, product class的vector只能設為pointer,
    // 若不為指標, 就無法處理多形, 任何component instance的宣告,
    // 均會要求產生Abstract component instance物件
    virtual void ls(int indent = 0) = 0;
};

// leaf class: 定義個別物件
class File : public FileSystem {
   protected:
    string ext;

   public:
    File(string name, string ext) : FileSystem() {
        this->name = name;
        this->ext = ext;
    };
    virtual ~File(){
        // 顯示被刪除的leaf instance
        cout << "deleting: " << this->name << endl;       
    };

    void ls(int indent = 0) override {
        cout << this->tab(indent) << this->name << "." << this->ext << endl;
    }
};

// composite class: 包含許多leaf與composite instances的類別
// 宣告vector來儲存leaf與composite instances的指標
class Folder : public FileSystem {
   protected:
    // 儲存指標物件, 必需為指標, 才能處理多形
    vector<FileSystem*> listings;

   public:
    Folder(string name) : FileSystem() {
        this->name = name;
    };
    virtual ~Folder() {
        vector<FileSystem*>::iterator itr = this->listings.begin();
        for (; itr != this->listings.end(); ++itr) {
            // ***呼叫delete等於呼叫destructor, 等於呼叫自己, 直到沒有物件為止***
            // 可完整刪除整個樹狀結構
            delete *itr;
        }
        // 可證明將整個樹狀結構刪除
        cout << "deleting: " << this->name << endl;
        // 清空vector, 但for迴圈已經delete所有的物件了, 應該可以省略
        this->listings.clear();
    }
    void ls(int indent = 0) override {
        cout << this->tab(indent) << this->name << "/\n";
        vector<FileSystem*>::iterator itr = this->listings.begin();
        for (itr; itr != this->listings.end(); ++itr) {
            // ***呼叫自己(ls), 遞迴結構, 可完整拜訪整個樹狀結構***
            (*itr)->ls(indent + 1);
        }
    }
    void Add(FileSystem* listing) {
        this->listings.push_back(listing);
    }
};

int main() {
    Folder* rootDir = new Folder("root");
    Folder* homeDir = new Folder("home");
    homeDir->Add(new File("howToCode", "pdf"));
    homeDir->Add(new File("ThingsToDo", "txt"));
    homeDir->Add(new File("grandCanyon", "png"));
    rootDir->Add(homeDir);
    Folder* projDir = new Folder("projDir");
    Folder* labDir = new Folder("labDir");
    labDir->Add(new File("index", "html"));
    Folder* eesDir = new Folder("ees");
    eesDir->Add(new File("app", "py"));
    projDir->Add(labDir);
    projDir->Add(eesDir);
    rootDir->Add(projDir);
    rootDir->Add(new File("composite", "cpp"));
    rootDir->ls();
    delete rootDir;
    system("PAUSE");
    return 0;
}