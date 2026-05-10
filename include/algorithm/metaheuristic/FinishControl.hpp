#ifndef UO_ALGORITHM_FINISH_CONTROL_HPP
#define UO_ALGORITHM_FINISH_CONTROL_HPP

#include <string>
#include <sstream>

namespace uo {

class FinishControl {
public:
    explicit FinishControl(std::string criteria = "evaluations & seconds & iterations",
                           int evaluations_max = 0,
                           int iterations_max = 0,
                           double seconds_max = 0.0);

    [[nodiscard]] FinishControl clone() const;

    [[nodiscard]] int evaluations_max() const noexcept { return evaluations_max_; }
    [[nodiscard]] int iterations_max() const noexcept { return iterations_max_; }
    [[nodiscard]] double seconds_max() const noexcept { return seconds_max_; }

    [[nodiscard]] bool check_evaluations() const noexcept { return check_evaluations_; }
    [[nodiscard]] bool check_iterations() const noexcept { return check_iterations_; }
    [[nodiscard]] bool check_seconds() const noexcept { return check_seconds_; }

    [[nodiscard]] std::string criteria() const;

    [[nodiscard]] bool is_finished(int evaluation, int iteration, double elapsed_seconds) const noexcept;
    [[nodiscard]] std::string to_string() const;

private:
    void parse_criteria(const std::string& criteria_str);

    int evaluations_max_;
    int iterations_max_;
    double seconds_max_;
    std::string criteria_str_;

    bool check_evaluations_{false};
    bool check_iterations_{false};
    bool check_seconds_{false};
};

} // namespace uo

#endif // UO_ALGORITHM_FINISH_CONTROL_HPP
