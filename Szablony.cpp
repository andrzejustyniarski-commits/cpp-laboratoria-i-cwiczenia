#include <iostream>
#include <string>

using namespace std;

// Zadanie 4 i 5: Szablon klasy i definicje metod poza ciałem klasy
template <typename T>
class Box {
private:
    T value;
public:
    Box(T val) : value(val) {}
    T getValue() const;
    void setValue(T newValue);
};

// Definicje metod poza klasą wymagają nagłówka szablonu
template <typename T>
T Box<T>::getValue() const {
    return value;
}

template <typename T>
void Box<T>::setValue(T newValue) {
    value = newValue;
}

// Zadanie 7: Specjalizacja szablonu dla typu bool
template <> 
class Box<bool> {
private:
    bool value;
public:
    Box(bool val) : value(val) {}
    string getStatus() const {
        return value ? "TAK" : "NIE";
    }
};

// Zadanie 6: Parametry szablonu niebędące typami (non-type)
template <typename T, int size>
class StaticArray {
private:
    T data[size];
public:
    int getSize() const { 
        return size; 
    }
    
    void set(int index, T value) { 
        data[index] = value; 
    }
    
    T get(int index) const { 
        return data[index]; 
    }
};

int main() {
    cout << "--- Zadanie 4, 5 i 7: Szablon klasy i specjalizacja ---\n";
    Box<int> intBox(42);
    cout << "Wartosc Box<int>: " << intBox.getValue() << "\n";

    Box<string> strBox("Witaj Szablonie");
    cout << "Wartosc Box<string>: " << strBox.getValue() << "\n";

    Box<bool> boolBox(true);
    cout << "Wartosc Box<bool> (getStatus): " << boolBox.getStatus() << "\n\n";

    cout << "--- Zadanie 6: Parametry non-type ---\n";
    StaticArray<double, 5> arr;
    arr.set(0, 3.14);
    cout << "Rozmiar tablicy: " << arr.getSize() << "\n";
    cout << "Pierwszy element: " << arr.get(0) << "\n";

    return 0;
}