///////////////////////////////////////////////////
//    This is automatically genearted file       //
//    by sasfit_convert.py                       //
//    Some editting might be required            //
///////////////////////////////////////////////////

double Iq( double q, double T, double SIGMA_T, double R, double SIGMA_R,
           double H, double SIGMA_H, double ETA_L, double ETA_SOL);
double Fq( double q,  double T, double SIGMA_T, double R, double SIGMA_R,
           double H, double SIGMA_H, double ETA_L, double ETA_SOL);
double form_volume(  double T, double SIGMA_T, double R, double SIGMA_R,
                     double H, double SIGMA_H, double ETA_L, double ETA_SOL);
double Iqxy( double qx, double qy, double T, double SIGMA_T, double R,
             double SIGMA_R, double H, double SIGMA_H, double ETA_L, double ETA_SOL);
/*
* Author(s) of this file:
*   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
*/
// define shortcuts for local parameters/variables
double Iq( double q, double T, double SIGMA_T, double R, double SIGMA_R,
           double H, double SIGMA_H, double ETA_L, double ETA_SOL)
{
    double Pcs, Pprime;
    sasfit_param subParam;
// insert your code here
    Pcs = sasfit_ff_pcs_homogeneousplate(q,param);
    sasfit_init_param( &subParam );
    subParam.p[0] = R;
    subParam.p[1] = H;
    subParam.p[2] = SIGMA_R;
    subParam.p[2] = SIGMA_H;
    Pprime = sasfit_sq_p__q___thin_hollow_cylinder(q,&subParam);
    return Pcs*Pprime;
}
double Fq( double q,  double T, double SIGMA_T, double R, double SIGMA_R,
           double H, double SIGMA_H, double ETA_L, double ETA_SOL)
{
// insert your code here
    return 0.0;
}
double form_volume(  double T, double SIGMA_T, double R, double SIGMA_R,
                     double H, double SIGMA_H, double ETA_L, double ETA_SOL)
{
// insert your code here
    return 0.0;
}
double Iqxy( double qx, double qy, double T, double SIGMA_T, double R,
             double SIGMA_R, double H, double SIGMA_H, double ETA_L, double ETA_SOL)
{
    double q = sqrt(qx*qx + qy*qy);
    return Iq( q, T, SIGMA_T, R, SIGMA_R, H, SIGMA_H, ETA_L, ETA_SOL);
}
