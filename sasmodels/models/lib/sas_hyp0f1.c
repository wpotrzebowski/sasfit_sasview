/*
Hypergeometric function related to Bessel functions
0F1[c,x] = Gamma[c] x^(1/2(1-c)) I_{c-1}(2 Sqrt[x])
Gamma[c] (-x)^(1/2(1-c)) J_{c-1}(2 Sqrt[-x])
*/

inline double sas_hyp0f1 (double v, double z) {
    double arg, v1, arg_exp, bess_val;

    if (v <= 0.0 && v == floor(v)) return 0.0;

    if (z == 0.0 && v != 0.0 ) return 1.0;

    //both v and z small: truncate the Taylor series at O(z**2)
    if (fabs(z) < 1e-6*(1.0 + fabs(v)))
        return 1.0 + z/v + z*z/(2.0*v*(v+1.0));

    if (z > 0) {
        arg = sqrt(z);
        //TODO: xlogy,lgam,iv have to be implemented/imported
        arg_exp = xlogy(1.0-v, arg) + lgam(v);
        bess_val = iv(v-1, 2.0*arg);

        if (arg_exp > log(DBL_MAX) || bess_val == 0 ||
            arg_exp < log(DBL_MIN) || isinf(bess_val)) {
            return hyp0f1_asy(v, z);
            }
        else {
            return exp(arg_exp) * gammasgn(v) * bess_val
        }
    }
    else {
        arg = sqrt(-z)
        return pow(arg, 1.0 - v) * sas_gamma(v) * sas_JN(v - 1, 2*arg)
    }

}

inline double _hyp0f1_asy(double v, double z){
    //Asymptotic expansion for I_{v-1}(2*sqrt(z)) * Gamma(v)
    //for real $z > 0$ and $v\to +\infty$.
    //Based off DLMF 10.41
    double arg = sqrt(z);
    double v1 = fabs(v - 1);
    double x = 2.0 * arg / v1;
    double p1 = sqrt(1.0 + x*x);
    double eta = p1 + log(x) - log1p(p1);
    double arg_exp_i, arg_exp_k;
    double pp, p2, p4, p6, u1, u2, u3, u_corr_i, u_corr_k;
    double result, gs;

    arg_exp_i = -0.5*log(p1);
    arg_exp_i -= 0.5*log(2.0*M_PI*v1);
    arg_exp_i += lgam(v);
    //TODO: gammasgn needs to be implemented
    gs = gammasgn(v)

    arg_exp_k = arg_exp_i;
    arg_exp_i += v1 * eta;
    arg_exp_k -= v1 * eta;

    //large-v asymptotic correction, DLMF 10.41.10
    pp = 1.0/p1;
    p2 = pp*pp;
    p4 = p2*p2;
    p6 = p4*p2;
    u1 = (3.0 - 5.0*p2) * pp / 24.0;
    u2 = (81.0 - 462.0*p2 + 385.0*p4) * p2 / 1152.0;
    u3 = (30375.0 - 369603.0*p2 + 765765.0*p4 - 425425.0*p6)
        * pp * p2 / 414720.0;
    u_corr_i = 1.0 + u1/v1 + u2/(v1*v1) + u3/(v1*v1*v1);

    result = exp(arg_exp_i - xlogy(v1, arg)) * gs * u_corr_i;
    if (v - 1 < 0) {
        //DLMF 10.27.2: I_{-v} = I_{v} + (2/pi) sin(pi*v) K_v
        u_corr_k = 1.0 - u1/v1 + u2/(v1*v1) - u3/(v1*v1*v1);
        //TODO: sin_pi needs to be implemented
        result += exp(arg_exp_k + xlogy(v1, arg)) * gs * 2.0
            * sin_pi(v1) * u_corr_k;
    }
    return result
}
