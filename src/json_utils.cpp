#include "json_utils.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include <stdexcept>
#include <boost/json/src.hpp> 

namespace json_utils {
    boost::json::value load_json_file(const std::string& filename) {
        try {
            std::ifstream file(filename);
            if (!file) {
                throw std::runtime_error("Cannot open file: " + filename);
            }
            std::string content((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
            return boost::json::parse(content);
        } catch (const boost::json::system_error& e) {
            throw std::runtime_error("JSON error: " + std::string(e.what()));
        }
    }
}