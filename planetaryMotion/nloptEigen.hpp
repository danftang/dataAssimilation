#ifndef NLOPTEIGEN_HPP_INCLUDED
#define NLOPTEIGEN_HPP_INCLUDED
#include <nlopt.h>
#include <functional>
#include <Eigen/Core>

class NloptEigen {
public:
    NloptEigen(nlopt_algorithm alg, unsigned n) {
      solver = nlopt_create(alg,n);
      dim= n;
    }

    void set_min_objective(std::function<double (Eigen::Map<const Eigen::VectorXd> &, Eigen::Map<Eigen::VectorXd> &)> eigenFunc) {
        eigenF = eigenFunc;
        nlopt_set_min_objective(solver, f, this);
    }

    nlopt_result set_ftol_rel(double tol) {
      return(nlopt_set_ftol_rel(solver,tol));
    }

    nlopt_result set_ftol_abs(double tol) {
      return(nlopt_set_ftol_abs(solver,tol));
    }

    nlopt_result optimize(Eigen::VectorXd &firstGuess) {
      Eigen::Map<const Eigen::VectorXd> x0(firstGuess.data(),firstGuess.size());
      Eigen::Map<Eigen::VectorXd> nullVec(NULL,0);
      double firstVal = eigenF(x0, nullVec);
      nlopt_result res = nlopt_optimize(solver, firstGuess.data(), &firstVal);
 //     std::cout << "Optimized: " << firstGuess.transpose() << std::endl;

      return(res);
    }

    static double f(unsigned n, const double* x, double* grad, void* f_data) {
        Eigen::Map<const Eigen::VectorXd> ex(x,n);
        if(grad != NULL) {
            Eigen::Map<Eigen::VectorXd> egrad(grad,n);
            return(((NloptEigen *)f_data)->eigenF(ex,egrad));
        }
        double dummy;
        Eigen::Map<Eigen::VectorXd> noGrad(&dummy,0);
        return(((NloptEigen *)f_data)->eigenF(ex,noGrad));
    }


protected:
    std::function<double (Eigen::Map<const Eigen::VectorXd> &, Eigen::Map<Eigen::VectorXd> &)> eigenF;
    unsigned int dim;
    nlopt_opt    solver;

};

#endif // NLOPTEIGEN_HPP_INCLUDED
