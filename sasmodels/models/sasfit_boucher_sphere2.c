///////////////////////////////////////////////////
//    This is automatically genearted file       //
//    by sasfit_convert.py                       //
//    Some editting might be required            //
///////////////////////////////////////////////////

double Iq( double q, double R,  double ALPHA,  double DELTA_ETA,  double P0);
double Fq( double q,  double R,  double ALPHA,  double DELTA_ETA,  double P0);
double form_volume(  double R,  double ALPHA,  double DELTA_ETA,  double P0);
double Iqxy( double qx, double qy, double R, double ALPHA, double DELTA_ETA,
             double P0);
/*
* Author(s) of this file:
*   <your name> (<email address>)
*/
// define shortcuts for local R, ALPHA, DELTA_ETA, P0eters/variables
double Iq( double q, double R,  double ALPHA,  double DELTA_ETA,  double P0)
{
// insert your code here
    return sas_pow_2(Fq(q,R, ALPHA, DELTA_ETA, P0));
}
double Fq( double q,  double R,  double ALPHA,  double DELTA_ETA,  double P0)
{
    double beta;
// insert your code here
//   beta = DELTA_ETA*sas_pow_3(R)*sqrt(M_PI)*M_PI*exp(gsl_sf_lngamma(ALPHA/2.-1)-gsl_sf_lngamma(ALPHA/2.+0.5));
//   beta = DELTA_ETA*sas_pow_3(R*sqrt(M_PI))*sas_gamma(ALPHA/2.-1)/sas_gamma(ALPHA/2.+0.5);
    beta  = DELTA_ETA*sas_pow_3(R)*4./3.*M_PI;
    if (q*R == 0) return beta;
    return beta*gsl_sf_hyperg_0F1(0.5*(ALPHA+1),-sas_pow_2(q*R/2.));
}
double form_volume(  double R,  double ALPHA,  double DELTA_ETA,  double P0)
{
// insert your code here
    return 4./3. * M_PI*sas_pow_3(R);
}
double Iqxy( double qx, double qy, double R, double ALPHA, double DELTA_ETA,
             double P0)
{
    double q = sqrt(qx*qx + qy*qy);
    return Iq( q, R, ALPHA, DELTA_ETA, P0);
}
