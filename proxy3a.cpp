#include <iostream>
#include <string>
using namespace std;

// Communication Proxy: 概念類似Property proxy, 但包裹proxy的概念較強
// 為模擬二維陣列, 需重載operator[]兩次, 
// 但同一個operator在同一個類別中只能重載一次,
// 所以必需將內陣列(二維陣列中的column)設為一種類別(proxy class),
// 而外陣列(二維陣列中的row)設為另一種類別(subject class)

// Proxy class
class proxy {
   private:
    int dim;
    int *arr1d;

   public:
    proxy() {
        dim = 0;
        arr1d = nullptr;
    }
    void setProxy(int n) {
        dim = n;
        arr1d = new int[n];
    }
    // 用call by reference的方式回傳陣列元素,
    // 在外部可設一個別名來接收, 就可以利用這個別名對陣列中的某個元素做設值, 取值的工作
    int &operator[](int idx) {
        return arr1d[idx];
    }
};

// Subject class
class arr2d {
   private:
    int row;
    int col;
    proxy *arr;

   public:
    arr2d(int r, int c) {
        row = r;
        col = c;
        arr = new proxy[r];
        for (int i = 0; i < row; i++) {
            arr[i].setProxy(col);
            for (int j = 0; j < col; j++) {
                arr[i][j] = i * 10 + j;
            }
        }
    }

    // 用call by reference的方式回傳陣列元素,
    // 在外部可設一個別名來接收, 就可以利用這個別名對陣列中的某個元素做設值, 取值的工作
    proxy &operator[](int idx) {
        return arr[idx];
    }
};

int main() {
    arr2d a(3, 4);
    cout << a[1][2] << endl;
    a[1][2] = 20;
    cout << a[1][2] << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}