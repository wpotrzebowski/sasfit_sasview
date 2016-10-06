r"""
Definition
----------
This model provides the form factor for a circular cylinder with a
core-shell scattering length density profile. Thus this is a variation
of a core-shell cylinder or disc where the shell on the walls and ends
may be of different thicknesses and scattering length densities. The form
factor is normalized by the particle volume.

.. _core-shell-bicelle-geometry:

.. figure:: img/core_shell_bicelle_geometry.png

    Schematic cross-section of bicelle. Note however that the model here
    calculates for rectangular, not curved, rims as shown below.

.. figure:: img/core_shell_bicelle_parameters.png

   Cross section of cylindrical symmetry model used here. Users will have 
   to decide how to distribute "heads" and "tails" between the rim, face 
   and core regions in order to estimate appropriate starting parameters.

The output of the 1D scattering intensity function for randomly oriented
cylinders is then given by the equation above.

The *theta* and *phi* parameters are not used for the 1D output.
Our implementation of the scattering kernel and the 1D scattering intensity
use the c-library from NIST.

.. figure:: img/cylinder_angle_definition.jpg

    Definition of the angles for the oriented core shell bicelle tmodel.

.. figure:: img/cylinder_angle_projection.jpg
    :width: 600px

    Examples of the angles for oriented pp against the detector plane.

References
----------

.. [#Matusmori] `N Matsumori and M Murata <http://dx.doi.org/10.1039/C0NP0000
   2G>`_, *Nat. Prod. Rep.* 27 (2010) 1480-1492
.. [#] L A Feigin and D I Svergun, *Structure Analysis by Small-Angle X-Ray and
   Neutron Scattering,* Plenum Press, New York, (1987)

Authorship and Verification
----------------------------

* **Author:** NIST IGOR/DANSE **Date:** pre 2010
* **Last Modified by:** Paul Butler **Date:** Septmber 30, 2016
* **Last Reviewed by:** Under Review **Date:** October 5, 2016

"""

from numpy import inf, sin, cos

name = "core_shell_bicelle"
title = "Circular cylinder with a core-shell scattering length density profile.."
description = """
    P(q,alpha)= (scale/Vs)*f(q)^(2) + bkg,  where: 
    f(q)= Vt(sld_rim - sld_solvent)* sin[qLt.cos(alpha)/2]
    /[qLt.cos(alpha)/2]*J1(qRout.sin(alpha))
    /[qRout.sin(alpha)]+
    (sld_core-sld_face)*Vc*sin[qLcos(alpha)/2][[qL
    *cos(alpha)/2]*J1(qRc.sin(alpha))
    /qRc.sin(alpha)]+
    (sld_face-sld_rim)*(Vc+Vf)*sin[q(L+2.thick_face).
    cos(alpha)/2][[q(L+2.thick_face)*cos(alpha)/2]*
    J1(qRc.sin(alpha))/qRc.sin(alpha)]

    alpha:is the angle between the axis of
    the cylinder and the q-vector
    Vt = pi.(Rc + thick_rim)^2.Lt : total volume
    Vc = pi.Rc^2.L :the volume of the core
    Vf = 2.pi.Rc^2.thick_face
    Rc = radius: is the core radius
    L: the length of the core
    Lt = L + 2.thick_face: total length
    Rout = radius + thick_rim
    sld_core, sld_rim, sld_face:scattering length
    densities within the particle
    sld_solvent: the scattering length density
    of the solvent
    bkg: the background
    J1: the first order Bessel function
    theta: axis_theta of the cylinder
    phi: the axis_phi of the cylinder...
        """
category = "shape:cylinder"

# pylint: disable=bad-whitespace, line-too-long
#             ["name", "units", default, [lower, upper], "type", "description"],
parameters = [
    ["radius",         "Ang",       20, [0, inf],    "volume",      "Cylinder core radius"],
    ["thick_rim",  "Ang",       10, [0, inf],    "volume",      "Rim shell thickness"],
    ["thick_face", "Ang",       10, [0, inf],    "volume",      "Cylinder face thickness"],
    ["length",         "Ang",      400, [0, inf],    "volume",      "Cylinder length"],
    ["sld_core",       "1e-6/Ang^2", 1, [-inf, inf], "sld",         "Cylinder core scattering length density"],
    ["sld_face",       "1e-6/Ang^2", 4, [-inf, inf], "sld",         "Cylinder face scattering length density"],
    ["sld_rim",        "1e-6/Ang^2", 4, [-inf, inf], "sld",         "Cylinder rim scattering length density"],
    ["sld_solvent",    "1e-6/Ang^2", 1, [-inf, inf], "sld",         "Solvent scattering length density"],
    ["theta",          "degrees",   90, [-inf, inf], "orientation", "In plane angle"],
    ["phi",            "degrees",    0, [-inf, inf], "orientation", "Out of plane angle"],
    ]

# pylint: enable=bad-whitespace, line-too-long

source = ["lib/Si.c", "lib/polevl.c", "lib/sas_J1.c", "lib/gauss76.c",
          "core_shell_bicelle.c"]

demo = dict(scale=1, background=0,
            radius=20.0,
            thick_rim=10.0,
            thick_face=10.0,
            length=400.0,
            sld_core=1.0,
            sld_face=4.0,
            sld_rim=4.0,
            sld_solvent=1.0,
            theta=90,
            phi=0)

qx, qy = 0.4 * cos(90), 0.5 * sin(0)
tests = [
    # Accuracy tests based on content in test/utest_other_models.py
    [{'radius': 20.0,
      'thick_rim': 10.0,
      'thick_face': 10.0,
      'length': 400.0,
      'sld_core': 1.0,
      'sld_face': 4.0,
      'sld_rim': 4.0,
      'sld_solvent': 1.0,
      'background': 0.0,
     }, 0.001, 353.550],

    [{'radius': 20.0,
      'thick_rim': 10.0,
      'thick_face': 10.0,
      'length': 400.0,
      'sld_core': 1.0,
      'sld_face': 4.0,
      'sld_rim': 4.0,
      'sld_solvent': 1.0,
      'theta': 90.0,
      'phi': 0.0,
      'background': 0.00,
     }, (qx, qy), 24.9167],

    # Additional tests with larger range of parameters
    [{'radius': 3.0,
      'thick_rim': 100.0,
      'thick_face': 100.0,
      'length': 1200.0,
      'sld_core': 5.0,
      'sld_face': 41.0,
      'sld_rim': 42.0,
      'sld_solvent': 21.0,
     }, 0.05, 1670.1828],
    ]
