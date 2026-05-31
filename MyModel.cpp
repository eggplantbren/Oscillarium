#include "MyModel.h"
#include "DNest4/code/DNest4.h"
#include <celerite2/terms.hpp>

namespace Oscillarium
{

Data MyModel::data("data.txt");

MyModel::MyModel()
{
    // Do the GP stuff based on t and err
    Eigen::VectorXd t = Eigen::Map<Eigen::VectorXd>(data.t.data(),
                                                    data.t.size());
    Eigen::VectorXd err = Eigen::Map<Eigen::VectorXd>(data.err.data(),
                                                      data.err.size());

    gp.add_term(celerite2::SHOTerm(1.0, 1.0/(2.0*M_PI), 100.0));
}

void MyModel::from_prior(DNest4::RNG& rng)
{
    a = 100.0*rng.rand();
    f = 100.0*rng.rand();
    q = 0.5 + 99.5*rng.rand();
    compute_derived_parameters();
}

void MyModel::compute_derived_parameters()
{
    w0 = 2.0*M_PI*f;
    S0 = a*a/(w0*q);

    auto* base = gp.terms_[0].get();
    auto* wrapper = dynamic_cast<Oscillarium::GaussianProcess::TermWrapper<
        celerite2::SHOTerm<double>>*>(base);
    if(!wrapper)
        throw std::runtime_error("Wrong term type!");
    auto& term = wrapper->term;

    term = celerite2::SHOTerm<double>(S0, w0, q);
    Eigen::VectorXd t = Eigen::Map<Eigen::VectorXd>(data.t.data(),
                                                    data.t.size());
    Eigen::VectorXd err = Eigen::Map<Eigen::VectorXd>(data.err.data(),
                                                    data.err.size());
    gp.compute(t, err);
}

double MyModel::perturb(DNest4::RNG& rng)
{
    double logH = 0.0;

    int which = rng.rand_int(3);
    if(which == 0)
    {
        a += 100.0*rng.randh();
        DNest4::wrap(a, 0.0, 100.0);
    }
    else if(which == 1)
    {
        f += 100.0*rng.randh();
        DNest4::wrap(f, 0.0, 100.0);
    }
    else
    {
        q += 99.5*rng.randh();
        DNest4::wrap(q, 0.5, 100.0);
    }

    compute_derived_parameters();

    return logH;
}

double MyModel::log_likelihood() const
{
    double logL = 0.0;


    Eigen::VectorXd y = Eigen::Map<Eigen::VectorXd>(data.y.data(),
                                                    data.y.size());

    return gp.log_likelihood(y);
}

void MyModel::print(std::ostream& out) const
{
    out << a << ' ' << f << ' ' << q;
}

std::string MyModel::description() const
{
    return std::string("a f q");
}

} // namespace
