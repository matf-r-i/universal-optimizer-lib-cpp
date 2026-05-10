#include "algorithm/metaheuristic/AdditionalStatisticsControl.hpp"
#include <algorithm>
#include <random>
#include <sstream>

namespace uo {

AdditionalStatisticsControl::AdditionalStatisticsControl(std::string keep, int max_local_optima_count)
    : max_local_optima_count_(max_local_optima_count) {
    parse_keep(keep);
}

void AdditionalStatisticsControl::parse_keep(const std::string& keep) {
    keep_all_solution_codes_ = false;
    keep_more_local_optima_ = false;

    if (keep.empty() || keep == "none") return;

    std::istringstream iss(keep);
    std::string token;
    while (std::getline(iss, token, ',')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        if (token == "all_solution_code")
            keep_all_solution_codes_ = true;
        else if (token == "more_local_optima")
            keep_more_local_optima_ = true;
    }
}

void AdditionalStatisticsControl::add_to_all_solution_codes(const std::string& representation) {
    if (keep_all_solution_codes_ && !representation.empty()) {
        all_solution_codes_.insert(representation);
    }
}

bool AdditionalStatisticsControl::add_to_more_local_optima(
    const std::string& solution_rep,
    std::optional<double> fitness,
    const std::string& best_solution_rep) {
    if (!keep_more_local_optima_) return false;
    if (solution_rep.empty()) return false;
    if (more_local_optima_.count(solution_rep) > 0) return false;

    if (static_cast<int>(more_local_optima_.size()) >= max_local_optima_count_) {
        // Remove a random entry (not the best one)
        for (auto it = more_local_optima_.begin(); it != more_local_optima_.end(); ++it) {
            if (it->first != best_solution_rep) {
                more_local_optima_.erase(it);
                break;
            }
        }
    }
    more_local_optima_[solution_rep] = fitness;
    return true;
}

std::string AdditionalStatisticsControl::to_string() const {
    std::ostringstream oss;
    oss << "AdditionalStatisticsControl{keep=" << keep_
        << ", all_solution_codes_count=" << all_solution_codes_.size()
        << ", more_local_optima_count=" << more_local_optima_.size()
        << "}";
    return oss.str();
}

} // namespace uo
