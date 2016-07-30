#ifndef AUTODIFFMODEL_H
#define AUTODIFFMODEL_H

template<int D>
class GaussianModel {
public:
	GaussianModel(IModel<D> &Model) : model(Model) {}
	
	void step(Gaussian<D> &);
	void observe(Observation &, ObservationOp &);
	
	IModel<D> &model;
};

tenplate<int D>
GaussianModel::step(Gaussian<D> &pdf) {
	IModel<D>::Jacobian J;
	model(pdf.M,J);
	J = J.inverse();
	pdf.S = J.transpose()*pdf.S*J;
}



#endif
