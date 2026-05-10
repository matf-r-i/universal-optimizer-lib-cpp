#include "algorithm/metaheuristic/FinishControl.hpp"

namespace uo {

FinishControl::FinishControl(std::string criteria,
                             int evaluations_max,
                             int iterations_max,
                             double seconds_max)
    : evaluations_max_(evaluations_max)
    , iterations_max_(iterations_max)
    , seconds_max_(seconds_max)
    , criteria_str_(std::move(criteria)) {
    parse_criteria(criteria_str_);
}

FinishControl FinishControl::clone() const {
    return FinishControl(criteria_str_, evaluations_max_, iterations_max_, seconds_max_);
}

void FinishControl::parse_criteria(const std::string& criteria_str) {
    check_evaluations_ = false;
    check_iterations_ = false;
    check_seconds_ = false;

    std::istringstream iss(criteria_str);
    std::string token;
    while (std::getline(iss, token, '&')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        if (token == "evaluations" && evaluations_max_ > 0)
            check_evaluations_ = true;
        else if (token == "iterations" && iterations_max_ > 0)
            check_iterations_ = true;
        else if (token == "seconds" && seconds_max_ > 0.0)
            check_seconds_ = true;
    }
}

std::string FinishControl::criteria() const {
    std::string result;
    if (check_evaluations_) result += "evaluations & ";
    if (check_iterations_) result += "iterations & ";
    if (check_seconds_) result += "seconds & ";
    if (!result.empty()) result.erase(result.size() - 3); // remove " & "
    return result;
}

bool FinishControl::is_finished(int evaluation, int iteration, double elapsed_seconds) const noexcept {
    return (check_evaluations_ && evaluation >= evaluations_max_) ||
           (check_iterations_ && iteration >= iterations_max_) ||
           (check_seconds_ && elapsed_seconds >= seconds_max_);
}

std::string FinishControl::to_string() const {
    std::ostringstream oss;
    oss << "FinishControl{evaluations_max=" << evaluations_max_
        << ", iterations_max=" << iterations_max_
        << ", seconds_max=" << seconds_max_
        << ", criteria=" << criteria()
        << "}";
    return oss.str();
}

} // namespace uo
