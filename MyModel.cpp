#include "MyModel.h"
#include "DNest4/code/DNest4.h"
#include <celerite2/terms.hpp>

namespace Oscillarium
{

MyModel::MyModel()
{

}

void MyModel::from_prior(DNest4::RNG& rng)
{
    a = 100.0*rng.rand();
    f = 100.0*rng.rand();
    q = 0.5 + 99.5*rng.rand();
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

    return logH;
}

double MyModel::log_likelihood() const
{
    double logL = 0.0;



    return logL;
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
