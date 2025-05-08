#include "cashier_shift.h"
#include <iostream>

CashierShift::CashierShift(const std::string& cashier_name, double initial_cash)
    : cashier_name(cashier_name), initial_cash(initial_cash), current_cash(initial_cash) {}

void CashierShift::open_shift() {
    if (shift_open) {
        throw std::runtime_error("Shift is already open");
    }
    shift_open = true;
    std::cout << "Shift opened for cashier: " << cashier_name << "\n";
    std::cout << "Initial cash: " << initial_cash << "\n";
}

void CashierShift::close_shift() {
    if (!shift_open) {
        throw std::runtime_error("Shift is not open");
    }
    shift_open = false;
    print_shift_report();
}

bool CashierShift::is_shift_open() const {
    return shift_open;
}

void CashierShift::add_receipt(const Receipt& receipt) {
    if (!shift_open) {
        throw std::runtime_error("Cannot add receipt to closed shift");
    }
    receipts.push_back(receipt);
    current_cash += receipt.get_total();
}

void CashierShift::print_shift_report() const {
    std::cout << "=== SHIFT REPORT ===\n";
    std::cout << "Cashier: " << cashier_name << "\n";
    std::cout << "Initial cash: " << initial_cash << "\n";
    std::cout << "Total cash sales: " << calculate_cash_total() << "\n";
    std::cout << "Total card sales: " << calculate_card_total() << "\n";
    std::cout << "Current cash in drawer: " << current_cash << "\n";
    std::cout << "Number of receipts: " << receipts.size() << "\n";
    std::cout << "====================\n";
}

const std::string& CashierShift::get_cashier_name() const {
    return cashier_name;
}

double CashierShift::get_initial_cash() const {
    return initial_cash;
}

double CashierShift::get_current_cash() const {
    return current_cash;
}

double CashierShift::calculate_card_total() const {
    double total = 0.0;
    for (const auto& receipt : receipts) {
        total += receipt.get_total();
    }
    return total;
}

double CashierShift::calculate_cash_total() const {
    double total = 0.0;
    for (const auto& receipt : receipts) {
        total += receipt.get_total();
    }
    return total;
}