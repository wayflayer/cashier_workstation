#include "cash_register.h"
#include "json_utils.h"
#include <stdexcept>
#include <iostream>

CashRegister::CashRegister() {}

void CashRegister::load_products(const std::string& filename) {
    auto json = json_utils::load_json_file(filename);
    const auto& products_array = json.as_array();
    
    for (const auto& item : products_array) {
        Product product = Product::from_json(item);
        products.emplace(product.get_barcode(), product);
    }
}

Product CashRegister::find_product(const std::string& search_term) const {
    auto it = products.find(search_term);
    if (it != products.end()) {
        return it->second;
    }
    
    for (const auto& pair : products) {
        if (pair.second.get_name().find(search_term) != std::string::npos) {
            return pair.second;
        }
    }
    
    throw std::runtime_error("Product not found: " + search_term);
}

void CashRegister::open_shift(const std::string& cashier_name, double initial_cash) {
    if (is_shift_open()) {
        throw std::runtime_error("Shift is already open");
    }
    current_shift = std::make_unique<CashierShift>(cashier_name, initial_cash);
    current_shift->open_shift();
}

void CashRegister::close_shift() {
    if (!is_shift_open()) {
        throw std::runtime_error("No shift is open");
    }
    current_shift->close_shift();
    current_shift.reset();
}

bool CashRegister::is_shift_open() const {
    return current_shift != nullptr;
}

void CashRegister::start_new_receipt() {
    if (!is_shift_open()) {
        throw std::runtime_error("Cannot create receipt - no shift is open");
    }
    current_receipt = std::make_unique<Receipt>();
}

void CashRegister::add_to_receipt(const Product& product, int quantity) {
    if (!current_receipt) {
        throw std::runtime_error("No receipt started");
    }
    current_receipt->add_product(product, quantity);
}

void CashRegister::close_receipt(PaymentMethod method, double amount_paid) {
    if (!current_receipt) {
        throw std::runtime_error("No receipt to close");
    }
    
    current_receipt->close(method, amount_paid);
    current_receipt->print();
    current_shift->add_receipt(*current_receipt);
    current_receipt.reset();
}

void CashRegister::print_current_receipt() const {
    if (!current_receipt) {
        throw std::runtime_error("No receipt to print");
    }
    current_receipt->print();
}