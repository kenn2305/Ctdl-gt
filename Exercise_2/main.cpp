#include <iostream>
#include <stdexcept>

using namespace std;

class MyVector {
private:
    int* data;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity_ = new_capacity;
    }

public:
    MyVector() : data(nullptr), size_(0), capacity_(0) {}

    ~MyVector() {
        delete[] data;
    }

    MyVector(const MyVector& other) : data(nullptr), size_(other.size_), capacity_(other.capacity_) {
        data = new int[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data[i] = other.data[i];
        }
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data = new int[capacity_];
            for (size_t i = 0; i < size_; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push_back(int value) {
        if (size_ == capacity_) {
            resize(capacity_ == 0 ? 1 : 2 * capacity_);
        }
        data[size_++] = value;
    }

    void pop_back() {
        if (size_ == 0) {
            throw out_of_range("Vector is empty");
        }
        --size_;
    }

    int& operator[](size_t index) {
        if (index >= size_) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const int& operator[](size_t index) const {
        if (index >= size_) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        size_ = 0;
    }

    int& at(size_t index) {
        if (index >= size_) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const int& at(size_t index) const {
        if (index >= size_) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    void print() const {
        for (size_t i = 0; i < size_; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    int& back() {
        if (size_ == 0) {
            throw out_of_range("Vector is empty");
        }
        return data[size_ - 1];
    }

    const int& back() const {
        if (size_ == 0) {
            throw out_of_range("Vector is empty");
        }
        return data[size_ - 1];
    }
};

class BigInt {
private:
    MyVector data;

public:
    BigInt() {}
    friend ostream& operator<<(ostream& os, const BigInt& b) {
        for (int i = b.data.size() - 1; i >= 0; --i) {
            os << b.data[i];
        }
        return os;
    }

    friend istream& operator>>(istream& is, BigInt& b) {
        string s; is >> s ;
        for (int i = s.size() - 1; i >= 0; --i) {
            b.data.push_back(s[i] - '0');
        }
        return is;
    }
    bool operator < (const BigInt& b) const {
        if (this->data.size() != b.data.size()) {
            return this->data.size() < b.data.size();
        }
        for (int i = 0; i < this->data.size(); ++i) {
            if (this->data[i] != b.data[i]) {
                return this->data[i] < b.data[i];
            }
        }
        return false;
    }
    BigInt operator+(const BigInt& b) {
        BigInt sum;
        int carry = 0;
        size_t maxSize = std::max(this->data.size(), b.data.size());

        for (size_t i = 0; i < maxSize || carry; ++i) {
            int x = carry;
            if (i < this->data.size()) x += this->data[i];
            if (i < b.data.size()) x += b.data[i];
            sum.data.push_back(x % 10);
            carry = x / 10;
        }
        return sum;
    }
    BigInt operator-(const BigInt& b) {
        BigInt result;
        int borrow = 0;
        size_t maxSize = std::max(this->data.size(), b.data.size());

        for (size_t i = 0; i < maxSize; ++i) {
            int x = this->data[i] - borrow;
            if (i < b.data.size()) x -= b.data[i];

            if (x < 0) { x += 10; borrow = 1;}
            else {borrow = 0;}

            result.data.push_back(x);
        }

        while (result.data.size() > 1 && result.data.back() == 0) {
            result.data.pop_back();
        }

        return result;
    }
    BigInt operator*(BigInt& b) {
        BigInt product = BigInt();
        for ( int i = 0 ; i < this->data.size() + b.data.size() ; ++i ) {
            product.data.push_back(0);
        }
        for ( int i = 0 ; i < this->data.size() ; ++i ) {

            int carry = 0;
            int j;
            for ( j = 0 ; j < b.data.size() ; ++j ) {
                int x = this->data[i] * b.data[j] + carry + product.data[i+j];
                product.data[i+j] = x % 10;
                carry = x / 10;
            }
            if (carry) product.data[i+j] = carry;
        }
        if (product.data[product.data.size()-1] == 0) {
            product.data.pop_back();
        }
        return product;
    }
    BigInt operator *(int n) {
        BigInt product = BigInt();
        BigInt temp1 = BigInt();
        BigInt temp2 = BigInt();
        temp2.data = this->data;
        while (n !=0) {
            temp1.data.push_back(n % 10);
            n /= 10;
        }
        return temp1 * temp2;
    }
     BigInt Fibonacci(int n) {
        if (n == 0) {
            BigInt fib;
            fib.data.push_back(0);
            return fib;
        }
        if (n == 1) {
            BigInt fib;
            fib.data.push_back(1);
            return fib;
        }

        BigInt a, b;
        a.data.push_back(0);
        b.data.push_back(1);

        for (int i = 2; i <= n; ++i) {
            BigInt tmp = a + b;
            a = b;
            b = tmp;
        }

        return b;
    }

    BigInt Factor(int n) {
        BigInt res;
        if (n == 1){BigInt a ; a.data.push_back(1); return a;}
        if (n == 2){BigInt a ; a.data.push_back(2); return a;}

        BigInt a = BigInt();
        a.data.push_back(1);
        for ( int i = 1 ; i <= n ; ++i) {
            a = a * i;
        }
        return a;
    }
};

int main() {
    int key;
    while (true) {
        cout << "CHUONG TRINH THAO TAC VOI SO NGUYEN LON C/C++\n";
        cout << "*************************MENU**************************\n";
        cout << "**  1. CONG HAI SO NGUYEN LON                        **\n";
        cout << "**  2. TRU HAI SO NGUYEN LON                         **\n";
        cout << "**  3. NHAN HAI SO NGUYEN LON                        **\n";
        cout << "**  4. TIM SO FIBONACCI THU N VOI (1 <= N <= 1000)   **\n";
        cout << "**  5. TIM GIAI THUA SO N LON VOI (1 <= N <= 1000)   **\n";
        cout << "**  0. Thoat                                         **\n";
        cout << "*******************************************************\n";
        cout << "Nhap tuy chon: ";
        cin >> key;

        switch (key) {
            case 1: {
                BigInt a, b;
                cout << "Nhap so nguyen thu 1: "; cin >> a;
                cout << "Nhap so nguyen thu 2: "; cin >> b;
                if (a < b) swap(a,b);
                cout << "Tong hai so nguyen: " << a + b << endl;
                break;
            }
            case 2: {
                BigInt c, d;
                if (c < d) {
                    cout << "Chuong trinh khong ho tro so nguyen am!!!!\n";
                    cout << "Vui long nhap so co gia tri lon hon dau tien!!!!\n";
                }else {
                    cout << "Nhap so nguyen thu 1: "; cin >> c;
                    cout << "Nhap so nguyen thu 2: "; cin >> d;
                    cout << "Hieu hai so nguyen: " << c - d << endl;
                }
                break;
            }
            case 3: {
                BigInt m, n;
                cout << "Nhap so nguyen thu 1: "; cin >> m;
                cout << "Nhap so nguyen thu 2: "; cin >> n;
                cout << "Tich cua hai so nguyen: " << m * n << endl;
                break;
            }
            case 4: {
                int z;
                cout << "Nhap so Fibonacci thu n: "; cin >> z;
                if (z < 1 || z > 1000) {
                    cout << "Chi nhap so nguyen tu 1 den 1000!!!" << endl;
                } else {
                    BigInt fib;
                    cout << "So Fibonacci thu n la: " << fib.Fibonacci(z) << endl;
                }
                break;
            }
            case 5: {
                int k;
                cout << "Nhap so nguyen n: "; cin >> k;
                if (k < 1 || k > 1000) {
                    cout << "Chi nhap so nguyen tu 1 den 1000!!!" << endl;
                } else {
                    BigInt fac;
                    cout << "Gia thua cua so n la: " << fac.Factor(k) << endl;
                }
                break;
            }
            case 0:
                cout << "Thoat chuong trinh.\n";
                return 0; // Kết thúc chương trình
            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }

        cout << "Nhap ki tu bat ky de tiep tuc...";
        PressAnyKey();
        system("cls");
    }
}

