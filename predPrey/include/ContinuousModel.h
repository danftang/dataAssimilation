#ifndef CONTINUOUSMODEL_H
#define CONTINUOUSMODEL_H


class ContinuousModel
{
    public:
        ContinuousModel();

        void step();

        double  population[3];  // log of current population
        double  a[3][3];        // a[i][j] = predation of j on i
        double  r[3];           // reproduction/death rate
        double  b[3];           // offset on log population n[i] = e^{population[i]/s[3]-b[i]}
        double  s[3];           // scale on log population
        double  dt;

    protected:
};

#endif // CONTINUOUSMODEL_H
