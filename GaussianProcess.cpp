#include "GaussianProcess.h"
#include <stdexcept>

namespace Oscillarium {

GaussianProcess::GaussianProcess(const GaussianProcess& other)
    : J_total_(other.J_total_),
      t_(other.t_), a_(other.a_), d_(other.d_),
      c_(other.c_), U_(other.U_), V_(other.V_), W_(other.W_)
{
    terms_.reserve(other.terms_.size());
    for (const auto& ptr : other.terms_) {
        terms_.push_back(ptr->clone());
    }
}

GaussianProcess& GaussianProcess::operator=(const GaussianProcess& other)
{
    if (this != &other) {
        J_total_ = other.J_total_;
        t_ = other.t_;
        a_ = other.a_;
        d_ = other.d_;
        c_ = other.c_;
        U_ = other.U_;
        V_ = other.V_;
        W_ = other.W_;

        terms_.clear();
        terms_.reserve(other.terms_.size());
        for (const auto& ptr : other.terms_) {
            terms_.push_back(ptr->clone());
        }
    }
    return *this;
}


void GaussianProcess::compute(const Eigen::VectorXd& t,
                              const Eigen::VectorXd& yerr)
{
    t_ = t;
    const int N = t.size();

    a_.setZero(N);
    U_.setZero(N, J_total_);
    V_.setZero(N, J_total_);
    c_.setZero(J_total_);

    int col = 0;

    for (const auto& term_ptr : terms_) {
        const int J = term_ptr->width();

        auto [c_tmp, a_tmp, U_tmp, V_tmp] =
            term_ptr->get_matrices(t_, Eigen::VectorXd::Zero(N));

        a_ += a_tmp;

        U_.block(0, col, N, J) = U_tmp;
        V_.block(0, col, N, J) = V_tmp;
        c_.segment(col, J)     = c_tmp;

        col += J;
    }

    a_.array() += yerr.array().square();

    d_.resize(N);
    W_.resize(N, J_total_);

    const int info =
        celerite2::core::factor(t_, c_, a_, U_, V_, d_, W_);

    if (info != 0) {
        throw std::runtime_error(
            "celerite factorization failed at row " +
            std::to_string(info));
    }
}

double GaussianProcess::log_likelihood(const Eigen::VectorXd& y) const
{
    const int N = y.size();

    Eigen::VectorXd z(N), alpha(N);

    celerite2::core::solve_lower(t_, c_, U_, W_, y, z);
    celerite2::core::solve_upper(t_, c_, U_, W_, z, alpha);

    const double logdet = d_.array().log().sum();
    const double quad   = y.dot(alpha);

    return -0.5 * (quad + logdet + N * std::log(2.0 * M_PI));
}

} // namespace Oscillarium

