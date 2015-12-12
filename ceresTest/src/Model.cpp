#include "Model.h"

const int Model::N = 4;

Model::Model(const double *params) : T(18)
{
//    params = new double[N];
//    observations = new double[T];
    f = 60.0;
    calcPrices(params, observations, T);
    cost_function = new ceres::AutoDiffCostFunction<Model, 1, 4>(this);
}

Model::~Model()
{
//    delete [] params;
//    delete [] observations;
}

void Model::calcObservations(const double *params) {
    calcPrices(params, observations, T);
}

template <typename P> void Model::calcPrices(const P* const params, P *prices, const int T) const {
    prices[0] = P(1.0);
    prices[1] = P(2.0);
    prices[2] = P(2.2);
    for(int i=3; i<T; ++i) {
        prices[i] = (0.02*i)*params[0]*(params[3]*prices[i-3] + params[2]*prices[i-2] + params[1]*prices[i-1]) + (1.0-(0.02*i)*params[0])*f;
    }
}

// ----------------------
// calculate residual
// ----------------------
template <typename P> bool Model::operator()(const P* const params, P* residual) const {
    P modelPrices[T];
    calcPrices(params, modelPrices,T);
    residual[0] = P(0.0);
    for(int i=3; i<T; ++i) {
        residual[0] += (modelPrices[i]-observations[i])*(modelPrices[i]-observations[i]);
    }
    return true;
}

// ------------------
// to implement ceres::FirstOrderFunction
// -------------------
bool Model::Evaluate(const double* parameters, double* cost, double* gradient) const {
    const double ** params = &parameters;
    double ** grad = NULL;
    if(gradient != NULL) {
        grad = &gradient;
    }
    cost_function->Evaluate(params,cost,grad);
    return true;
}
