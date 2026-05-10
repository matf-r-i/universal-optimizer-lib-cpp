#include "algorithm/OutputControl.hpp"
#include <algorithm>
#include <sstream>

namespace uo {

OutputControl::OutputControl(std::shared_ptr<std::ostream> output_stream,
                             std::string fields,
                             std::string moments)
    : output_stream_(std::move(output_stream)) {
    parse_fields(fields);
    parse_moments(moments);
}

OutputControl OutputControl::clone() const {
    OutputControl oc(output_stream_, "", "");
    oc.field_headings_ = field_headings_;
    oc.field_definitions_ = field_definitions_;
    oc.write_before_algorithm_ = write_before_algorithm_;
    oc.write_after_algorithm_ = write_after_algorithm_;
    oc.write_before_iteration_ = write_before_iteration_;
    oc.write_after_iteration_ = write_after_iteration_;
    oc.write_before_evaluation_ = write_before_evaluation_;
    oc.write_after_evaluation_ = write_after_evaluation_;
    return oc;
}

void OutputControl::parse_fields(const std::string& fields) {
    field_headings_.clear();
    field_definitions_.clear();
    // Default fields are already set; this would parse custom ones.
    (void)fields;
}

void OutputControl::parse_moments(const std::string& moments) {
    write_before_algorithm_ = false;
    write_after_algorithm_ = true;  // default
    write_before_iteration_ = false;
    write_after_iteration_ = false;
    write_before_evaluation_ = false;
    write_after_evaluation_ = false;

    std::istringstream iss(moments);
    std::string token;
    while (std::getline(iss, token, ',')) {
        // Trim whitespace
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        if (token == "before_algorithm") write_before_algorithm_ = true;
        else if (token == "after_algorithm") write_after_algorithm_ = true;
        else if (token == "before_iteration") write_before_iteration_ = true;
        else if (token == "after_iteration") write_after_iteration_ = true;
        else if (token == "before_evaluation") write_before_evaluation_ = true;
        else if (token == "after_evaluation") write_after_evaluation_ = true;
    }
}

std::string OutputControl::to_string() const {
    std::ostringstream oss;
    oss << "OutputControl{output_stream=" << (output_stream_ ? "set" : "null")
        << ", field_headings=[";
    for (size_t i = 0; i < field_headings_.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << field_headings_[i];
    }
    oss << "]}";
    return oss.str();
}

} // namespace uo
