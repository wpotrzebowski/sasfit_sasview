///////////////////////////////////////////////////
//    This is automatically genearted file       //
//    by sasfit_convert.py                       //
//    Some editting might be required            //
///////////////////////////////////////////////////

/*
* src/sasfit_ff/sasfit_ff_TeubnerStrey.c
*
* Copyright (c) 2008-2009, Paul Scherrer Institute (PSI)
*
* This file is part of SASfit.
*
* SASfit is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* SASfit is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with SASfit.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
* Author(s) of this file:
*   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
*   Ingo Bressler (ingo@cs.tu-berlin.de)
*/
double Iq( double q,
	double xi,
	double d,
	double eta)
{
double a, b, k, c;//, xi, d, eta;
k = 2.*M_PI/d;
a = k*k + 1./(xi*xi);
b = k*k - 1./(xi*xi);
c = a*a - 2.*b*q*q + q*q*q*q;
return eta*eta*8*M_PI/xi/c;
}
double Iqxy( double qx, double qy,
	double xi,
	double d,
	double eta)
{
	double q = sqrt(qx*qx + qy*qy);
	return Iq( q, xi, d, eta);
}
