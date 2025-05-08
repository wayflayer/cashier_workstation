#ifndef CASH_REGISTER_H
#define CASH_REGISTER_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "product.h"
#include "cashier_shift.h"
#include "receipt.h"

class CashRegister {
public:
    CashRegister();
    
    void load_products(const std::string& filename);
    Product find_product(const std::string& search_term) const;
    
    void open_shift(const std::string& cashier_name, double initial_cash);
    void close_shift();
    bool is_shift_open() const;
    
    void start_new_receipt();
    void add_to_receipt(const Product& product, int quantity);
    void close_receipt(PaymentMethod method, double amount_paid = 0.0);
    void print_current_receipt() const;
    
private:
    std::unordered_map<std::string, Product> products;
    std::unique_ptr<CashierShift> current_shift;
    std::unique_ptr<Receipt> current_receipt;
};

#endif 