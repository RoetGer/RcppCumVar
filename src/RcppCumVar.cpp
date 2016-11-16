#include <Rcpp.h>
using namespace Rcpp;
 
// C++ implementation of Welford's algorithm to compute the cumulative sample variance 
// Reference: B. P. Welford (1962)."Note on a method for calculating corrected sums of squares and products". Technometrics 4(3):419–420.
// [[Rcpp::export]]
NumericVector RcppCumVar(NumericVector x, bool isSampleVar) {
  int nelem = x.size();
  double avg = x[0];
  double M2 = 0.0;
  double n;
  double diff;
  
  NumericVector cumvar(nelem);
  
  if(isSampleVar) {
    cumvar[0] = NA_REAL;
    
    for(int i=1; i<nelem; i++) {
      n = i + 1.0;
      diff = x[i] - avg;
      avg += diff/n;
      M2 += diff*(x[i] - avg);
      cumvar[i] = M2/(n - 1.0);
    }
  } else {
    cumvar[0] = 0;
    
    for(int i=1; i<nelem; i++) {
      n = i + 1.0;
      diff = x[i] - avg;
      avg += diff/n;
      M2 += diff*(x[i] - avg);
      cumvar[i] = M2/n;
    }
  }
  
  return cumvar;
}
