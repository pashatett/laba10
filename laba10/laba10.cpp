#include <iostream>
#include <sstream>
#include <cmath>

#define EPS 0.000000001

using namespace std;

class my_complex {
    double Re, Im;

public:
    my_complex() : Re(0), Im(0) {}
    my_complex(double a, double b = 0) : Re(a), Im(b) {}
    my_complex(const my_complex& X) : Re(X.Re), Im(X.Im) {} // Исправленный конструктор копирования
    ~my_complex() {}

    void setRe(double x) { Re = x; }
    void setIm(double x) { Im = x; }
    double getRe() const { return Re; }
    double getIm() const { return Im; }

    friend void print_complex(const my_complex& A);
    friend my_complex operator+(const my_complex& A, const my_complex& B);
    friend my_complex operator-(const my_complex& A, const my_complex& B);
    friend my_complex operator*(const my_complex& A, const my_complex& B);
    friend my_complex operator/(const my_complex& A, const my_complex& B);
    friend bool operator!=(const my_complex& A, const my_complex& B);
    friend bool operator==(const my_complex& A, const my_complex& B);
    friend float modul(const my_complex& A);
    friend string trigonometric(const my_complex& A);
    friend ostream& operator<<(std::ostream& out, const my_complex& X);

    my_complex& operator=(const my_complex& A) {
        if (&A == this)
            return *this;
        this->Re = A.Re;
        this->Im = A.Im;
        return *this;
    }

    string toString() const {
        ostringstream ss;
        if (abs(Im) < EPS) {
            ss << Re;
            return ss.str();
        }
        if (Im > 0)
            ss << Re << "+" << Im << "i";
        else
            ss << Re << Im << "i";
        return ss.str();
    }
};

ostream& operator<<(std::ostream& out, const my_complex& X) {
    out << X.toString();
    return out;
}

bool operator==(const my_complex& A, const my_complex& B) {
    return (abs(A.Re - B.Re) < EPS && abs(A.Im - B.Im) < EPS);
}

my_complex operator+(const my_complex& A, const my_complex& B) {
    return my_complex(A.Re + B.Re, A.Im + B.Im);
}

bool operator!=(const my_complex& A, const my_complex& B) {
    return !(A == B);
}

my_complex operator-(const my_complex& A, const my_complex& B) {
    return my_complex(A.Re - B.Re, A.Im - B.Im);
}

my_complex operator*(const my_complex& A, const my_complex& B) {
    return my_complex(A.Re * B.Re - A.Im * B.Im, A.Re * B.Im + B.Re * A.Im);
}

my_complex operator/(const my_complex& A, const my_complex& B) {
    double denominator = B.Re * B.Re + B.Im * B.Im;
    return my_complex((A.Re * B.Re + A.Im * B.Im) / denominator,
        (A.Im * B.Re - A.Re * B.Im) / denominator);
}

float modul(const my_complex& A) {
    return sqrt(A.Re * A.Re + A.Im * A.Im);
}

string trigonometric(const my_complex& A) {
    double r = modul(A);
    double arg = atan2(A.Im, A.Re);
    return to_string(r) + "(cos " + to_string(arg) + " + i sin " + to_string(arg) + ")";
}

void print_complex(const my_complex& A) {
    cout << A.Re;
    if (A.Im < 0)
        cout << A.Im << "i" << endl;
    else
        cout << "+" << A.Im << "i" << endl;
}

int main() {
    setlocale(LC_ALL, "");
    my_complex a(3, 4), b(3, 4);
    my_complex c = a - b;
    cout << "a - b = " << c << endl;
    my_complex d = a * b;
    cout << "a * b = " << d << endl;
    my_complex e = a / b;
    cout << "a / b = " << e << endl;
    cout << "a != b? ";
    if (a != b)
        cout << "Да" << endl;
    else
        cout << "Нет" << endl;

    cout << "|a| = " << modul(a) << endl;
    cout << "a в триг. форме: " << trigonometric(a) << endl;

    return 0;
}