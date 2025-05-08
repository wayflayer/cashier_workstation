#include "receipt.h"
#include <iostream>
#include <iomanip>

void Receipt::add_product(const Product& product, int quantity) {
    if (closed) {
        throw std::runtime_error("Cannot add products to a closed receipt");
    }
    items.push_back({product, quantity});
}

void Receipt::close(PaymentMethod method, double amount_paid) {
    if (closed) {
        throw std::runtime_error("Receipt already closed");
    }
    
    double total = get_total();
    if (method == PaymentMethod::CASH && amount_paid < total) {
        throw std::runtime_error("Insufficient payment");
    }
    
    payment_method = method;
    this->amount_paid = amount_paid;
    closed = true;
}

double Receipt::get_total() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.product.get_price() * item.quantity;
    }
    return total;
}

bool Receipt::is_closed() const {
    return closed;
}

void Receipt::print() const {
    if (!closed) {
        throw std::runtime_error("Cannot print an open receipt");
    }

    std::cout << "=== RECEIPT ===\n";
    std::cout << std::left << std::setw(30) << "Name" 
              << std::setw(10) << "Price" 
              << std::setw(5) << "Qty" 
              << std::setw(10) << "Total" << "\n";

    for (const auto& item : items) {
        std::cout << std::left << std::setw(30) << item.product.get_name()
                  << std::setw(10) << item.product.get_price()
                  << std::setw(5) << item.quantity
                  << std::setw(10) << (item.product.get_price() * item.quantity) << "\n";
    }

    std::cout << "\nTOTAL: " << get_total() << "\n";
    std::cout << "Payment method: " << (payment_method == PaymentMethod::CASH ? "CASH" : "CARD") << "\n";
    
    if (payment_method == PaymentMethod::CASH) {
        std::cout << "Amount paid: " << amount_paid << "\n";
        std::cout << "Change: " << (amount_paid - get_total()) << "\n";
    }
    
    std::cout << "===============\n";
}