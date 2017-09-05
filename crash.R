library(crashtest)
simulate.data <- function(Tn=10, x0=1, sigma_x=1, sigma_y=1, mu=0, dt=1) {
  x <- x0
  y <- rep(NA,Tn)
  for (k in 1:Tn) {
    x <- x*exp((mu-0.5*sigma_x^2)*dt + sqrt(dt) * rnorm(1, sd=sigma_x))
    y[k] <- rnorm(1, mean=log(x), sd=sigma_y)
  }
  return(y)
}
set.seed(834)
n <- 50
y <- simulate.data(n, mu = 0.05, sigma_x = 0.2, sigma_y = 1)

for (i in 1:10) {
  print(paste0("iteration ", i))
  Rcpp::sourceCpp("sde_functions1.cpp", rebuild = TRUE)
  pntrs <- create_pntrs()
  # this seems to be crucial, altough looks to be irrelevant. Probably triggers gc at some point?
  print("create matrices")
  a <- matrix(1000^2, 1000, 1000)

  print("repeat millstein function 100,000 times")
  for (j in 1:100000)
    out <- milstein(1, 4, 1, c(0.05, 0.2, 1), pntrs$drift, pntrs$diffusion, pntrs$ddiffusion, TRUE, 1)

}

