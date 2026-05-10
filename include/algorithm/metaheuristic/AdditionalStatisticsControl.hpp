#ifndef UO_ALGORITHM_ADDITIONAL_STATISTICS_CONTROL_HPP
#define UO_ALGORITHM_ADDITIONAL_STATISTICS_CONTROL_HPP

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace uo {

/**
 * @brief Controls additional statistics tracking during metaheuristic execution.
 * 
 * This is the C++ equivalent of the Python `AdditionalStatisticsControl` class.
 * It supports tracking all solution codes and collecting multiple local optima.
 */
class AdditionalStatisticsControl {
public:
    /**
     * @brief Construct a new AdditionalStatisticsControl object.
     * @param keep Comma-separated items to keep: "all_solution_code", "more_local_optima".
     * @param max_local_optima_count Maximum number of local optima to store.
     */
    explicit AdditionalStatisticsControl(
        std::string keep = "",
        int max_local_optima_count = 10);

    /**
     * @brief Get the keep specification string.
     * @return const std::string& The keep specification.
     */
    [[nodiscard]] const std::string& keep() const noexcept { return keep_; }

    //@{
    /// @name Options
    /** @brief Whether to keep all solution codes. */
    [[nodiscard]] bool keep_all_solution_codes() const noexcept { return keep_all_solution_codes_; }

    /** @brief Whether to keep more local optima. */
    [[nodiscard]] bool keep_more_local_optima() const noexcept { return keep_more_local_optima_; }
    //@}

    //@{
    /// @name Local optima management
    /** @brief Get the maximum local optima count. */
    [[nodiscard]] int max_local_optima_count() const noexcept { return max_local_optima_count_; }

    /** @brief Add a solution to the local optima collection. */
    bool add_to_more_local_optima(const std::string& solution_rep,
                                  std::optional<double> fitness,
                                  const std::string& best_solution_rep);
    //@}

    //@{
    /// @name Solution codes
    /** @brief Add a solution code to the collection. */
    void add_to_all_solution_codes(const std::string& representation);

    /** @brief Get all collected solution codes. */
    [[nodiscard]] const std::unordered_set<std::string>& all_solution_codes() const noexcept {
        return all_solution_codes_;
    }
    //@}

    /** @brief String representation. */
    [[nodiscard]] std::string to_string() const;

private:
    void parse_keep(const std::string& keep);

    std::string keep_;
    int max_local_optima_count_;

    bool keep_all_solution_codes_{false};
    bool keep_more_local_optima_{false};

    std::unordered_set<std::string> all_solution_codes_;
    std::unordered_map<std::string, std::optional<double>> more_local_optima_;
};

} // namespace uo

#endif // UO_ALGORITHM_ADDITIONAL_STATISTICS_CONTROL_HPP
