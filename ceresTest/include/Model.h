#ifndef MODEL_H
#define MODEL_H
#include "ceres/ceres.h"

class Model : public ceres::FirstOrderFunction
{
    public:
        Model(const double *params);
        virtual ~Model();

        void calcObservations(const double *params);
        template <typename P> void calcPrices(const P* const params, P *prices, const int T) const;
        template <typename P> bool operator()(const P* const x, P* residual) const;
        virtual bool Evaluate(const double* params, double* cost, double* gradient) const;
        virtual int NumParameters() const { return N; }

        double observations[18];
        static const int N;
        const int T;
        double f; // fundamental price
        ceres::CostFunction* cost_function;

    protected:
    private:
};

#endif // MODEL_H
