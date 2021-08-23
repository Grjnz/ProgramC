#include <iostream>
#include <string>
using namespace std;

// Communication Proxy: 概念類似Property proxy, 但包裹proxy的概念較強

template <typename T>
class proxy {
   private:
    int dim;
    T *arr1d;

   public:
    proxy() {
        dim = 0;
        arr1d = nullptr;
    }
    void setProxy(int n) {
        dim = n;
        arr1d = new T[n];
    }
    T &operator[](int idx) {
        return arr1d[idx];
    }
};

template <typename T>
class arr2d {
   private:
    int row;
    int col;
    proxy<T> *arr;

   public:
    arr2d(int r, int c) {
        row = r;
        col = c;
        arr = new proxy<T>[r];
        for (int i = 0; i < row; i++) {
            arr[i].setProxy(col);
            for (int j = 0; j < col; j++) {
                arr[i][j] = i * 10 + j;
            }
        }
    }
    proxy<T> &operator[](int idx) {
        return arr[idx];
    }
};

int main() {
    arr2d<int> a(3, 4);
    cout << a[1][2] << endl;
    a[2][3] = 1000;
    cout << a[2][3] << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}