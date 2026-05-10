#include "algorithm/metaheuristic/Metaheuristic.hpp"
#include <random>
#include <sstream>

namespace uo {

Metaheuristic::Metaheuristic(
    FinishControl finish_control,
    std::unique_ptr<Problem> problem,
    std::unique_ptr<ISolution> solution_template,
    std::string name,
    std::shared_ptr<OutputControl> output_control,
    std::optional<int> random_seed,
    std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control)
    : Algorithm(std::move(problem), std::move(solution_template), std::move(name), std::move(output_control))
    , finish_control_(std::move(finish_control))
    , additional_statistics_control_(std::move(additional_statistics_control)) {
    if (random_seed.has_value() && random_seed.value() != 0) {
        random_seed_ = random_seed.value();
    } else {
        random_seed_ = std::random_device{}();
    }
    rng_.seed(random_seed_);
}

void Metaheuristic::main_loop() {
    while (!should_finish()) {
        main_loop_iteration();
    }
}

std::unique_ptr<ISolution> Metaheuristic::optimize() {
    init();
    main_loop();
    set_execution_ended(std::chrono::system_clock::now());
    return nullptr; // Placeholder - would return best_solution
}

bool Metaheuristic::should_finish() const {
    return finish_control_.is_finished(evaluation(), iteration(), elapsed_seconds());
}

std::string Metaheuristic::to_string() const {
    std::ostringstream oss;
    oss << "Metaheuristic{"
        << Algorithm::to_string()
        << ", random_seed=" << random_seed_
        << ", finish_control=" << finish_control_.to_string()
        << "}";
    return oss.str();
}

} // namespace uo
