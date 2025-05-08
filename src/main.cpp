#include "../include/cash_register.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

void print_help() {
    std::cout << "Available commands:\n"
              << "  open <cashier_name> <initial_cash> - Open a new shift\n"
              << "  close - Close current shift\n"
              << "  new - Start a new receipt\n"
              << "  add <barcode/name> <quantity> - Add product to receipt\n"
              << "  pay cash <amount> - Pay with cash\n"
              << "  pay card - Pay with card\n"
              << "  print - Print current receipt\n"
              << "  help - Show this help\n"
              << "  exit - Exit the program\n";
}

int main() {
    CashRegister cash_register;
    cash_register.load_products("data/products.json");
    
    std::cout << "Cashier Workstation\n";
    print_help();
    
    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;
        
        try {
            if (cmd == "open") {
                std::string cashier_name;
                double initial_cash;
                if (!(iss >> cashier_name >> initial_cash)) {
                    std::cerr << "Usage: open <name> <initial_cash>\n";
                    continue;
                }
                cash_register.open_shift(cashier_name, initial_cash);
            }
            else if (cmd == "close") {
                cash_register.close_shift();
            }
            else if (cmd == "new") {
                cash_register.start_new_receipt();
                std::cout << "New receipt started\n";
            }
            else if (cmd == "add") {
                std::string search_term;
                int quantity;
                if (!(iss >> search_term >> quantity)) {
                    std::cerr << "Usage: add <barcode/name> <quantity>\n";
                    continue;
                }
                
                size_t slash_pos = search_term.find('/');
                if (slash_pos != std::string::npos) {
                    search_term = search_term.substr(0, slash_pos);
                }
                
                Product product = cash_register.find_product(search_term);
                cash_register.add_to_receipt(product, quantity);
                std::cout << "Added " << quantity << " x " << product.get_name() << "\n";
            }
            else if (cmd == "pay") {
                std::string method;
                iss >> method;
                if (method == "cash") {
                    double amount;
                    if (!(iss >> amount)) {
                        std::cerr << "Usage: pay cash <amount>\n";
                        continue;
                    }
                    cash_register.close_receipt(PaymentMethod::CASH, amount);
                }
                else if (method == "card") {
                    cash_register.close_receipt(PaymentMethod::CARD);
                }
                else {
                    std::cerr << "Invalid payment method. Use 'cash' or 'card'\n";
                }
            }
            else if (cmd == "print") {
                cash_register.print_current_receipt();
            }
            else if (cmd == "help") {
                print_help();
            }
            else if (cmd == "exit") {
                if (cash_register.is_shift_open()) {
                    std::cerr << "Please close the shift before exiting\n";
                    continue;
                }
                break;
            }
            else {
                std::cerr << "Unknown command. Type 'help' for available commands.\n";
            }
        } 
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    
    return 0;
}