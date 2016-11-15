# Cumulative Sample Variance in Rcpp

Small .cpp-file plus testfile that allows for a fast computation of the cumulative sample variance vector in R.
The implementation is based on Welford's algorithm (Reference: B. P. Welford (1962)."Note on a method for calculating corrected sums of squares and products". Technometrics 4(3):419–420.)

Example:
```
require(Rcpp)
sourceCpp("src/RcppCumVar.cpp")

testdata <- rnorm(10000)
RcppCumVar(testdata)
```