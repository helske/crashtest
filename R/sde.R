#'
#' Millstein discretization of univaraite SDE
#'
#' @param drift,diffusion,ddiffusion An external pointers for the C++ functions which
#' define the drift, diffusion and derivative of diffusion functions of SDE.
#' @param theta Parameter vector passed to all model functions.
#' @param x0 Fixed initial value for SDE at time 0.
#' @param positive If \code{TRUE}, positive constraint is
#'   forced by \code{abs} in Millstein scheme.
#' @param seed seed for RNG.
#' @export
milstein <- function(x0, L, t, theta, drift_pntr, diffusion_pntr, ddiffusion_pntr, positive, seed) {
  .Call('_crashtest_R_milstein', PACKAGE = 'crashtest', x0, L, t, theta, drift_pntr, diffusion_pntr, ddiffusion_pntr, positive, seed)
}
