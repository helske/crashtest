// Functions for univariate SDE models

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::interfaces(r, cpp)]]

// x: state
// theta: vector of parameters

// Geometric Brownian motion case:
// theta(0) = mu
// theta(1) = sigma

// Drift function
// [[Rcpp::export]]
double drift(const double x, const arma::vec& theta) {
  return theta(0) * x;
}
// Volatility function
// [[Rcpp::export]]
double diffusion(const double x, const arma::vec& theta) {
  return std::max(0.0, theta(1) * x);
}
// Derivative of volatility
// [[Rcpp::export]]
double ddiffusion(const double x, const arma::vec& theta) {
  return theta(1) * (x > 0.0);
}

// log-density of the prior
double log_prior_pdf(const arma::vec& theta) {

  double log_pdf = 0.0;
  double infinite = -arma::datum::inf; //comment out this line and everything works??
  return log_pdf;
}

// Function which returns the pointers to above functions (no need to modify)

// [[Rcpp::export]]
Rcpp::List create_pntrs() {
  // typedef for a pointer of drift/volatility function
  typedef double (*funcPtr)(const double x, const arma::vec& theta);

  return Rcpp::List::create(
    Rcpp::Named("drift") = Rcpp::XPtr<funcPtr>(new funcPtr(&drift)),
    Rcpp::Named("diffusion") = Rcpp::XPtr<funcPtr>(new funcPtr(&diffusion)),
    Rcpp::Named("ddiffusion") = Rcpp::XPtr<funcPtr>(new funcPtr(&ddiffusion)));
}
