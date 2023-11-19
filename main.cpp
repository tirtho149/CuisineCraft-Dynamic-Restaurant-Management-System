#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

// Define classes for Customer, Order, MenuItem, and Payment
class Customer {
public:
    std::string name;
    std::string address;
    std::string phone;
};

class MenuItem {
public:
    std::string name;
    double price;

    MenuItem(const std::string& name, double price) : name(name), price(price) {}
};

class Order {
public:
    MenuItem menuItem;
    int quantity;

    Order(const MenuItem& menuItem, int quantity) : menuItem(menuItem), quantity(quantity) {}
};

class Payment {
public:
    double amount;
    std::string paymentMethod;
};

// Define a class for managing the menu
class Menu {
private:
    std::vector<MenuItem> menu;

public:
    // Function to add a new menu item
    void addMenuItem(const std::string& name, double price) {
        menu.emplace_back(name, price);
    }

    // Function to display the menu
    void displayMenu() {
        std::cout << "-------- Menu --------" << std::endl;
        for (const auto& menuItem : menu) {
            std::cout << std::setw(10) << menuItem.name << std::setw(10) << "$" << menuItem.price << std::endl;
        }
        std::cout << "-----------------------" << std::endl;
    }

    // Function to get a menu item by name
    MenuItem getMenuItemByName(const std::string& name) {
        auto menuItem = std::find_if(menu.begin(), menu.end(),
            [name](const MenuItem& item) { return item.name == name; });

        if (menuItem != menu.end()) {
            return *menuItem;
        } else {
            // Return a default item with zero price if not found
            return MenuItem("", 0.0);
        }
    }
};

// Define a class for managing the restaurant
class Restaurant {
private:
    std::vector<Customer> customers;
    std::vector<Order> kitchenOrders;
    Menu menu;
    double usTaxRate = 0.0825; // US tax rate

public:
    // Function to take customer information
    void takeCustomerInformation() {
        Customer customer;
        std::cout << "Enter customer name: ";
        std::getline(std::cin, customer.name);
        std::cout << "Enter customer address: ";
        std::getline(std::cin, customer.address);
        std::cout << "Enter customer phone number: ";
        std::getline(std::cin, customer.phone);

        customers.push_back(customer);
    }

    // Function to take customer orders
    void takeCustomerOrder() {
        menu.displayMenu();

        std::string itemName;
        int quantity;

        std::cout << "Enter item name from the menu: ";
        std::getline(std::cin, itemName);

        auto menuItem = menu.getMenuItemByName(itemName);

        if (menuItem.name != "") {
            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            kitchenOrders.emplace_back(menuItem, quantity);
        } else {
            std::cout << "Invalid menu item. Please choose from the menu." << std::endl;
        }
    }

    // Function to display customer information
    void displayCustomerInformation() {
        std::cout << "-------- Customer Information --------" << std::endl;
        for (const auto& customer : customers) {
            std::cout << "Name: " << customer.name << std::endl;
            std::cout << "Address: " << customer.address << std::endl;
            std::cout << "Phone: " << customer.phone << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }
    }

    // Function to display kitchen orders
    void displayKitchenOrders() {
        std::cout << "-------- Kitchen Orders --------" << std::endl;
        double totalOrderPrice = 0.0;

        for (const auto& order : kitchenOrders) {
            std::cout << "Item: " << order.menuItem.name << std::endl;
            std::cout << "Quantity: " << order.quantity << std::endl;
            double itemTotalPrice = order.quantity * order.menuItem.price;
            std::cout << "Total Price: $" << itemTotalPrice << std::endl;
            totalOrderPrice += itemTotalPrice;
            std::cout << "--------------------------------" << std::endl;
        }

        // Calculate and display tax
        double tax = calculateTax(totalOrderPrice);
        std::cout << "Subtotal: $" << totalOrderPrice << std::endl;
        std::cout << "Tax (" << (usTaxRate * 100) << "%): $" << tax << std::endl;
        std::cout << "Total Price (including tax): $" << (totalOrderPrice + tax) << std::endl;
    }

    // Function to calculate tax based on the US tax rate
    double calculateTax(double subtotal) {
        return subtotal * usTaxRate;
    }

    // Function to process payment
    void processPayment() {
        Payment payment;
        std::cout << "Enter payment amount: $";
        std::cin >> payment.amount;
        std::cin.ignore(); // Consume the newline character
        std::cout << "Enter payment method (Cash/Card): ";
        std::getline(std::cin, payment.paymentMethod);

        std::cout << "Payment processed successfully. Thank you!" << std::endl;
    }

    // Function to add a new menu item
    void addMenuItem() {
        std::string name;
        double price;

        std::cout << "Enter the name of the new menu item: ";
        std::getline(std::cin, name);
        std::cout << "Enter the price of the new menu item: $";
        std::cin >> price;

        menu.addMenuItem(name, price);
        std::cout << "New menu item added successfully." << std::endl;
    }

    // Function to set the tax rate
    void setTaxRate() {
        std::cout << "Enter the new tax rate: ";
        std::cin >> usTaxRate;
        std::cout << "Tax rate updated successfully." << std::endl;
    }
};

int main() {
    Restaurant restaurant;

    // Initialize the menu
    restaurant.addMenuItem(); // You can add more items as needed

    // Set the tax rate
    restaurant.setTaxRate(); // You can adjust the tax rate as needed

    // Take customer information
    restaurant.takeCustomerInformation();

    // Take customer order
    restaurant.takeCustomerOrder();

    // Display customer information
    restaurant.displayCustomerInformation();

    // Display kitchen orders
   restaurant.displayKitchenOrders();

    // Process payment
    restaurant.processPayment();

    return 0;
}
