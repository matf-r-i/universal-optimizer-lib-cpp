#include <iostream>
#include <cassert>
#include <memory>
#include <sstream>

#include "algorithm/OutputControl.hpp"
#include "algorithm/metaheuristic/FinishControl.hpp"
#include "algorithm/metaheuristic/AdditionalStatisticsControl.hpp"

void test_output_control() {
    // Test OutputControl
    std::cout << "  Testing OutputControl..." << std::flush;
    {
        auto oc = std::make_shared<uo::OutputControl>();
        assert(oc->write_after_algorithm() == true);
        assert(oc->write_before_algorithm() == false);
        std::cout << " PASS" << std::endl;
    }
}

void test_finish_control() {
    // Test FinishControl
    std::cout << "  Testing FinishControl..." << std::flush;
    {
        uo::FinishControl fc("evaluations & seconds", 1000, 0, 60.0);
        assert(fc.check_evaluations() == true);
        assert(fc.check_iterations() == false);
        assert(fc.check_seconds() == true);
        assert(fc.is_finished(500, 10, 30.0) == false);
        assert(fc.is_finished(1500, 10, 30.0) == true);
        assert(fc.is_finished(500, 10, 90.0) == true);

        // Test default construction
        uo::FinishControl fc_default;
        assert(fc_default.check_evaluations() == false); // 0 max evaluations
        assert(fc_default.check_iterations() == false);  // 0 max iterations
        assert(fc_default.check_seconds() == false);     // 0.0 max seconds

        // Test clone
        uo::FinishControl fc_cloned = fc.clone();
        assert(fc_cloned.check_evaluations() == true);
        assert(fc_cloned.check_seconds() == true);

        std::cout << " PASS" << std::endl;
        std::cout << "    " << fc.to_string() << std::endl;
    }
}

void test_additional_statisitcs_control() {
    // Test AdditionalStatisticsControl
    std::cout << "  Testing AdditionalStatisticsControl..." << std::flush;
    {
        auto asc = std::make_shared<uo::AdditionalStatisticsControl>("all_solution_code, more_local_optima", 5);
        assert(asc->keep_all_solution_codes() == true);
        assert(asc->keep_more_local_optima() == true);

        asc->add_to_all_solution_codes("solution_1");
        asc->add_to_all_solution_codes("solution_2");
        asc->add_to_all_solution_codes("solution_1"); // duplicate
        assert(asc->all_solution_codes().size() == 2);

        asc->add_to_more_local_optima("optimum_a", 10.5, "optimum_a");
        asc->add_to_more_local_optima("optimum_b", 9.0, "optimum_a");
        assert(asc->keep_more_local_optima() == true);

        std::cout << " PASS" << std::endl;
        std::cout << "    " << asc->to_string() << std::endl;
    }
}

void test_output_control_with_moments() {
    // Test OutputControl with moments
    std::cout << "  Testing OutputControl moments..." << std::flush;
    {
        uo::OutputControl oc(nullptr, "iteration, evaluation, step_name", "before_algorithm, after_algorithm, after_iteration");
        assert(oc.write_before_algorithm() == true);
        assert(oc.write_after_algorithm() == true);
        assert(oc.write_after_iteration() == true);
        assert(oc.write_before_iteration() == false);
        assert(oc.write_before_evaluation() == false);
        assert(oc.write_after_evaluation() == false);
        std::cout << " PASS" << std::endl;
    }
}

int main() {
    std::cout << "=== Universal Optimizer C++ Tests ===" << std::endl;
 
    test_output_control();
    test_finish_control();
    test_additional_statisitcs_control();
    test_output_control_with_moments();
 
    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
