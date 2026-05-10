#ifndef UO_SOLUTION_SOLUTION_HPP
#define UO_SOLUTION_SOLUTION_HPP

#include <memory>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "solution/QualityOfSolution.hpp"
#include "problem/Problem.hpp"

namespace uo {

class ISolution {
public:
    virtual ~ISolution() = default;

    [[nodiscard]] virtual std::unique_ptr<ISolution> clone() const = 0;
    virtual void copy_from(const ISolution& other) = 0;
    virtual void init_random(const Problem& problem) = 0;
    virtual void init_from(const std::string& representation, const Problem& problem) = 0;
    [[nodiscard]] virtual std::string to_string() const = 0;

    [[nodiscard]] virtual QualityOfSolution calculate_quality_directly(const Problem& problem) = 0;
    virtual void evaluate(const Problem& problem) = 0;

    [[nodiscard]] virtual std::optional<double> fitness_value() const = 0;
    virtual void set_fitness_value(std::optional<double> value) = 0;
    [[nodiscard]] virtual std::optional<double> objective_value() const = 0;
    virtual void set_objective_value(std::optional<double> value) = 0;
    [[nodiscard]] virtual bool is_feasible() const = 0;
    virtual void set_is_feasible(bool value) = 0;

    [[nodiscard]] virtual std::optional<bool> is_better_than(
        const ISolution& other, const Problem& problem) const = 0;

    [[nodiscard]] virtual double representation_distance(const ISolution& other) const = 0;
    [[nodiscard]] virtual int random_seed() const = 0;
};

template <typename R>
class Solution : public ISolution {
public:
    explicit Solution(std::optional<int> random_seed = std::nullopt,
                      std::optional<double> fitness_value = std::nullopt,
                      std::optional<double> objective_value = std::nullopt,
                      bool is_feasible = false)
        : fitness_value_(fitness_value)
        , objective_value_(objective_value)
        , is_feasible_(is_feasible)
    {
        if (random_seed.has_value() && random_seed.value() != 0) {
            random_seed_ = random_seed.value();
        } else {
            random_seed_ = std::random_device{}();
        }
        rng_.seed(random_seed_);
    }

    ~Solution() override = default;

    // clone() must be implemented by derived class - not provided here

    void copy_from(const ISolution& other) override {
        auto* derived = dynamic_cast<const Solution<R>*>(&other);
        if (derived) {
            representation_ = derived->representation_;
            fitness_value_ = derived->fitness_value_;
            objective_value_ = derived->objective_value_;
            is_feasible_ = derived->is_feasible_;
            random_seed_ = derived->random_seed_;
        }
    }

    [[nodiscard]] const R& representation() const noexcept { return representation_; }
    void set_representation(const R& repr) { representation_ = repr; }
    void set_representation(R&& repr) { representation_ = std::move(repr); }

    [[nodiscard]] std::optional<double> fitness_value() const override { return fitness_value_; }
    void set_fitness_value(std::optional<double> value) override { fitness_value_ = value; }
    [[nodiscard]] std::optional<double> objective_value() const override { return objective_value_; }
    void set_objective_value(std::optional<double> value) override { objective_value_ = value; }
    [[nodiscard]] bool is_feasible() const override { return is_feasible_; }
    void set_is_feasible(bool value) override { is_feasible_ = value; }
    [[nodiscard]] int random_seed() const override { return random_seed_; }

    [[nodiscard]] std::optional<bool> is_better_than(
        const ISolution& other, const Problem& problem) const override {
        if (problem.is_multi_objective()) {
            throw std::runtime_error("Multi-objective comparison not supported");
        }
        auto fit1 = fitness_value();
        auto fit2 = other.fitness_value();
        if (!fit1.has_value() && !fit2.has_value()) return std::nullopt;
        if (!fit1.has_value()) return std::optional<bool>(false);
        if (!fit2.has_value()) return std::optional<bool>(true);
        if (fit1.value() > fit2.value()) return std::optional<bool>(true);
        if (fit1.value() == fit2.value()) return std::nullopt;
        return std::optional<bool>(false);
    }

    void evaluate(const Problem& problem) override {
        QualityOfSolution qos = calculate_quality_directly(problem);
        objective_value_ = qos.objective_value();
        fitness_value_ = qos.fitness_value();
        is_feasible_ = qos.is_feasible();
    }

    void init_from(const std::string& representation, const Problem& problem) override {
        (void)problem;
        representation_ = native_representation(representation);
    }

    // Pure virtuals - must be overridden by concrete types
    virtual void init_random(const Problem& problem) override = 0;
    [[nodiscard]] virtual QualityOfSolution calculate_quality_directly(const Problem& problem) override = 0;
    [[nodiscard]] virtual std::string to_string() const override = 0;
    [[nodiscard]] virtual R native_representation(const std::string& representation_str) const = 0;
    [[nodiscard]] virtual double representation_distance(const ISolution& other) const override = 0;

protected:
    R representation_;
    std::mt19937 rng_;

private:
    int random_seed_{0};
    std::optional<double> fitness_value_{std::nullopt};
    std::optional<double> objective_value_{std::nullopt};
    bool is_feasible_{false};
};

} // namespace uo

#endif // UO_SOLUTION_SOLUTION_HPP
