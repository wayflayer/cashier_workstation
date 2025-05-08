#ifndef RECEIPT_H
#define RECEIPT_H

#include <vector>
#include <string>
#include <memory>
#include "product.h"

enum class PaymentMethod { CASH, CARD };

class Receipt {
public:
    void add_product(const Product& product, int quantity);
    void close(PaymentMethod method, double amount_paid = 0.0);
    void print() const;
    
    double get_total() const;
    bool is_closed() const;

private:
    struct ReceiptItem {
        Product product;
        int quantity;
    };

    std::vector<ReceiptItem> items;
    PaymentMethod payment_method;
    double amount_paid;
    bool closed = false;
};

#endif 