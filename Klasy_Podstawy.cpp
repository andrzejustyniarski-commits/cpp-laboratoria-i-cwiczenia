#include <iostream>
#include <string>

using namespace std;

// --- Zadanie 1 i 4: Lista inicjalizacyjna oraz Składowe Statyczne ---
class Employee {
private:
    const int id;
    string name;

public:
    static int active_instances;

    // Lista inicjalizacyjna
    Employee(int emp_id, string emp_name) : id(emp_id), name(emp_name) {
        active_instances++;
    }

    ~Employee() {
        active_instances--;
    }

    static int get_active_instances() {
        return active_instances;
    }

    void display() const {
        cout << "Pracownik ID: " << id << ", Imie: " << name << "\n";
    }
};

// Inicjalizacja składowej statycznej poza klasą
int Employee::active_instances = 0;

// --- Zadanie 2: Delegowanie Konstruktorów ---
class Window {
private:
    int width, height;
    string title;

public:
    // Główny konstruktor
    Window(int w, int h, string t) : width(w), height(h), title(t) {}

    // Delegowanie do głównego
    Window(int w, int h) : Window(w, h, "Untitled") {}

    // Delegowanie do konstruktora z dwoma parametrami
    Window() : Window(800, 600) {}

    void show() const { 
        cout << "Okno: " << title << " [" << width << "x" << height << "]\n"; 
    }
};

// --- Zadanie 3: Destruktor i RAII ---
class Buffer {
private:
    int* data;
    int size;

public:
    Buffer(int s) : size(s) {
        data = new int[size];
        cout << "Allocated " << size << "\n";
    }

    ~Buffer() {
        delete[] data;
        cout << "Deallocated\n";
    }
};

int main() {
    cout << "--- Test Zadania 1 i 4 ---\n";
    cout << "Aktywne instancje: " << Employee::get_active_instances() << "\n";
    {
        Employee e1(1, "Jan");
        Employee e2(2, "Anna");
        e1.display();
        cout << "Aktywne instancje (w bloku): " << Employee::get_active_instances() << "\n";
    }
    cout << "Aktywne instancje (poza blokiem): " << Employee::get_active_instances() << "\n\n";

    cout << "--- Test Zadania 2 ---\n";
    Window w1(1920, 1080, "Main Window");
    Window w2(1024, 768);
    Window w3;
    w1.show();
    w2.show();
    w3.show();
    cout << "\n";

    cout << "--- Test Zadania 3 ---\n";
    cout << "Start\n";
    {
        Buffer b(100);
    } // Tutaj automatycznie wywoła się destruktor
    cout << "End\n";

    return 0;
}