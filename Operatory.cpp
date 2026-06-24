#include <iostream>

using namespace std;

class Vector2D {
private:
    double x, y;

public:
    Vector2D(double val_x = 0.0, double val_y = 0.0) : x(val_x), y(val_y) {}

    // Zadanie 1: Przeciążanie operatorów binarnych (+, -)
    [[nodiscard]] Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    [[nodiscard]] Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    void display() const {
        cout << "[" << x << ", " << y << "]\n";
    }

    // Zadanie 2: Przeciążanie operatorów porównania (==, !=)
    bool operator==(const Vector2D& other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }

    // Zadanie 3: Operator strumieniowy (funkcja zaprzyjaźniona)
    friend ostream& operator<<(ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os; // Zwracanie referencji umożliwia kaskadowość
    }
};

int main() {
    cout << "--- Zadanie 1 i 3: Operatory binarne i strumieniowe ---\n";
    Vector2D v1(3.5, 2.0);
    Vector2D v2(1.5, 4.0);
    
    cout << "v1: " << v1 << "\n";
    cout << "v2: " << v2 << "\n";
    cout << "v1 + v2 = " << (v1 + v2) << "\n";
    cout << "v1 - v2 = " << (v1 - v2) << "\n\n";

    cout << "--- Zadanie 2: Operatory porownania ---\n";
    Vector2D v3(3.5, 2.0);
    cout << boolalpha; // Wymuszenie wyświetlania true/false
    cout << "Czy v1 == v2? " << (v1 == v2) << "\n";
    cout << "Czy v1 == v3? " << (v1 == v3) << "\n";
    cout << "Czy v1 != v2? " << (v1 != v2) << "\n";

    return 0;
}