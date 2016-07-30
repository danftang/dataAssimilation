#ifndef PROBABM_H
#define PROBABM_H


class ProbABM
{
	public:
		ProbABM();

		void agentStep();

		int			choose();

		int 		N; 				// total population
		double 	prob[3]; 	// prob of being in each state (full joint over agent states)
	protected:
	private:
};

#endif // PROBABM_H
