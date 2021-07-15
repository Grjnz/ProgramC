#include <deque>
#include <iostream>
#include <string>
using namespace std;
// Singleton: 在程式執行過程中, 只能存在一個此類別的物件

// Singleton class
class FileRepository {
   private:
    deque<string> _files;
    // ***Forbid client code instating a new instance.
    // ***private default construct
    FileRepository() {
        cerr << " [LOG] File Respository Initialized."
             << "\n";
    }
   public:
    // ***delete copy constructor and overloading operator=
    FileRepository(const FileRepository&) = delete;
    FileRepository &operator=(FileRepository const &) = delete;
    ~FileRepository() {
        cerr << " [LOG] File Respository Deleted. Ok."
             << "\n";
    }

    // ***Return a reference to not allow client code to delete object.
    // ***static method for initiate an instance
    static FileRepository& getInstance() {
        // ***static instance => will not create new instance => unique instance
        static FileRepository RF;
        return RF;
    }

    void addFile(string fname) {
        _files.push_back(move(fname));
    }
    void clearFiles() {
        _files.clear();
    }
    void showFiles() {
        for (const auto& file : _files)
            cout << " File = " << file << endl;
    }
};

int main() {
    // FileRepository repo1 = FileRepository::getInstance();
    FileRepository& repo1 = FileRepository::getInstance();
    repo1.addFile("CashFlowStatement.txt");
    repo1.addFile("Balance-Sheet.dat");
    repo1.addFile("Sales-Report.csv");

    FileRepository& repo2 = FileRepository::getInstance();

    cout << boolalpha << "Same object? (&repo1 == &repo2 ?) = "
         << (&repo1 == &repo2)
         << "\n";
    cout << "Repository files" << endl;
    repo2.showFiles();

    cout << "Add more files" << endl;
    repo2.addFile("fileX1.pdf");
    repo2.addFile("fileX2.pdf");
    repo2.addFile("fileX3.pdf");
    repo2.showFiles();
    system("PAUSE");
    return 0;

    cout<<"test";
}