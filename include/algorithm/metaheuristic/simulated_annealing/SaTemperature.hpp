#ifndef UO_ALGORITHM_SA_TEMPERATURE_HPP
#define UO_ALGORITHM_SA_TEMPERATURE_HPP

#include <string>

namespace uo {

class SaTemperature {
public:
    virtual ~SaTemperature() = default;
    [[nodiscard]] virtual double calculate(int iteration) const = 0;
    [[nodiscard]] virtual std::string to_string() const = 0;
};

class SaTemperatureConst : public SaTemperature {
public:
    explicit SaTemperatureConst(double temperature) : temperature_(temperature) {}
    [[nodiscard]] double calculate(int /*iteration*/) const override { return temperature_; }
    [[nodiscard]] std::string to_string() const override;
private:
    double temperature_;
};

class SaTemperatureLinear : public SaTemperature {
public:
    SaTemperatureLinear(double initial, double final, int max_iterations);
    [[nodiscard]] double calculate(int iteration) const override;
    [[nodiscard]] std::string to_string() const override;
private:
    double initial_;
    double final_;
    int max_iterations_;
};

class SaTemperatureExponential : public SaTemperature {
public:
    SaTemperatureExponential(double initial, double cooling_rate);
    [[nodiscard]] double calculate(int iteration) const override;
    [[nodiscard]] std::string to_string() const override;
private:
    double initial_;
    double cooling_rate_;
};

} // namespace uo

#endif // UO_ALGORITHM_SA_TEMPERATURE_HPP
