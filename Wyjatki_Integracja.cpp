#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Zadanie 8: Wyjątki i specyfikator noexcept
template <typename T>
class SimpleContainer {
private:
    T value;
public:
    SimpleContainer(T val) : value(val) {}

    // Obietnica braku wyjątków
    T getValue() const noexcept { 
        return value; 
    }

    void checkAndSet(T val) {
        if (val < 0) { 
            throw out_of_range("Wartosc nie moze byc ujemna!");
        }
        value = val;
    }
};

// Funkcja szablonowa sprawdzająca bezpieczeństwo metody w czasie kompilacji
template <typename T>
void safe_call(T obj) {
    if constexpr (noexcept(obj.getValue())) {
        cout << "[safe_call] Bezpieczne wywolanie getValue(): " << obj.getValue() << "\n";
    }
}

// Zadanie 9: Integracja - Szablonowy SafeArray
template <typename T, int size>
class SafeArray {
private:
    T data[size];
public:
    // Wersja do modyfikacji elementów
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Indeks poza zakresem!");
        }
        return data[index];
    }

    // Wersja do odczytu obiektów const
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Indeks poza zakresem!");
        }
        return data[index];
    }
};

int main() {
    cout << "--- Zadanie 8: noexcept ---\n";
    SimpleContainer<int> container(100);
    safe_call(container);
    cout << "\n";

    cout << "--- Zadanie 9: Szablonowy SafeArray ---\n";
    SafeArray<string, 3> words;
    words[0] = "Zadanie";
    words[1] = "zrobione";
    words[2] = "wzorowo";

    try {
        cout << "Proba dostepu do words[3]...\n";
        // Celowe wywołanie błędu (indeks 3 w tablicy 3-elementowej)
        cout << words[3] << "\n"; 
    } catch (const out_of_range& e) {
        cout << "Przechwycono wyjatek: " << e.what() << "\n";
    }

    return 0;
}