#ifndef CASHIER_SHIFT_H
#define CASHIER_SHIFT_H

#include <string>
#include <vector>
#include <memory>
#include "receipt.h"

class CashierShift {
public:
    CashierShift(const std::string& cashier_name, double initial_cash);
    
    void open_shift();
    void close_shift();
    bool is_shift_open() const;
    
    void add_receipt(const Receipt& receipt);
    void print_shift_report() const;
    
    const std::string& get_cashier_name() const;
    double get_initial_cash() const;
    double get_current_cash() const;

private:
    std::string cashier_name;
    double initial_cash;
    double current_cash;
    bool shift_open = false;
    std::vector<Receipt> receipts;
    
    double calculate_card_total() const;
    double calculate_cash_total() const;
};

#endif 