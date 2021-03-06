#define PJ_LIB__

#include <math.h>

#include "proj.h"
#include "proj_internal.h"

PROJ_HEAD(tcc, "Transverse Central Cylindrical") "\n\tCyl, Sph, no inv";

#define EPS10 1.e-10


static PJ_XY tcc_s_forward (PJ_LP lp, PJ *P) {           /* Spheroidal, forward */
    PJ_XY xy = {0.0, 0.0};
    double b, bt;

    b = cos (lp.phi) * sin (lp.lam);
    if ((bt = 1. - b * b) < EPS10) {
        proj_errno_set(P, PJD_ERR_TOLERANCE_CONDITION);
        return xy;
    }
    xy.x = b / sqrt(bt);
    xy.y = atan2 (tan (lp.phi) , cos (lp.lam));
    return xy;
}


PJ *PROJECTION(tcc) {
    P->es  = 0.;
    P->fwd = tcc_s_forward;
    P->inv = nullptr;

    return P;
}
