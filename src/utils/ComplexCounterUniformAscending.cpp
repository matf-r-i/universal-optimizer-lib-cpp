#include "utils/ComplexCounterUniformAscending.hpp"
#include <sstream>

namespace uo {

ComplexCounterUniformAscending::ComplexCounterUniformAscending(int number_of_counters, int counter_size)
    : number_of_counters_(number_of_counters)
    , counter_size_(counter_size)
    , counters_(number_of_counters, 0) 
{
    if (number_of_counters <= 0) {
        throw std::invalid_argument("Parameter 'number_of_counters' must be greater than zero.");
    }
    if (counter_size <= 0) {
        throw std::invalid_argument("Parameter 'counter_size' must be greater than zero.");
    }
    if (counter_size < number_of_counters) {
        throw std::invalid_argument("Parameter 'counter_size' must be >= 'number_of_counters'.");
    }
}

bool ComplexCounterUniformAscending::reset() {
    for (int i = 0; i < number_of_counters_; ++i) {
        counters_[i] = i;
    }
    return number_of_counters_ * counter_size_ > 0;
}

bool ComplexCounterUniformAscending::progress() {
    // Check if we've reached the final state
    bool finish = true;
    for (int i = 0; i < number_of_counters_; ++i) {
        if (counters_[i] < counter_size_ - 1) {
            finish = false;
            break;
        }
    }
    if (finish) {
        return false;
    }
    // Find the rightmost counter that can be incremented
    int ind_not_max = number_of_counters_ - 1;
    for (int i = ind_not_max; i >= 0; --i) {
        if (counters_[i] < counter_size_ - 1) {
            ind_not_max = i;
            break;
        }
    }
    counters_[ind_not_max] += 1;
    // Reset all counters after the incremented one to 0
    for (int i = ind_not_max + 1; i < number_of_counters_; ++i) {
        counters_[i] = 0;
    }
    return true;
}

std::string ComplexCounterUniformAscending::to_string() const {
    std::ostringstream oss;
    oss << "ComplexCounterUniformAscending{number_of_counters=" << number_of_counters_
        << ", counter_size=" << counter_size_
        << ", current_state=[";
    for (size_t i = 0; i < counters_.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << counters_[i];
    }
    oss << "]}";
    return oss.str();
}

} // namespace uo
