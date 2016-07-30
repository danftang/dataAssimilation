#ifndef MODEL_H
#define MODEL_H

#include <eigen3/Eigen/Core>

class Model {
public:

	virtual Eigen::VectorXd state()=0;
	virtual void						setState(const Eigen::VectorXd &)=0;
	virtual Eigen::MatrixXd	jacobian()=0;
	virtual void 						step()=0;
	
};

#endif
