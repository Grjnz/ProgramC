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
        cout << "deleting: " << this->name << endl;       
    };

    void ls(int indent = 0) override {
        cout << this->tab(indent) << this->name << "." << this->ext << endl;
    }
};

class Folder : public FileSystem {
   protected:
    vector<FileSystem*> listings;

   public:
    Folder(string name) : FileSystem() {
        this->name = name;
    };
    virtual ~Folder() {
        cout << "deleting: " << this->name << endl;
        this->listings.clear();
    }
    void ls(int indent = 0) override {
        cout << this->tab(indent) << this->name << "/\n";
        vector<FileSystem*>::iterator itr = this->listings.begin();
        for (itr; itr != this->listings.end(); ++itr) {
            (*itr)->ls(indent + 1);
        }
    }
    void Add(FileSystem* listing) {
        this->listings.push_back(listing);
    }
};

void generator(){
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
}
int main() {
    // 無法自動釋放函式內的物件記憶體
    generator();
    system("PAUSE");
    return 0;
}