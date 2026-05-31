#ifndef Oscillarium_MyModel_h
#define Oscillarium_MyModel_h

#include "DNest4/code/DNest4.h"
#include <ostream>
#include "GaussianProcess.h"
#include "Data.h"

namespace Oscillarium
{

class MyModel
{
    private:

        // Dataset
        static Data data;

        // Amplitude, period, quality
        double a, f, q;

        // Derived parameters
        double S0, w0;
        void compute_derived_parameters();

        GaussianProcess gp;

    public:
        // Constructor only gives size of params
        MyModel();

        // Generate the point from the prior
        void from_prior(DNest4::RNG& rng);

        // Metropolis-Hastings proposals
        double perturb(DNest4::RNG& rng);

        // Likelihood function
        double log_likelihood() const;

        // Print to stream
        void print(std::ostream& out) const;

        // Return string with column information
        std::string description() const;
};

} // namespace

#endif

