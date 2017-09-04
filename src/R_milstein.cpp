#include "milstein_functions.h"

// [[Rcpp::export]]
double R_milstein(const double x0, const unsigned int L, const double t,
  const arma::vec& theta,
  SEXP drift_pntr, SEXP diffusion_pntr, SEXP ddiffusion_pntr,
  bool positive, const unsigned int seed) {

  sitmo::prng_engine eng(seed);

  Rcpp::XPtr<funcPtr> xpfun_drift(drift_pntr);
  funcPtr drift = *xpfun_drift;

  Rcpp::XPtr<funcPtr> xpfun_diffusion(diffusion_pntr);
  funcPtr diffusion= *xpfun_diffusion;

  Rcpp::XPtr<funcPtr> xpfun_ddiffusion(ddiffusion_pntr);
  funcPtr ddiffusion = *xpfun_ddiffusion;

  return milstein(x0, L, t, theta,
    drift, diffusion, ddiffusion, positive, eng);
}
