#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class FileSystem {
   protected:
    string tab(int indent) {
        return string(indent * 4, ' ');
    }
    string name;

   public:
    FileSystem(): name(""){};
    virtual ~FileSystem(){};
    virtual void ls(int indent = 0) = 0;
};

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

class Folder : public FileSystem {
   protected:
    vector<shared_ptr<FileSystem>> listings;

   public:
    Folder(string name) : FileSystem() {
        this->name = name;
    };
    virtual ~Folder() {
        this->listings.clear();
        cout << "deleting: " << this->name << endl;
    }
    void ls(int indent = 0) override {
        cout << this->tab(indent) << this->name << "/\n";
        vector<shared_ptr<FileSystem>>::iterator itr = this->listings.begin();
        for (itr; itr != this->listings.end(); ++itr) {
            (*itr)->ls(indent + 1);
        }
    }
    void Add(shared_ptr<FileSystem> listing) {
        this->listings.push_back(listing);
    }
};

void generator(){
    shared_ptr<Folder> rootDir = make_shared<Folder>("root");
    shared_ptr<Folder> homeDir = make_shared<Folder>("home");
    homeDir->Add(make_shared<File>("howToCode", "pdf"));
    homeDir->Add(make_shared<File>("ThingsToDo", "txt"));
    homeDir->Add(make_shared<File>("grandCanyon", "png"));
    rootDir->Add(homeDir);
    shared_ptr<Folder> projDir = make_shared<Folder>("projDir");
    shared_ptr<Folder> labDir = make_shared<Folder>("labDir");
    labDir->Add(make_shared<File>("index", "html"));
    shared_ptr<Folder> eesDir = make_shared<Folder>("ees");
    eesDir->Add(make_shared<File>("app", "py"));
    projDir->Add(labDir);
    projDir->Add(eesDir);
    rootDir->Add(projDir);
    rootDir->Add(make_shared<File>("composite", "cpp"));
    rootDir->ls();
}

int main() {
    // 在函式執行完之後所有的物件均被成功釋放
    generator();
    system("PAUSE");
    return 0;
}