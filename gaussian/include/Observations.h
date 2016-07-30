#ifndef OBSERVATIONS_H
#define OBSERVATIONS_H

#include <vector>
#include <array>

template<int D>
class Observations : public std::Vector<Array<double,D> > {
	Observations(int n) : Vector<Array<double,D> >(n) {}
};

#endif
