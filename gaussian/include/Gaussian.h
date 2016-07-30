/*
 * Represents a multivariate Gaussian PDF
 */
#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include <Eigen/Core>

template<int D>
class Gaussian {
public:
	
	Gaussian<D> operator *(const Gaussian<D> &other);
	
	Eigen::Matrix<double, D, D>			S; // inverse of covariance matrix
	Eigen::Matrix<double, D, 1>			M; // mean of PDF
	
protected:
};

template<int D>
Gaussian<D> Gaussian<D>::operator *(const Gaussian<D> &other) {
	Gaussian<D> result;
	result.S = S + other.S;
	result.M = M + result.S.inverse() * other.S * (other.M - M);
}

#endif
