#include "problem/Problem.hpp"
#include <sstream>

namespace uo {

Problem::Problem(std::string name, bool is_minimization, bool is_multi_objective)
    : name_(std::move(name))
    , is_minimization_(is_minimization)
    , is_multi_objective_(is_multi_objective) {}

std::string Problem::to_string(const std::string& delimiter,
                                int indentation,
                                const std::string& indentation_symbol) const {
    std::ostringstream oss;
    for (int i = 0; i < indentation; ++i) oss << indentation_symbol;
    oss << "{" << delimiter;
    for (int i = 0; i < indentation; ++i) oss << indentation_symbol;
    oss << "name=" << name_ << delimiter;
    for (int i = 0; i < indentation; ++i) oss << indentation_symbol;
    oss << "is_minimization=" << (is_minimization_ ? "true" : "false") << delimiter;
    for (int i = 0; i < indentation; ++i) oss << indentation_symbol;
    oss << "is_multi_objective=" << (is_multi_objective_ ? "true" : "false") << delimiter;
    for (int i = 0; i < indentation; ++i) oss << indentation_symbol;
    oss << "}";
    return oss.str();
}

} // namespace uo
