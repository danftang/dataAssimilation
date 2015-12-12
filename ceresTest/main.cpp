#include <iostream>
#include "ceres/ceres.h"
#include "glog/logging.h"

#include "Model.h"

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

int main(int argc, char ** argv) {
    google::InitGoogleLogging(argv[0]);

//    const int T = 18;

    double params[4];
    params[0] = 0.5;
    params[1] = 0.5;
    params[2] = 0.3;
    params[3] = 0.2;

    ceres::GradientProblemSolver::Options options;
    options.minimizer_progress_to_stdout = true;
    ceres::GradientProblemSolver::Summary summary;
    ceres::GradientProblem problem(new Model(params));

    params[0] = 0.4;
    params[1] = 0.6;
    params[2] = 0.1;
    params[3] = 0.1;
    ceres::Solve(options, problem, params, &summary);

    std::cout << summary.FullReport() << "\n";
    std::cout << "Final   x: "
                << params[0] << ", "
                << params[1] << ", "
                << params[2] << ", "
                << params[3] << std::endl;
    return(0);
}
