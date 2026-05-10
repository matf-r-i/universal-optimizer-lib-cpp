#include "algorithm/metaheuristic/simulated_annealing/SaTemperature.hpp"
#include <sstream>
#include <cmath>

namespace uo {

std::string SaTemperatureConst::to_string() const {
    std::ostringstream oss;
    oss << "SaTemperatureConst{temperature=" << temperature_ << "}";
    return oss.str();
}

SaTemperatureLinear::SaTemperatureLinear(double initial, double final, int max_iterations)
    : initial_(initial), final_(final), max_iterations_(max_iterations) {}

double SaTemperatureLinear::calculate(int iteration) const {
    if (max_iterations_ <= 0) return initial_;
    double t = static_cast<double>(iteration) / max_iterations_;
    return initial_ - t * (initial_ - final_);
}

std::string SaTemperatureLinear::to_string() const {
    std::ostringstream oss;
    oss << "SaTemperatureLinear{initial=" << initial_
        << ", final=" << final_
        << ", max_iterations=" << max_iterations_ << "}";
    return oss.str();
}

SaTemperatureExponential::SaTemperatureExponential(double initial, double cooling_rate)
    : initial_(initial), cooling_rate_(cooling_rate) {}

double SaTemperatureExponential::calculate(int iteration) const {
    return initial_ * std::pow(cooling_rate_, iteration);
}

std::string SaTemperatureExponential::to_string() const {
    std::ostringstream oss;
    oss << "SaTemperatureExponential{initial=" << initial_
        << ", cooling_rate=" << cooling_rate_ << "}";
    return oss.str();
}

} // namespace uo
