#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <boost/json.hpp>

class Product {
public:
    Product(const std::string& name, const std::string& barcode, double price);
    
    static Product from_json(const boost::json::value& json);
    boost::json::value to_json() const;

    std::string get_name() const;
    std::string get_barcode() const;
    double get_price() const;

private:
    std::string name;
    std::string barcode;
    double price;
};

#endif 