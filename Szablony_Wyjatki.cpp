#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// --- Zadanie 7: Szablony Funkcji ---
template <typename T>
T znajdzWiekszy(T a, T b) {
    return (a > b) ? a : b;
}

// --- Zadanie 8: Wyjątki (try-catch) ---
double podziel(double licznik, double mianownik) {
    if (mianownik == 0.0) {
        throw invalid_argument("Blad: Dzielenie przez zero!");
    }
    return licznik / mianownik;
}

// --- Zadanie 9: Własne Klasy Wyjątków ---
class EmployeeException : public runtime_error {
public:
    EmployeeException(const string& msg) : runtime_error(msg) {}
};

class InvalidSalaryException : public EmployeeException {
public:
    InvalidSalaryException(const string& msg) : EmployeeException(msg) {}
};

// Prosta klasa testowa dla wyjatkow biznesowych
class ManagerData {
private:
    string name;
    double base_salary;
public:
    ManagerData(string n, double salary) : name(n) {
        if (salary < 4000.0) {
            throw InvalidSalaryException("Pensja " + to_string(salary) + " jest ponizej placy minimalnej (4000)!");
        }
        base_salary = salary;
        cout << "Poprawnie utworzono managera: " << name << "\n";
    }
};

int main() {
    cout << "--- Zadanie 7: Szablony Funkcji ---\n";
    cout << "Wiekszy int (5 czy 10): " << znajdzWiekszy(5, 10) << "\n";
    cout << "Wiekszy double (3.14 czy 2.71): " << znajdzWiekszy(3.14, 2.71) << "\n";
    cout << "Wiekszy string (Ala czy Kot): " << znajdzWiekszy(string("Ala"), string("Kot")) << "\n\n";

    cout << "--- Zadanie 8: Wyjatki przy dzieleniu ---\n";
    try {
        cout << "10 / 2 = " << podziel(10, 2) << "\n";
        cout << "10 / 0 = " << podziel(10, 0) << "\n";
        cout << "To sie nie wypisze\n";
    } catch (const invalid_argument& e) {
        cerr << "Przechwycono wyjatek: " << e.what() << "\n";
    }
    cout << "\n";

    cout << "--- Zadanie 9: Kaskadowa obsluga wlasnych wyjatkow ---\n";
    try {
        ManagerData m1("Anna Szefowa", 5000.0);
        ManagerData m2("Jan Stazysta", 2500.0); // To wyrzuci wyjatek
    } 
    catch (const InvalidSalaryException& e) {
        cerr << "Wyjatek wyplaty: " << e.what() << "\n";
    } 
    catch (const EmployeeException& e) {
        cerr << "Ogolny wyjatek pracowniczy: " << e.what() << "\n";
    } 
    catch (const exception& e) {
        cerr << "Inny wyjatek standardowy: " << e.what() << "\n";
    }

    return 0;
}