#ifndef SYNCH_H
#define SYNCH_H

#include <functional>
#include <eigen3/Eigen/Core>
#include "lorenz.h"
#include "observationOperator.h"

class SynchronizedSystem {
public:
	SynchronizedSystem(Model &Driver, ObservationOperator &observationOp, Model &Driven) :
		H(observationOp), driver(Driver), driven(Driven)
		 {};
		
	void step();
	void step2Obs();
	double err(); // Euclidean distance to synchronization manifold

	ObservationOperator &H; // observation operator
	Model &driver;
	Model &driven;
};

#endif
