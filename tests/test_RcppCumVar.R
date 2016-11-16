require(Rcpp)
require(rbenchmark)

sourceCpp("src/RcppCumVar.cpp", verbose = T)

# R implementation of Welford's algorithm to compute the cumulative sample variance 
# Reference: B. P. Welford (1962)."Note on a method for calculating corrected sums of squares and products". Technometrics 4(3):419–420.
cum.variance <- function(x) {
  vars <- numeric(length(x))
  
  vars[1] <- NA
  
  n <- 1
  avg <- x[1]
  M2 <- 0.0
  
  for(i in 2:length(x)) {
    n <- n + 1
    diff <- x[i] - avg
    avg <- avg + diff/n
    M2 <- M2 + diff*(x[i] - avg)
    vars[i] <- M2/(n-1)
  }
  
  return(vars)
}

sample.size <- 100000
testdata <- rnorm(sample.size)

all.equal(cum.variance(testdata), RcppCumVar(testdata, isSampleVar = TRUE))

RcppCumVar(testdata, isSampleVar=FALSE)

benchmark(replications=10,
          RcppCumVar(testdata),
          cum.variance(testdata),
          columns=c('test', 'elapsed', 'replications'))