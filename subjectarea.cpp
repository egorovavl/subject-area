#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Dish {
private:
    string name;
    double price;
public:
    Dish(string name, double price) {
        this->name = name;
        this->price = price;
    }
    string getName() {
        return name;
    }
    double getPrice() {
        return price;
    }
};

class Order {
private:
    vector<Dish> dishes;
    double total;
public:
    void addDish(Dish dish, int quantity = 1) {
        for (int i = 0; i < quantity; i++) {
            dishes.push_back(dish);
        }
        total += dish.getPrice() * quantity;
    }
    void display() {
        cout << "Order:" << endl;
        for (int i = 0; i < dishes.size(); i++) {
            cout << "- " << dishes[i].getName() << " ($" << dishes[i].getPrice() << ")" << endl;
        }
        cout << "Total: $" << total << endl;
    }
};


class Person {
protected:
    string firstName;
    string lastName;
    int age;
public:
    Person(string firstName, string lastName, int age) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
    }
    void display() {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Age: " << age << endl;
    }
};

class Waiter : public Person {
private:
    double salary;
public:
    Waiter(string firstName, string lastName, int age, double salary) : Person(firstName, lastName, age) {
        this->salary = salary;
    }
    void display() {
        Person::display();
        cout << "Salary: $" << salary << endl;
    }
};

class Client : public Person {
private:
    string phoneNumber;
public:
    Client(string firstName, string lastName, int age, string phoneNumber) : Person(firstName, lastName, age) {
        this->phoneNumber = phoneNumber;
    }
    void displayAsPerson() {
        Person::display();
        cout << "Phone number: " << phoneNumber << endl;
    }
    void display() {
        cout << "Dear, " << this->firstName << " " << this->lastName << endl;
    }
};


class Restaurant {
private:
    string name;
    string address;
    double rating;
    vector<Dish> menu;
public:
    Restaurant(string name, string address, double rating) {
        this->name = name;
        this->address = address;
        this->rating = rating;
    }
    void addDish(string name, double price) {
        menu.push_back(Dish(name, price));
    }
    void display() {
        cout << "Restaurant:" << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Rating: " << rating << endl;
        cout << "Menu:" << endl;
        for (int i = 0; i < menu.size(); i++) {
            cout << "- " << menu[i].getName() << " ($" << menu[i].getPrice() << ")" << endl;
        }
        cout << endl;
    }
    friend void makeOrder(Restaurant& restaurant, Client& client);
};



void makeOrder(Restaurant& restaurant, Client& client) {
    cout << "Welcome to " << restaurant.name << "!" << endl;
    cout << "Please make your order:" << endl;
    Order order;
    int choice;
    do {
        cout << "Menu:" << endl;
        for (int i = 0; i < restaurant.menu.size(); i++) {
            cout << i + 1 << ". " << restaurant.menu[i].getName() << " ($" << restaurant.menu[i].getPrice() << ")" << endl;
        }
        cout << "0. Done" << endl;
        cout << "Choice: ";
        string input;
        getline(cin, input);
        stringstream ss(input);
        ss >> choice;
        if (choice >= 1 && choice <= restaurant.menu.size()) {
            order.addDish(restaurant.menu[choice - 1]);
        }
        else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);
    cout << endl;
    cout << "Your order:" << endl;
    order.display();
    cout << endl;
}

int main() {
    Restaurant restaurant("Mama mia pizzeria", "123 Main St", 4.5);
    restaurant.addDish("Pizza", 10.99);
    restaurant.addDish("Pasta", 8.99);
    restaurant.addDish("Salad", 5.99);
    restaurant.display();
    cout << "=================\nYour waiter:\n";
    Waiter waiter("Peter", "Parker", 25, 500.0);
    waiter.display();
    cout << "=================" << endl;
    Client client("Valeriya", "Egorova", 30, "555-1234");
    client.display();

    makeOrder(restaurant, client);
}
