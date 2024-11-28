#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
class Sinhvien {
private:
    string ten;
    string diachi;
    int masinhvien;
    int tuoi;
    float diemtrungbinh;
    string hocluc;

public:
    friend ostream& operator<<(ostream& os, const Sinhvien& obj) {
        os << "       Ho va ten sinh vien : " << obj.ten << endl;
        os << "       Ma sinh vien : " << obj.masinhvien << endl;
        os << "       Dia chi cua sinh vien : " << obj.diachi << endl;
        os << "       Tuoi cua sinh vien : " << obj.tuoi << endl;
        os << "       Diem trung binh cua sinh vien : " << obj.diemtrungbinh << endl;
        os << "       Hoc luc cua sinh vien : " << obj.hocluc << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Sinhvien& obj) {
        cout << "Nhap ho va ten cua sinh vien : ";
        getline(is, obj.ten);

        cout << "Nhap dia chi cua sinh vien : ";
        getline(is, obj.diachi);

        cout << "Nhap ma sinh vien : ";
        is >> obj.masinhvien;

        cout << "Nhap tuoi cua sinh vien : ";
        is >> obj.tuoi;
        is.ignore();

        cout << "Nhap diem trung binh cua sinh vien : ";
        is >> obj.diemtrungbinh;
        is.ignore();

        cout << "Nhap hoc luc cua sinh vien : ";
        getline(is, obj.hocluc);

        return is;
    }
    void setten(string ten) {
        this->ten = ten;
    }

    void setdiachi(string diachi) {
        this->diachi = diachi;
    }

    void setmsv(int msv) {
        this->masinhvien = msv;
    }

    void settuoi(int tuoi) {
        this->tuoi = tuoi;
    }

    void setdiemtrungbinh(float diemtrungbinh) {
        this->diemtrungbinh = diemtrungbinh;
    }

    void sethocluc(string hocluc) {
        this->hocluc = hocluc;
    }


    bool TimMaSinhVien(int masinhvien) {
        return masinhvien == this->masinhvien;
    }

    string LayHocLuc() {
        return hocluc;
    }
    bool operator < (const Sinhvien &other) const {
        return this->diemtrungbinh < other.diemtrungbinh;
    }

};

class Quanli {
private:
    vector<Sinhvien> sinhvien;
public:
    Quanli() {
        ifstream file("D:/Program/Exercise/sinhvien.txt");

        if (!file.is_open()) {
            cout << "ko the mo file!!" << endl;
            return;
        }

        Sinhvien sv;
        string line;
        while (getline(file, line)) {
            sv.setten(line);
            getline(file, line);
            sv.setdiachi(line);
            getline(file, line);
            sv.setmsv(stoi(line));
            getline(file, line);
            sv.settuoi(stoi(line));
            getline(file, line);
            sv.setdiemtrungbinh(stof(line));
            getline(file, line);
            sv.sethocluc(line);

            sinhvien.push_back(sv);
        }
        file.close();
    };
    void InSinhVienVuaNhap() {
        for (size_t i = 0; i < sinhvien.size(); i++) {
            cout << "Sinh vien thu " << i + 1 << " : " << endl;
            cout <<sinhvien[i] << endl;
        }
    };
    void CapNhatSinhVien() {
        int msv ;
        cout << "Nhap ma sinh vien muon cap nhat : ";
        cin >> msv;
        cout << "Nhap cac thong tin muon cap nhat : \n";
        string diachi , hocluc;
        int tuoi; float diem;
        cout << "Nhap dia chi : " ;
        cin.ignore();
        getline(cin, diachi);
        cout << "Nhap tuoi : ";
        cin >> tuoi;
        cout << "Nhap diem : ";
        cin >> diem;
        cout << "Nhap hoc luc : ";
        cin.ignore();
        getline(cin, hocluc);
        for ( int i = 0 ; i < sinhvien.size(); i++) {
            if (sinhvien[i].TimMaSinhVien(msv)) {
                sinhvien[i].setdiachi((diachi));
                sinhvien[i].settuoi((tuoi));
                sinhvien[i].setdiemtrungbinh((diem));
                sinhvien[i].sethocluc((hocluc));
                break;
            }
        }
        cout << "Da cap nha sinh vien !!!!!!!" << endl;
    };
    void TimSinhVien() {
        int n ;
        cout << "Nhap ma sinh vien : " ; cin >> n ;
        for ( int i = 0 ; i < sinhvien.size(); i++) {
            if (sinhvien[i].TimMaSinhVien(n)) {
                cout << "Da tinh thay sinh vien : " << endl;
                cout << sinhvien[i] << endl;
                break;
            }
        }
        cout << "Khong tim thay sinh vien !!!!!!" << endl;
    }
    void ThemSinhVien() {
        Sinhvien tmp;
        cout << "Nhap thong tin sinh vien muon them : " << endl;
        cin >> tmp;
        sinhvien.push_back(tmp);
        cout << "Da them sinh vien thanh cong!!!!" << endl;
    };
    void XoaSinhVien() {
        Sinhvien tmp;
        cout << "Nhap ma sinh vien muon xoa : ";
        int n ; cin >> n ;
        for ( int i = 0 ; i < sinhvien.size(); i++) {
            if (sinhvien[i].TimMaSinhVien(n)) {
                sinhvien.erase(sinhvien.begin()+i);
                break;
            }
        }
        cout << "Da xoa sinh vien !!!!!!" << endl;
    };
    void DiemCaoNhat() {
        auto diemcaonhat = *max_element(sinhvien.begin(), sinhvien.end());
        cout << diemcaonhat << endl;
    };
    void PhanLoaiHocLuc() {
        fs::path filepath = fs::current_path();
        fs::path file_path =filepath.parent_path() / "phanloaisinhvien.txt";
        ofstream file(file_path, ios::trunc);

        if (!file) {
            cerr << "Can't open file \"phanloaisinhvien.txt\"" << endl;
            exit(1);
        }
        vector<Sinhvien> Yeu , Trungbinh , Kha , Gioi;
        for ( int i = 0 ; i < sinhvien.size(); i++) {
            if (sinhvien[i].LayHocLuc() == "Yeu") {
                Yeu.push_back(sinhvien[i]);
            } else if (sinhvien[i].LayHocLuc() == "Trung binh") {
                Trungbinh.push_back(sinhvien[i]);
            } else if (sinhvien[i].LayHocLuc() == "Kha") {
                Kha.push_back(sinhvien[i]);
            } else if (sinhvien[i].LayHocLuc() == "Gioi") {
                Gioi.push_back(sinhvien[i]);
            }
        }

        if (Gioi.size() != 0) {
            cout << "Cac sinh vien dat hoc luc gioi : " << endl;
            file << "Cac sinh vien dat hoc luc gioi : " << endl;
            for ( int i = 0 ; i < Gioi.size(); i++) {
                cout << Gioi[i] << endl;
                file << Gioi[i] << endl;
            }
        }

        if(Kha.size() != 0) {
            cout << "Cac sinh vien dat hoc luc kha : " << endl;
            file << "Cac sinh vien dat hoc luc kha : " << endl;
            for ( int i = 0 ; i < Kha.size(); i++) {
                cout << Kha[i] << endl;
                file << Kha[i] << endl;
            }
        }

        if(Trungbinh.size() != 0) {
            cout << "Cac sinh vien dat hoc luc trung binh : " << endl;
            file << "Cac sinh vien dat hoc luc trung binh : " << endl;
            for ( int i = 0 ; i < Trungbinh.size(); i++) {
                cout << Trungbinh[i] << endl;
                file << Trungbinh[i] << endl;
            }
        }

        if(Yeu.size() != 0) {
            cout << "Cac sinh vien dat hoc luc yeu : " << endl;
            file << "Cac sinh vien dat hoc luc yeu : " << endl;
            for ( int i = 0 ; i < Yeu.size(); i++) {
                cout << Yeu[i] << endl;
                file << Yeu[i] << endl;
            }
        }

    }
    void SapXepTheoDiem() {
        sort(sinhvien.begin(), sinhvien.end());
    }

    void ghiFile() {
        fs::path filepath = fs::current_path();
        fs::path file_path =filepath.parent_path() / "danhsach.txt";
        ofstream file(file_path, ios::trunc);

        if (!file) {
            cerr << "Can't open file \"danhsach.txt\"" << endl;
            exit(1);
        }
        file << "Danh sach sinh vien : "<< endl;
        for ( int i = 0 ; i < sinhvien.size(); i++) {
            file << "   Sinh vien thu " <<  i + 1 << " : " << endl;
            file << sinhvien[i] << endl;
        }
    }
};
class App {
private:
    Quanli quanli;
public:
    void Menu() {
        int key;
        while (true) {
            // Hiển thị menu
            cout << "CHUONG TRINH QUAN LY SINH VIEN C/C++\n";
            cout << "*************************MENU****************************\n";
            cout << "**  1. Them sinh vien.                                 **\n";
            cout << "**  2. Cap nhat thong tin sinh vien.                   **\n";
            cout << "**  3. Xoa sinh vien bang ma sinh vien.                **\n";
            cout << "**  4. Tim kiem sinh vien bang ma sinh vien.           **\n";
            cout << "**  5. Sap xep sinh vien theo diem trung binh.         **\n";
            cout << "**  6. Hien thi danh sach sinh vien.                   **\n";
            cout << "**  7. Hien thi sinh vien co diem trung binh cao nhat. **\n";
            cout << "**  8. Phan loai hoc luc .                             **\n";
            cout << "**  0. Thoat                                           **\n";
            cout << "*********************************************************\n";
            cout << "Nhap tuy chon: ";
            cin >> key;
            cin.ignore();
            switch (key) {
                case 1:
                    quanli.ThemSinhVien();
                break;
                case 2:
                    quanli.CapNhatSinhVien();
                break;
                case 3:
                    quanli.XoaSinhVien();
                break;
                case 4:
                    quanli.TimSinhVien();
                break;
                case 5:
                    quanli.SapXepTheoDiem();
                break;
                case 6:
                    quanli.InSinhVienVuaNhap();
                quanli.ghiFile();
                break;
                case 7:
                    quanli.DiemCaoNhat();
                break;
                case 8:
                    quanli.PhanLoaiHocLuc();
                break;
                case 0:
                    cout << "Ban da thoat chuong trinh.\n";
                return;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                break;
            }

            cout << endl;
        }
    }
};
int main() {
    App app;
    app.Menu();
    return 0;
}
