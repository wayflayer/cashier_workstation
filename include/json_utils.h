#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <boost/json.hpp>
#include <string>
#include <vector>

namespace json_utils {
    boost::json::value load_json_file(const std::string& filename);
    void save_json_file(const std::string& filename, const boost::json::value& data);
}

#endif 