//------------------------1---------------------------------------
#include <cmath>
#include <iostream>
using namespace std;

class my_complex {
private:
	double Re, Im;

public:
	my_complex(double a = 0, double b = 0) : Re(a), Im(b) {}
	my_complex(const my_complex& other) : Re(other.Re), Im(other.Im) {}

	double getRe() const { return Re; }
	double getIm() const { return Im; }
	void setRe(double re) { Re = re; }
	void setIm(double im) { Im = im; }

	double modulus() const {
		return sqrt(Re * Re + Im * Im);
	}

	void toTrigonometricForm(double& r, double& theta) const {
		r = modulus();
		theta = atan2(Im, Re);
	}

	friend my_complex operator-(const my_complex& A, const my_complex& B);
	friend my_complex operator*(const my_complex& A, const my_complex& B);
	friend my_complex operator/(const my_complex& A, const my_complex& B);
	friend bool operator!=(const my_complex& A, const my_complex& B);
	friend ostream& operator<<(ostream& os, const my_complex& c);
};

my_complex operator-(const my_complex& A, const my_complex& B) {
	return my_complex(A.Re - B.Re, A.Im - B.Im);
}

my_complex operator*(const my_complex& A, const my_complex& B) {
	return my_complex(A.Re * B.Re - A.Im * B.Im, A.Re * B.Im + A.Im * B.Re);
}

my_complex operator/(const my_complex& A, const my_complex& B) {
	double denominator = B.Re * B.Re + B.Im * B.Im;
	return my_complex(
		(A.Re * B.Re + A.Im * B.Im) / denominator,
		(A.Im * B.Re - A.Re * B.Im) / denominator
	);
}

bool operator!=(const my_complex& A, const my_complex& B) {
	return !(A.Re == B.Re && A.Im == B.Im);
}

ostream& operator<<(ostream& os, const my_complex& c) {
	os << c.Re << (c.Im >= 0 ? "+" : "") << c.Im << "i";
	return os;
}

void Task1() {
	my_complex a(1, 2), b(3, 4);

	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	cout << "a / b = " << a / b << endl;
	cout << "Modulus of a: " << a.modulus() << endl;

	double r, theta;
	a.toTrigonometricForm(r, theta);
	cout << "Trigonometric form of a: " << r << "(cos(" << theta << ") + i*sin(" << theta << "))" << endl;

	cout << "a != b: " << (a != b ? "true" : "false") << endl;
}


//---------------------------2-----------------------------------------
#include <string>

class Account {
private:
	string ownerName;
	unsigned int accountNumber;
	double interestRate;
	unsigned int balance;

public:
	Account() : ownerName(""), accountNumber(0), interestRate(0.0), balance(0) {}
	Account(const string& name, unsigned int accNum, double rate, unsigned int bal)
		: ownerName(name), accountNumber(accNum), interestRate(rate), balance(bal) {
	}
	Account(const Account& other)
		: ownerName(other.ownerName), accountNumber(other.accountNumber),
		interestRate(other.interestRate), balance(other.balance) {
	}
	~Account() {}

	void changeOwner(const string& newOwner) {
		ownerName = newOwner;
	}

	bool withdraw(unsigned int amount) {
		if (amount > balance) return false;
		balance -= amount;
		return true;
	}

	void deposit(unsigned int amount) {
		balance += amount;
	}

	void addInterest() {
		balance += static_cast<unsigned int>(balance * interestRate / 100.0);
	}

	double toDollars(double exchangeRate) const {
		return balance / exchangeRate;
	}

	double toEuros(double exchangeRate) const {
		return balance / exchangeRate;
	}

	bool operator>(const Account& other) const {
		return balance > other.balance;
	}

	bool operator==(const Account& other) const {
		return balance == other.balance;
	}

	friend ostream& operator<<(ostream& os, const Account& acc);
	friend istream& operator>>(istream& is, Account& acc);
};

ostream& operator<<(ostream& os, const Account& acc) {
	os << "Owner: " << acc.ownerName << ", Account Number: " << acc.accountNumber
		<< ", Balance: " << acc.balance << ", Interest Rate: " << acc.interestRate << "%";
	return os;
}

istream& operator>>(istream& is, Account& acc) {
	cout << "Enter owner name: ";
	getline(is, acc.ownerName);
	cout << "Enter account number: ";
	is >> acc.accountNumber;
	cout << "Enter interest rate (%): ";
	is >> acc.interestRate;
	cout << "Enter initial balance: ";
	is >> acc.balance;
	return is;
}

void Task2() {
	Account acc1("John Doe", 12345, 5.0, 1000);
	Account acc2;

	cin >> acc2;
	cout << acc1 << endl;
	cout << acc2 << endl;

	acc1.deposit(500);
	acc1.addInterest();
	cout << "After deposit and interest: " << acc1 << endl;

	cout << "Account 1 > Account 2: " << (acc1 > acc2 ? "Yes" : "No") << endl;
}


//------------------------3---------------------------------
#include <iostream>
#include <cmath>
using namespace std;

class figure {
protected:
	double x, y;
public:
	figure(double a = 0, double b = 0) : x(a), y(b) {}
	virtual double area() { return 0; }
};

class triangle : public figure {
private:
	double z;
public:
	triangle(double a, double b, double c) : figure(a, b), z(c) {
		if (!(a + b > c && a + c > b && b + c > a)) {
			cout << "Invalid triangle sides!" << endl;
			x = y = z = 0;
		}
	}
	double area() override {
		double p = (x + y + z) / 2;
		return sqrt(p * (p - x) * (p - y) * (p - z));
	}
};

void Task3() {
	triangle t(3, 4, 5);
	cout << "Area of triangle: " << t.area() << endl;
}

//---------------------------------4----------------------------------
#include <iostream>
using namespace std;

class Triad {
protected:
	int first, second, third;
public:
	Triad(int f = 0, int s = 0, int t = 0) : first(f), second(s), third(t) {}
	Triad(const Triad& other) : first(other.first), second(other.second), third(other.third) {}

	bool operator>(const Triad& other) const {
		return (first > other.first) ||
			(first == other.first && second > other.second) ||
			(first == other.first && second == other.second && third > other.third);
	}

	bool operator==(const Triad& other) const {
		return first == other.first && second == other.second && third == other.third;
	}

	friend ostream& operator<<(ostream& os, const Triad& t);
};

ostream& operator<<(ostream& os, const Triad& t) {
	os << "(" << t.first << ", " << t.second << ", " << t.third << ")";
	return os;
}

class Date : public Triad {
public:
	Date(int year = 0, int month = 0, int day = 0) : Triad(year, month, day) {}
	Date(const Date& other) : Triad(other) {}

	bool operator>(const Date& other) const {
		return Triad::operator>(other);
	}

	bool operator==(const Date& other) const {
		return Triad::operator==(other);
	}

	friend ostream& operator<<(ostream& os, const Date& d);
};

ostream& operator<<(ostream& os, const Date& d) {
	os << d.first << "-" << d.second << "-" << d.third;
	return os;
}

void Task4() {
	Date d1(2023, 10, 15);
	Date d2(2023, 10, 16);

	cout << "d1: " << d1 << endl;
	cout << "d2: " << d2 << endl;
	cout << "d1 > d2: " << (d1 > d2 ? "Yes" : "No") << endl;
	cout << "d1 == d2: " << (d1 == d2 ? "Yes" : "No") << endl;
}


//----------------------------5------------------------------
#include <iostream>
#include <stdexcept>
using namespace std;

class InvalidParameterException : public runtime_error {
public:
	InvalidParameterException(const string& msg) : runtime_error(msg) {}
};

double sectorArea(double radius, double angleDegrees) {
	if (radius <= 0) {
		throw InvalidParameterException("Radius must be positive.");
	}
	if (angleDegrees <= 0 || angleDegrees >= 360) {
		throw InvalidParameterException("Angle must be between 0 and 360 degrees.");
	}
	return (3.1415 * radius * radius) * (angleDegrees / 360.0);
}

void Task5() {
	try {
		cout << "Area: " << sectorArea(5, 90) << endl;
		cout << "Area: " << sectorArea(-1, 90) << endl; // Exception
	}
	catch (const InvalidParameterException& e) {
		cerr << "Error: " << e.what() << endl;
	}
}


int main() {
	setlocale(LC_ALL, "");
	cout << "Пирогов Павел Алексеевич 151412 17 вариант" << endl;
	int n;
	cout << "Какое задание вывести?" << endl;
	cout << "0 - Выход" << endl;
	cout << "1 - 1 задание" << endl;
	cout << "2 - 2 задание" << endl;
	cout << "3 - 3 задание" << endl;
	cout << "4 - 4 задание" << endl;
	cout << "5 - 5 задание" << endl;

	cin >> n;
	switch (n) {
	case 0:
		break;
	case 1:
		Task1();
		break;
	case 2:
		Task2();
		break;
	case 3:
		Task3();
		break;
	case 4:
		Task4();
		break;
	case 5:
		Task5();
		break;
	}
}