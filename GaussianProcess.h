#ifndef OSCILLARIUM_GAUSSIANPROCESS_H
#define OSCILLARIUM_GAUSSIANPROCESS_H

#include <Eigen/Core>
#include <vector>
#include <memory>
#include <cmath>

#include <celerite2/interface.hpp>
#include <celerite2/terms.hpp>

namespace Oscillarium {

class GaussianProcess {

    friend class MyModel;

private:
    struct TermBase {
        virtual ~TermBase() = default;
        virtual int width() const = 0;

        virtual celerite2::Term<double>::Matrices
        get_matrices(const Eigen::VectorXd& t,
                     const Eigen::VectorXd& diag) const = 0;

        virtual std::unique_ptr<TermBase> clone() const = 0;
    };

    template <typename TermType>
    struct TermWrapper : TermBase {
        TermType term;
        explicit TermWrapper(const TermType& t) : term(t) {}

        int width() const override { return term.get_width(); }

        celerite2::Term<double>::Matrices
        get_matrices(const Eigen::VectorXd& t,
                     const Eigen::VectorXd& diag) const override {
            return term.get_celerite_matrices(t, diag);
        }

        std::unique_ptr<TermBase> clone() const override {
            return std::make_unique<TermWrapper<TermType>>(term);
        }
    };



    std::vector<std::unique_ptr<TermBase>> terms_;
    int J_total_ = 0;

    Eigen::VectorXd t_;
    Eigen::VectorXd a_, d_, c_;
    Eigen::MatrixXd U_, V_, W_;

public:
    GaussianProcess() = default;
    GaussianProcess(const GaussianProcess& other);
    GaussianProcess& operator=(const GaussianProcess& other);

    template <typename TermType>
    void add_term(const TermType& term) {
        terms_.push_back(std::make_unique<TermWrapper<TermType>>(term));
        J_total_ += term.get_width();
    }

    void compute(const Eigen::VectorXd& t,
                 const Eigen::VectorXd& yerr);

    double log_likelihood(const Eigen::VectorXd& y) const;
};

} // namespace Oscillarium

#endif

