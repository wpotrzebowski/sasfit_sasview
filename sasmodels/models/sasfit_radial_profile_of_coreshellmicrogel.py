r"""
This file has been automatically gereated by sasfit_convert
The model calculates an empirical functional form for SAS data characterized
by radial_profile_of_coreshellmicrogel

Definition:
-----------

References:
-----------

"""
from numpy import inf

name = "radial_profile_of_coreshellmicrogel"
title = " "
description = ""
category = " "
#pylint: disable=bad-whitespace, line-too-long
parameters = [
 [ "W_CORE", 	"", 	10.0, 	[-inf, inf], 	"", 	""],
 [ "SIGMA_CORE", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
 [ "W_SH", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
 [ "SIGMA_SHIN", 	"", 	1.0, 	[-inf, inf], 	"", 	""],
 [ "D", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
 [ "SIGMA_OUT", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
 [ "ETA_CORE", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
 [ "ETA_SHELL", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
 [ "ETA_SOL", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
 [ "P0", 	"", 	0.0, 	[-inf, inf], 	"", 	""],
]
 #pylint: enable=bad-whitespace, line-too-long

source = [ "lib/sas_pow.c",  "sasfit_radial_profile_of_coreshellmicrogel.c" ]

demo = dict(
	W_CORE = 10.0,
	SIGMA_CORE = 0.0,
	W_SH = 0.0,
	SIGMA_SHIN = 1.0,
	D = 0.0,
	SIGMA_OUT = 0.0,
	ETA_CORE = 0.0,
	ETA_SHELL = 0.0,
	ETA_SOL = 0.0,
	P0 = 0.0)
