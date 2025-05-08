#include "product.h"

Product::Product(const std::string& name, const std::string& barcode, double price)
    : name(name), barcode(barcode), price(price) {}

Product Product::from_json(const boost::json::value& json) {
    const auto& obj = json.as_object();
    return Product(
        obj.at("name").as_string().c_str(),
        obj.at("barcode").as_string().c_str(),
        obj.at("price").as_double()
    );
}

boost::json::value Product::to_json() const {
    return {
        {"name", name},
        {"barcode", barcode},
        {"price", price}
    };
}

std::string Product::get_name() const { return name; }
std::string Product::get_barcode() const { return barcode; }
double Product::get_price() const { return price; }