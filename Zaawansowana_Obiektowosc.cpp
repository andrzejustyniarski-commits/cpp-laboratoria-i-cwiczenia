#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Zadanie 5: Interfejsy jako Kontrakty ---
class IReportable {
public:
    virtual string getReport() const = 0;
    virtual ~IReportable() = default;
};

// --- Zadanie 6: Kompozycja (Relacja "has-a") ---
class Task {
public:
    string description;
    int priority;

    Task(string desc, int prio) : description(desc), priority(prio) {}
};

// Klasa abstrakcyjna implementująca interfejs
class Employee : public IReportable {
protected:
    string name;
    int id;
    vector<Task> tasks; // Kompozycja: Employee posiada zadania

public:
    Employee(string n, int i) : name(n), id(i) {}

    // --- Zadanie 1: Wirtualny Destruktor ---
    virtual ~Employee() {
        cout << "Destruktor Employee: " << name << "\n";
    }

    virtual void display() const = 0;
    virtual double calculate_salary() const = 0;

    void assignTask(const string& desc, int prio) {
        tasks.push_back(Task(desc, prio));
    }

    void displayTasks() const {
        if (tasks.empty()) {
            cout << "  Brak przypisanych zadan.\n";
            return;
        }
        cout << "  Zadania:\n";
        for (const auto& task : tasks) {
            cout << "   - [" << task.priority << "] " << task.description << "\n";
        }
    }
};

// --- Zadanie 2: override i final ---
class Manager final : public Employee { 
private:
    float bonus;

public:
    Manager(string n, int i, float b) : Employee(n, i), bonus(b) {}

    ~Manager() override {
        cout << "Destruktor Manager: " << name << "\n";
    }

    void display() const override {
        cout << "Manager: " << name << " (ID: " << id << ")\n";
        displayTasks();
    }

    double calculate_salary() const override final {
        return 10000.0 + bonus;
    }

    // --- Zadanie 4: Specyficzna metoda do testu dynamic_cast ---
    void scheduleMeeting() const {
        cout << "  Manager " << name << " ustala spotkanie zarzadu.\n";
    }

    string getReport() const override {
        return "RAPORT MANAGERA: " + name + ", Pensja: " + to_string(calculate_salary());
    }
};

class Developer : public Employee {
public:
    Developer(string n, int i) : Employee(n, i) {}

    ~Developer() override {
        cout << "Destruktor Developer: " << name << "\n";
    }

    void display() const override {
        cout << "Developer: " << name << " (ID: " << id << ")\n";
        displayTasks();
    }

    double calculate_salary() const override {
        return 8500.0;
    }

    string getReport() const override {
        return "RAPORT DEVELOPERA: " + name + ", Pensja: " + to_string(calculate_salary());
    }
};

// Funkcja testujaca interfejs IReportable
void printReport(const IReportable& obj) {
    cout << ">>> " << obj.getReport() << "\n";
}

int main() {
    cout << "--- Zadanie 3: Kolekcje Polimorficzne ---\n";
    vector<Employee*> staff;

    staff.push_back(new Manager("Anna Nowak", 101, 2000.0f));
    staff.push_back(new Developer("Jan Kowalski", 102));
    staff.push_back(new Developer("Piotr Wiśniewski", 103));

    // Przypisanie zadań (Kompozycja)
    staff[0]->assignTask("Zatrudnic nowego stazyste", 1);
    staff[1]->assignTask("Naprawic blad w logowaniu", 2);

    double total_salary = 0.0;

    for (Employee* e : staff) {
        e->display();
        total_salary += e->calculate_salary();

        // --- Zadanie 4: dynamic_cast ---
        Manager* mgr = dynamic_cast<Manager*>(e);
        if (mgr != nullptr) {
            mgr->scheduleMeeting();
        } else {
            cout << "  To nie jest Manager.\n";
        }

        // Test interfejsu
        printReport(*e);
        cout << "\n";
    }

    cout << "Calkowite koszty wynagrodzen: " << total_salary << " PLN\n\n";

    cout << "--- Czyszczenie pamieci (Test wirtualnego destruktora) ---\n";
    for (Employee* e : staff) {
        delete e; 
    }

    return 0;
}