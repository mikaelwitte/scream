#ifndef SCREAM_SHOC_FUNCTIONS_F90_HPP
#define SCREAM_SHOC_FUNCTIONS_F90_HPP

#include "share/scream_types.hpp"
#include "physics/share/physics_test_data.hpp"

#include "shoc_functions.hpp"

#include <vector>
#include <array>
#include <utility>

//
// Bridge functions to call fortran version of shoc functions from C++
//

#define SHOC_DIM_RENAME1 PTD_DIM_RENAME(1, shcol)
#define SHOC_DIM_RENAME2 PTD_DIM_RENAME(2, shcol, nlev)
#define SHOC_DIM_RENAME3 PTD_DIM_RENAME(3, shcol, nlev, nlevi)

#define SHOC_NO_SCALAR(name, dim) \
  PTD_STD_DEF(name, dim, 0);                      \
  SHOC_DIM_RENAME##dim

#define SHOC_SCALARS(name, dim, num_scalars, ...)       \
  PTD_STD_DEF(name, dim, num_scalars, __VA_ARGS__);     \
  SHOC_DIM_RENAME##dim

namespace scream {
namespace shoc {

//Create data structure to hold data for shoc_grid
struct SHOCGridData : public PhysicsTestData {
  // Inputs
  Real *zt_grid, *zi_grid, *pdel;

  // In/out
  Real *dz_zt, *dz_zi, *rho_zt;

  SHOCGridData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&zt_grid, &dz_zt, &pdel, &rho_zt}, {&zi_grid, &dz_zi}) {}

  SHOC_NO_SCALAR(SHOCGridData, 3);
};

struct SHOCObklenData : public PhysicsTestData {
  // Inputs
  Real *uw_sfc, *vw_sfc, *wthl_sfc, *wqw_sfc, *thl_sfc;
  Real *cldliq_sfc, *qv_sfc;

  // Outputs
  Real *ustar, *kbfs, *obklen;

  SHOCObklenData(Int shcol_) :
  PhysicsTestData(shcol_, {&uw_sfc, &vw_sfc, &wthl_sfc, &wqw_sfc, &thl_sfc, &cldliq_sfc, &qv_sfc, &ustar, &kbfs, &obklen}){}

  SHOC_NO_SCALAR(SHOCObklenData, 1);

};

//Create data structure to hold data for compute_tmpi
struct SHOCComptmpiData : public PhysicsTestData {
  //Inputs
  Real dtime;
  Real *rho_zi, *dz_zi;

  //Outputs
  Real *tmpi;

  SHOCComptmpiData(Int shcol_, Int nlevi_, Real dtime_) :
    PhysicsTestData(shcol_, nlevi_, {&rho_zi, &dz_zi, &tmpi}), dtime(dtime_) {}

  PTD_STD_DEF(SHOCComptmpiData, 2, 1, dtime);
  PTD_DIM_RENAME(2, shcol, nlevi);

}; // SHOCComptmpiData

//Create data structure to hold data for dp_inverse
struct SHOCDpinverseData : public PhysicsTestData {
  //Inputs
  Real *rho_zt, *dz_zt;

  //Outputs
  Real *rdp_zt;

  SHOCDpinverseData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&rho_zt, &dz_zt, &rdp_zt}) {}

  SHOC_NO_SCALAR(SHOCDpinverseData, 2);

}; // SHOCDpinverseData

//Create data structure to hold data for sfc_fluxes
struct SHOCSfcfluxesData : public PhysicsTestData {
  //Inputs
  Real dtime;
  Real *rdp_zt_sfc, *rho_zi_sfc, *wthl_sfc, *wqw_sfc, *wtke_sfc, *wtracer_sfc;

  //In/Outputs
  Real *thetal, *qw, *tke, *tracer;

  SHOCSfcfluxesData(Int shcol_, Int num_tracer_, Real dtime_) :
    PhysicsTestData(shcol_, num_tracer_, {&wtracer_sfc, &tracer}, {&rdp_zt_sfc, &rho_zi_sfc, &wthl_sfc, &wqw_sfc, &wtke_sfc, &thetal, &qw, &tke}), dtime(dtime_) {}

    PTD_STD_DEF(SHOCSfcfluxesData, 2, 1, dtime);
    PTD_DIM_RENAME(2, shcol, num_tracer)

}; // SHOCSfcfluxesData

//Create data structure to hold data for impli_srf_stress_term
struct SHOCImplsrfstressData : public PhysicsTestData {
  //Inputs
  Real *rho_zi_sfc, *uw_sfc, *vw_sfc, *u_wind_sfc, *v_wind_sfc;

  //Outputs
  Real *ksrf;

  SHOCImplsrfstressData(Int shcol_) :
    PhysicsTestData(shcol_, {&rho_zi_sfc, &uw_sfc, &vw_sfc, &u_wind_sfc, &v_wind_sfc, &ksrf}) {}

  SHOC_NO_SCALAR(SHOCImplsrfstressData, 1);

}; // SHOCImplsrfstressData

//Create data structure to hold data for tke_srf_flux_term
struct SHOCTkesrffluxData : public PhysicsTestData {
  //Inputs
  Real *uw_sfc, *vw_sfc;

  //Outputs
  Real *wtke_sfc;

  SHOCTkesrffluxData(Int shcol_) :
    PhysicsTestData(shcol_, {&uw_sfc, &vw_sfc, &wtke_sfc}) {}

  SHOC_NO_SCALAR(SHOCTkesrffluxData, 1);

}; // SHOCTkesrffluxData

//Create data structure to hold data for check_tke
struct SHOCCheckTkeData : public PhysicsTestData {

  // Output
  Real *tke;

  SHOCCheckTkeData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&tke}) {}

  SHOC_NO_SCALAR(SHOCCheckTkeData, 2);
};//SHOCCheckTkeData

//Create data structure to hold data for shoc_tke
struct SHOCTkeData : public PhysicsTestData {
  // Inputs
  Real dtime;
  Real *wthv_sec, *shoc_mix, *dz_zi, *u_wind, *v_wind, *pblh;
  Real *brunt, *obklen, *zt_grid, *zi_grid, *dz_zt, *pres;

  // Output
  Real *tke, *tkh, *tk, *isotropy;

  SHOCTkeData(Int shcol_, Int nlev_, Int nlevi_, Real dtime_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&wthv_sec, &shoc_mix, &dz_zt, &pres, &u_wind, &v_wind, &zt_grid, &brunt, &tke, &tk, &tkh, &isotropy}, {&dz_zi, &zi_grid}, {&obklen, &pblh}), dtime(dtime_) {}

  SHOC_SCALARS(SHOCTkeData, 3, 1, dtime);
};//SHOCTkeData

//Create data structure to hold data for integ_column_stability
struct SHOCColstabData : public PhysicsTestData {
  // Inputs
  Real *dz_zt, *pres, *brunt;

  // Output
  Real *brunt_int;

  SHOCColstabData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&dz_zt, &pres, &brunt}, {&brunt_int}) {}

  SHOC_NO_SCALAR(SHOCColstabData, 2);
};//SHOCColstabData

//Create data structure to hold data for compute_shr_prod
struct SHOCTkeshearData : public PhysicsTestData {
  // Inputs
  Real *dz_zi, *u_wind, *v_wind;

  // In/out
  Real *sterm;

  //functions to initialize data
  SHOCTkeshearData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&u_wind, &v_wind}, {&dz_zi, &sterm}) {}

  SHOC_NO_SCALAR(SHOCTkeshearData, 3);
};//SHOCTkeshearData

//Create data structure to hold data for isotropic_ts
struct SHOCIsotropicData : public PhysicsTestData {
  // Inputs
  Real *tke, *a_diss, *brunt, *brunt_int;

  // Output
  Real *isotropy;

  //functions to initialize data
  SHOCIsotropicData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&tke, &a_diss, &brunt, &isotropy}, {&brunt_int}) {}

  SHOC_NO_SCALAR(SHOCIsotropicData, 2);
};//SHOCIsotropicData

//Create data structure to hold data for adv_sgs_tke
struct SHOCAdvsgstkeData : public PhysicsTestData {
  // Inputs
  Real dtime;
  Real *shoc_mix, *wthv_sec, *sterm_zt, *tk;

  // In/out
  Real *tke;

  // Outputs
  Real *a_diss;

  //functions to initialize data
  SHOCAdvsgstkeData(Int shcol_, Int nlev_, Real dtime_) :
    PhysicsTestData(shcol_, nlev_, {&shoc_mix, &wthv_sec, &sterm_zt, &tk, &tke, &a_diss}), dtime(dtime_) {}

  SHOC_SCALARS(SHOCAdvsgstkeData, 2, 1, dtime);
};//SHOCAdvsgstkeData

//Create data structure to hold data for eddy_diffusivities
struct SHOCEddydiffData : public PhysicsTestData {
  // Inputs
  Real *pblh, *obklen, *zt_grid, *shoc_mix, *sterm_zt,
        *isotropy, *tke;

  // Output
  Real *tk, *tkh;

  //functions to initialize data
  SHOCEddydiffData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&zt_grid, &shoc_mix, &isotropy, &tke, &tk, &tkh, &sterm_zt}, {&obklen, &pblh}) {}

  SHOC_NO_SCALAR(SHOCEddydiffData, 2);
};//SHOCEddydiffData


//create data structure for update_host_dse
struct SHOCEnergydseData : public PhysicsTestData {
  // Inputs
  Real *thlm, *shoc_ql, *exner, *zt_grid, *phis;

  // Output
  Real *host_dse;

  //functions to initialize data
  SHOCEnergydseData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&thlm, &shoc_ql, &exner, &zt_grid, &host_dse}, {&phis}) {}

  SHOC_NO_SCALAR(SHOCEnergydseData, 2);
};//SHOCEnergydseData

//create data structure for shoc_energy_fixer
struct SHOCEnergyfixerData : public PhysicsTestData {
  // Inputs
  Int nadv;
  Real dtime;
  Real *zt_grid, *zi_grid, *se_b, *wv_b, *pint;
  Real *se_a, *ke_b, *wl_b, *ke_a, *tke;
  Real *wv_a, *wl_a, *wthl_sfc, *wqw_sfc, *rho_zt;

  // Output
  Real *host_dse;

  //functions to initialize data
  SHOCEnergyfixerData(Int shcol_, Int nlev_, Int nlevi_, Real dtime_, Real nadv_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&host_dse, &zt_grid, &rho_zt, &tke}, {&zi_grid, &pint}, {&se_b, &ke_b, &wv_b, &wl_b, &se_a, &ke_a, &wv_a, &wl_a, &wthl_sfc, &wqw_sfc}), nadv(nadv_), dtime(dtime_) {}

  SHOC_SCALARS(SHOCEnergyfixerData, 3, 2, dtime, nadv);
};//SHOCEnergyfixerData

//create data structure for shoc_energy_integrals
struct SHOCEnergyintData : public PhysicsTestData {
  // Inputs
  Real *host_dse, *pdel, *rtm, *rcm, *u_wind, *v_wind;

  // Output
  Real *se_int, *ke_int, *wv_int, *wl_int;

  //functions to initialize data
  SHOCEnergyintData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&host_dse, &pdel, &rtm, &rcm, &u_wind, &v_wind}, {&se_int, &ke_int, &wv_int, &wl_int}) {}

  SHOC_NO_SCALAR(SHOCEnergyintData, 2);
};//SHOCEnergyintData

//Create data structure for shoc_energy_total_fixer
struct SHOCEnergytotData : public PhysicsTestData {
  // Inputs
  Int nadv;
  Real dtime;
  Real *zt_grid, *zi_grid, *se_b, *ke_b, *wv_b, *wl_b, *se_a;
  Real *ke_a, *wv_a, *wl_a, *wthl_sfc, *wqw_sfc, *rho_zt;

  // Output
  Real *te_a, *te_b;

  //functions to initialize data for shoc_energy_total_fixer
  SHOCEnergytotData(Int shcol_, Int nlev_, Int nlevi_, Real dtime_, Int nadv_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&zt_grid, &rho_zt}, {&zi_grid}, {&se_b, &ke_b, &wv_b, &wl_b, &se_a, &ke_a, &wv_a, &wl_a, &wthl_sfc, &wqw_sfc, &te_a, &te_b}), nadv(nadv_), dtime(dtime_) {}

  SHOC_SCALARS(SHOCEnergytotData, 3, 2, dtime, nadv);
};//SHOCEnergytotData

//create data structure for shoc_energy_threshold_fixer
struct SHOCEnergythreshfixerData : public PhysicsTestData {
  // Inputs
  Real *pint, *tke, *te_a, *te_b;

  // In/out
  Real *se_dis;
  Int *shoctop;

  //functions to initialize data
  SHOCEnergythreshfixerData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&tke}, {&pint}, {&se_dis, &te_a, &te_b}, {&shoctop}) {}

  SHOC_NO_SCALAR(SHOCEnergythreshfixerData, 3);
};//SHOCEnergythreshfixerData

//create data structure for shoc_energy_dse_fixer
struct SHOCEnergydsefixerData : public PhysicsTestData {
  // Inputs
  Real *se_dis;
  Int *shoctop;

  // In/out
  Real *host_dse;

  //functions to initialize data
  SHOCEnergydsefixerData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&host_dse}, {&se_dis}, {&shoctop}) {}

  SHOC_NO_SCALAR(SHOCEnergydsefixerData, 2);
};//SHOCEnergydsefixerData

//Create data structure to hold data for calc_shoc_vertflux
struct SHOCVertfluxData : public PhysicsTestData {
  // Inputs
  Real *tkh_zi, *dz_zi, *invar;

  // In/out
  Real *vertflux;

  SHOCVertfluxData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&invar}, {&tkh_zi, &dz_zi, &vertflux}) {}

  SHOC_NO_SCALAR(SHOCVertfluxData, 3);
}; //SHOCVertfluxData

//Create data structure to hold data for calc_shoc_varorcovar
struct SHOCVarorcovarData : public PhysicsTestData {
  // Inputs
  Real tunefac;
  Real *tkh_zi, *dz_zi, *isotropy_zi, *invar1, *invar2;

  // In/out
  Real *varorcovar;

  SHOCVarorcovarData(Int shcol_, Int nlev_, Int nlevi_, Real tunefac_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&invar1, &invar2}, {&tkh_zi, &dz_zi, &isotropy_zi, &varorcovar}), tunefac(tunefac_) {}

  SHOC_SCALARS(SHOCVarorcovarData, 3, 1, tunefac);
};//SHOCVarorcovarData

//Create data structure to hold data for shoc_length
struct SHOCLengthData : public PhysicsTestData {
  // Inputs
  Real *tke, *host_dx, *host_dy, *pblh, *zt_grid, *zi_grid;
  Real *dz_zt, *dz_zi, *wthv_sec, *thetal, *thv;

  // Outputs
  Real *brunt, *shoc_mix;

  SHOCLengthData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&tke, &zt_grid, &dz_zt, &wthv_sec, &thetal, &thv, &brunt, &shoc_mix}, {&zi_grid, &dz_zi}, {&host_dx, &host_dy, &pblh}) {}

  SHOC_NO_SCALAR(SHOCLengthData, 3);
};//SHOCLengthData

//Create data structure to hold data for compute_brunt_shoc_length
struct SHOCBruntlengthData : public PhysicsTestData {
  // Inputs
  Real *dz_zt, *thv, *thv_zi;

  // In/out
  Real *brunt;

  SHOCBruntlengthData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&dz_zt, &thv, &brunt}, {&thv_zi}) {}

  SHOC_NO_SCALAR(SHOCBruntlengthData, 3);
};//SHOCBruntlengthData

//Create data structure to hold data for compute_l_inf_shoc_length
struct SHOCInflengthData : public PhysicsTestData {
  // Inputs
  Real *zt_grid, *dz_zt, *tke;

  // In/out
  Real *l_inf;

  SHOCInflengthData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&zt_grid, &dz_zt, &tke}, {&l_inf}) {}

  SHOC_NO_SCALAR(SHOCInflengthData, 2);
};//SHOCInflengthData

//Create data structure to hold data for compute_vel_shoc_length
struct SHOCConvvelData : public PhysicsTestData {
  // Inputs
  Real *pblh, *zt_grid, *dz_zt, *thv, *wthv_sec;

  // In/out
  Real *conv_vel;

  SHOCConvvelData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&zt_grid, &dz_zt, &thv, &wthv_sec}, {&conv_vel, &pblh}) {}

  SHOC_NO_SCALAR(SHOCConvvelData, 2);
};//SHOCConvvelData

//Create data structure to hold data for compute_conv_time_shoc_length
struct SHOCConvtimeData : public PhysicsTestData {
  // Inputs
  Real *pblh, *conv_vel;

  // In/out
  Real *tscale;

  SHOCConvtimeData(Int shcol_) :
    PhysicsTestData(shcol_, {&conv_vel, &pblh, &tscale}) {}

  SHOC_NO_SCALAR(SHOCConvtimeData, 1);
};//SHOCConvtimeData

//Create data structure to hold data for compute_shoc_mix_shoc_length
struct SHOCMixlengthData : public PhysicsTestData {
  // Inputs
  Real *tke, *brunt, *tscale, *zt_grid, *l_inf;

  // In/out
  Real *shoc_mix;

  SHOCMixlengthData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&tke, &brunt, &zt_grid, &shoc_mix}, {&l_inf, &tscale}) {}

  SHOC_NO_SCALAR(SHOCMixlengthData, 2);
};//SHOCMixlengthData

//Create data structure to hold data for check_length_scale_shoc_length
struct SHOCMixcheckData : public PhysicsTestData {
  // Inputs
  Real *host_dx, *host_dy;

  // In/out
  Real *shoc_mix;

  SHOCMixcheckData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&shoc_mix}, {&host_dx, &host_dy}) {}

  SHOC_NO_SCALAR(SHOCMixcheckData, 2);
};//SHOCMixcheckData

//Create data structure to hold data for clipping_diag_third_shoc_moments
struct SHOCClipthirdmomsData : public PhysicsTestData {
  // Inputs
  Real *w_sec_zi;

  // In/out
  Real *w3;

  SHOCClipthirdmomsData(Int shcol_, Int nlevi_) :
    PhysicsTestData(shcol_, nlevi_,{&w_sec_zi, &w3}){}

  PTD_STD_DEF(SHOCClipthirdmomsData, 2, 0);
  PTD_DIM_RENAME(2, shcol, nlevi);

};//SHOCClipthirdmomsData

struct SHOCAAdiagthirdmomsData
{
  // inputs
  Real omega0, omega1, omega2, x0, x1, y0, y1;

  // outputs
  Real aa0, aa1;

};

struct SHOCFtermdiagthirdmomsData
{
  // inputs
  Real thedz, thedz2, bet2, iso, isosqrd, wthl_sec, wthl_sec_kc;
  Real wthl_sec_kb, thl_sec, thl_sec_kc, thl_sec_kb, w_sec;
  Real w_sec_kc, w_sec_zi, tke, tke_kc;

  // outputs
  Real f0, f1, f2, f3, f4, f5;

};

struct SHOCOmegadiagthirdmomsData
{
  // inputs
  Real buoy_sgs2, f3, f4;

  // outputs
  Real omega0, omega1, omega2;

};

struct SHOCXYdiagthirdmomsData
{
  // inputs
  Real buoy_sgs2, f0, f1, f2;

  // outputs
  Real x0, y0, x1, y1;

};

struct SHOCW3diagthirdmomsData
{
  // inputs
  Real aa0, aa1, x0, x1, f5;

  // outputs
  Real w3;

};

struct SHOCFterminputthirdmomsData
{
  // inputs
  Real dz_zi, dz_zt, dz_zt_kc, isotropy_zi, brunt_zi, thetal_zi;

  // outputs
  Real thedz, thedz2, iso, isosqrd, buoy_sgs2, bet2;

};

struct SHOCSecondMomentSrfData : public PhysicsTestData {
  // Inputs
  Real *wthl_sfc, *uw_sfc, *vw_sfc;

  // out
  Real *ustar2, *wstar;

  SHOCSecondMomentSrfData(Int shcol_) :
    PhysicsTestData(shcol_, {&wthl_sfc, &uw_sfc, &vw_sfc, &ustar2, &wstar}) {}

  SHOC_NO_SCALAR(SHOCSecondMomentSrfData, 1);
};

//Create data structure to hold data for diag_third_shoc_moments
struct SHOCDiagThirdMomData : public PhysicsTestData {
  // Inputs
  Real *w_sec, *thl_sec, *wthl_sec, *tke;
  Real *dz_zt, *dz_zi, *zt_grid, *zi_grid, *isotropy, *brunt;
  Real *thetal;

  // Output
  Real *w3;

  SHOCDiagThirdMomData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&w_sec, &tke, &dz_zt, &zt_grid, &brunt, &thetal, &isotropy}, {&thl_sec, &wthl_sec, &zi_grid, &dz_zi, &w3}) {}

  SHOC_NO_SCALAR(SHOCDiagThirdMomData, 3);
};//SHOCDiagThirdMomData

//Create data structure to hold data for compute_diag_third_shoc_moment
struct SHOCCompThirdMomData : public PhysicsTestData {
  // Inputs
  Real *w_sec, *thl_sec, *wthl_sec, *tke, *dz_zt;
  Real *dz_zi, *isotropy_zi, *brunt_zi, *w_sec_zi;
  Real *thetal_zi;

  // Output
  Real *w3;

  SHOCCompThirdMomData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&w_sec, &tke, &dz_zt}, {&thl_sec, &wthl_sec, &isotropy_zi, &dz_zi, &brunt_zi, &w_sec_zi, &thetal_zi, &w3}) {}

  SHOC_NO_SCALAR(SHOCCompThirdMomData, 3);
};//SHOCCompThirdMomData

//Create data structure to hold data for linear_interp
struct SHOCLinearInterpData : public PhysicsTestData {
  // Inputs
  Real minthresh;
  Real *x1, *x2, *y1;

  // In/out
  Real *y2;

  SHOCLinearInterpData(Int shcol_, Int nlev_, Int nlevi_, Real minthresh_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&x1, &y1}, {&x2, &y2}), minthresh(minthresh_) {}

  SHOC_SCALARS(SHOCLinearInterpData, 3, 1, minthresh);
};//SHOCLinearInterpData

//Create data structure to hold data for compute_shr_prod
struct SHOCAssumedpdfData : public PhysicsTestData {
  // Inputs
  Real *thetal, *qw, *w_field, *thl_sec, *qw_sec, *wthl_sec, *w_sec;
  Real *wqw_sec, *qwthl_sec, *w3, *pres, *zt_grid, *zi_grid;

  // Outputs
  Real *shoc_cldfrac, *shoc_ql, *wqls, *wthv_sec, *shoc_ql2;

  //functions to initialize data
  SHOCAssumedpdfData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&thetal, &qw, &w_field, &w_sec, &pres, &zt_grid, &shoc_cldfrac, &shoc_ql, &wqls, &wthv_sec, &shoc_ql2}, {&w3, &thl_sec, &qw_sec, &wthl_sec, &wqw_sec, &qwthl_sec, &zi_grid}) {}

  SHOC_NO_SCALAR(SHOCAssumedpdfData, 3);
};//SHOCAssumedpdfData

//Create data structure to hold data for shoc_assumed_pdf_tilde_to_real
struct SHOCPDFtildeData
{
  // inputs
  Real w_first, sqrtw2;

  // outputs
  Real w1;
};

// Create data structure to hold data for shoc_assumed_pdf_vv_parameters
struct SHOCPDFvvparamData
{
  // inputs
  Real w_first, w_sec, w3var;

  // outputs
  Real Skew_w, w1_1, w1_2, w2_1, w2_2, a;
};

// Create data structure to hold data for shoc_assumed_pdf_thl_parameters
struct SHOCPDFthlparamData
{
  // inputs
  Real wthlsec, sqrtw2, sqrtthl, thlsec, thl_first, w1_1, w1_2, Skew_w, a;
  bool dothetal_skew;

  // outputs
  Real thl1_1, thl1_2, thl2_1, thl2_2, sqrtthl2_1, sqrtthl2_2;
};

// Create data structure to hold data for shoc_assumed_pdf_qw_parameters
struct SHOCPDFqwparamData
{
  // inputs
  Real wqwsec, qwsec, sqrtw2, sqrtqt, qw_first, w1_1, w1_2, Skew_w, a;

  // outputs
  Real qw1_1, qw1_2, qw2_1, qw2_2, sqrtqw2_1, sqrtqw2_2;
};

// Create data structure to hold data for shoc_assumed_pdf_inplume_correlations
struct SHOCPDFinplumeData
{
  // inputs
  Real sqrtqw2_1,sqrtthl2_1,a,sqrtqw2_2,sqrtthl2_2;
  Real qwthlsec,qw1_1,qw_first,thl1_1,thl_first,qw1_2,thl1_2;

  // outputs
  Real r_qwthl_1;
};

//Create data structure to hold data for shoc_assumed_pdf_compute_temperature
struct SHOCPDFcomptempData
{
  // inputs
  Real thl1, basepres, pval;

  // outputs
  Real Tl1;
};

//Create data structure to hold data for shoc_assumed_pdf_compute_qs
struct SHOCPDFcompqsData
{
  // inputs
  Real Tl1_1, Tl1_2, pval;

  // outputs
  Real qs1, beta1, qs2, beta2;
};

//Create data structure to hold data for shoc_assumed_pdf_compute_s
struct SHOCPDFcompsData
{
  // inputs
  Real qw1, qs1, beta, pval, thl2, qw2, sqrtthl2, sqrtqw2, r_qwthl;

  // outputs
  Real s, std_s, qn, C;
};

//Create data structure to hold data for shoc_assumed_pdf_compute_sgs_liquid
struct SHOCPDFcompsgsliqData
{
  // inputs
  Real a, ql1, ql2;

  // outputs
  Real shoc_ql;
};

//Create data structure to hold data for shoc_assumed_pdf_compute_cloud_liquid_variance
struct SHOCPDFcompcloudvarData
{
  // inputs
  Real a, s1, ql1, C1, std_s1, s2, ql2, C2, std_s2, shoc_ql;

  // outputs
  Real shoc_ql2;
};

//Create data structure to hold data for shoc_assumed_pdf_compute_liquid_water_flux
struct SHOCPDFcompliqfluxData
{
  // inputs
  Real a, w1_1, w_first, ql1, w1_2, ql2;

  // outputs
  Real wqls;
};

//Create data structure to hold data for shoc_assumed_pdf_compute_buoyancy_flux
struct SHOCPDFcompbuoyfluxData
{
  // inputs
  Real wthlsec, epsterm, wqwsec, pval, wqls;

  // outputs
  Real wthv_sec;
};

struct SHOCSecondMomentUbycondData : public PhysicsTestData {
  // Outputs
  Real *thl_sec, *qw_sec, *wthl_sec, *wqw_sec, *qwthl_sec;
  Real *uw_sec, *vw_sec, *wtke_sec;

  SHOCSecondMomentUbycondData(Int shcol_) :
    PhysicsTestData(shcol_, {&thl_sec, &qw_sec, &wthl_sec, &wqw_sec, &qwthl_sec, &uw_sec, &vw_sec, &wtke_sec}) {}

  SHOC_NO_SCALAR(SHOCSecondMomentUbycondData, 1);
};

struct SHOCPblintdInitPotData : public PhysicsTestData {
  // inputs
  Real *thl, *ql, *q;

  // outputs
  Real *thv;

  SHOCPblintdInitPotData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&thl, &ql, &q, &thv}) {}

  SHOC_NO_SCALAR(SHOCPblintdInitPotData, 2);
};

struct DiagSecondMomentsLbycondData : public PhysicsTestData {
  // Inputs
  Real *wthl_sfc, *wqw_sfc, *uw_sfc, *vw_sfc, *ustar2, *wstar;

  // Outputs
  Real *wthl_sec, *wqw_sec, *uw_sec, *vw_sec, *wtke_sec, *thl_sec, *qw_sec, *qwthl_sec;

  DiagSecondMomentsLbycondData(Int shcol_) :
    PhysicsTestData(shcol_, {&wthl_sfc, &wqw_sfc, &uw_sfc, &vw_sfc, &ustar2, &wstar, &wthl_sec, &wqw_sec, &uw_sec, &vw_sec, &wtke_sec, &thl_sec, &qw_sec, &qwthl_sec}) {}

  SHOC_NO_SCALAR(DiagSecondMomentsLbycondData, 1)
};
struct DiagSecondMomentsData : public PhysicsTestData {
  // Inputs
  Real *thetal, *qw, *u_wind, *v_wind, *tke, *isotropy, *tkh, *tk, *dz_zi, *zt_grid, *zi_grid, *shoc_mix;

  // Inputs/Outputs
  Real *thl_sec, *qw_sec, *wthl_sec, *wqw_sec, *qwthl_sec, *uw_sec, *vw_sec, *wtke_sec;

  // Outputs
  Real *w_sec;

  DiagSecondMomentsData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&thetal, &qw, &u_wind, &v_wind, &tke, &isotropy, &tkh, &tk, &zt_grid, &shoc_mix, &w_sec}, {&dz_zi, &zi_grid, &thl_sec, &qw_sec, &wthl_sec, &wqw_sec, &qwthl_sec, &uw_sec, &vw_sec, &wtke_sec}) {}

  SHOC_NO_SCALAR(DiagSecondMomentsData, 3)
};
struct DiagSecondShocMomentsData : public PhysicsTestData {
  // Inputs
  Real *thetal, *qw, *u_wind, *v_wind, *tke, *isotropy, *tkh, *tk, *dz_zi, *zt_grid, *zi_grid, *shoc_mix, *wthl_sfc, *wqw_sfc, *uw_sfc, *vw_sfc;

  // Outputs
  Real *thl_sec, *qw_sec, *wthl_sec, *wqw_sec, *qwthl_sec, *uw_sec, *vw_sec, *wtke_sec, *w_sec;

  DiagSecondShocMomentsData(Int shcol_, Int nlev_, Int nlevi_) :
    PhysicsTestData(shcol_, nlev_, nlevi_, {&thetal, &qw, &u_wind, &v_wind, &tke, &isotropy, &tkh, &tk, &zt_grid, &shoc_mix, &w_sec}, {&dz_zi, &zi_grid, &thl_sec, &qw_sec, &wthl_sec, &wqw_sec, &qwthl_sec, &uw_sec, &vw_sec, &wtke_sec}, {&wthl_sfc, &wqw_sfc, &uw_sfc, &vw_sfc}) {}

  SHOC_NO_SCALAR(DiagSecondShocMomentsData, 3)
};

struct SHOCPblintdCldCheckData : public PhysicsTestData {
  // inputs
 Real *zi, *cldn;

 // outputs
  Real *pblh;

  SHOCPblintdCldCheckData(Int shcol_, Int nlev_, Int nlevi_) :
     PhysicsTestData(shcol_, nlev_, nlevi_, {&cldn}, {&zi}, {&pblh}) {}

  SHOC_NO_SCALAR(SHOCPblintdCldCheckData, 3);
};

struct ComputeShocVaporData : public PhysicsTestData {
  // Inputs
  Real *qw, *ql;

  // Outputs
  Real *qv;

  ComputeShocVaporData(Int shcol_, Int nlev_) :
    PhysicsTestData(shcol_, nlev_, {&qw, &ql, &qv}) {}

  SHOC_NO_SCALAR(ComputeShocVaporData, 2)
};
struct UpdatePrognosticsImplicitData : public PhysicsTestDataGeneric {
  // Inputs
  Int shcol, nlev, nlevi, num_tracer;
  Real dtime;
  Real *dz_zt, *dz_zi, *rho_zt, *zt_grid, *zi_grid, *tk, *tkh, *uw_sfc, *vw_sfc, *wthl_sfc, *wqw_sfc, *wtracer_sfc;

  // Inputs/Outputs
  Real *thetal, *qw, *tracer, *tke, *u_wind, *v_wind;

  UpdatePrognosticsImplicitData(Int shcol_, Int nlev_, Int nlevi_, Int num_tracer_, Real dtime_) :
    PhysicsTestDataGeneric({{ shcol, nlev }, { shcol, nlevi }, { shcol }, { shcol, num_tracer }, { shcol, nlev, num_tracer }}, {{ &dz_zt, &rho_zt, &zt_grid, &tk, &tkh, &thetal, &qw, &tke, &u_wind, &v_wind }, { &dz_zi, &zi_grid }, { &uw_sfc, &vw_sfc, &wthl_sfc, &wqw_sfc }, { &wtracer_sfc }, { &tracer }}, {}), shcol(shcol_), nlev(nlev_), nlevi(nlevi_), num_tracer(num_tracer_), dtime(dtime_) {}

  PTDG_STD_DEF(UpdatePrognosticsImplicitData, 5, shcol, nlev, nlevi, num_tracer, dtime);
};
// Glue functions to call fortran from from C++ with the Data struct
void shoc_grid                                      (SHOCGridData &d);
void shoc_diag_obklen                               (SHOCObklenData &d);
void update_host_dse                                (SHOCEnergydseData &d);
void shoc_energy_fixer                              (SHOCEnergyfixerData &d);
void shoc_energy_integrals                          (SHOCEnergyintData &d);
void shoc_energy_total_fixer                        (SHOCEnergytotData &d);
void shoc_energy_threshold_fixer                    (SHOCEnergythreshfixerData &d);
void shoc_energy_dse_fixer                          (SHOCEnergydsefixerData &d);
void calc_shoc_vertflux                             (SHOCVertfluxData &d);
void calc_shoc_varorcovar                           (SHOCVarorcovarData &d);
void compute_tmpi                                   (SHOCComptmpiData &d);
void dp_inverse                                     (SHOCDpinverseData &d);
void sfc_fluxes                                     (SHOCSfcfluxesData &d);
void impli_srf_stress_term                          (SHOCImplsrfstressData &d);
void tke_srf_flux_term                              (SHOCTkesrffluxData &d);
void integ_column_stability                         (SHOCColstabData &d);
void check_tke                                      (SHOCCheckTkeData &d);
void shoc_tke                                       (SHOCTkeData &d);
void compute_shr_prod                               (SHOCTkeshearData &d);
void isotropic_ts                                   (SHOCIsotropicData &d);
void adv_sgs_tke                                    (SHOCAdvsgstkeData &d);
void eddy_diffusivities                             (SHOCEddydiffData &d);
void shoc_length                                    (SHOCLengthData &d);
void compute_brunt_shoc_length                      (SHOCBruntlengthData &d);
void compute_l_inf_shoc_length                      (SHOCInflengthData &d);
void compute_conv_vel_shoc_length                   (SHOCConvvelData &d);
void compute_conv_time_shoc_length                  (SHOCConvtimeData &d);
void compute_shoc_mix_shoc_length                   (SHOCMixlengthData &d);
void check_length_scale_shoc_length                 (SHOCMixcheckData &d);
void fterms_input_for_diag_third_shoc_moment        (SHOCFterminputthirdmomsData &d);
void aa_terms_diag_third_shoc_moment                (SHOCAAdiagthirdmomsData &d);
void f0_to_f5_diag_third_shoc_moment                (SHOCFtermdiagthirdmomsData &d);
void omega_terms_diag_third_shoc_moment             (SHOCOmegadiagthirdmomsData &d);
void x_y_terms_diag_third_shoc_moment               (SHOCXYdiagthirdmomsData &d);
void w3_diag_third_shoc_moment                      (SHOCW3diagthirdmomsData &d);
void clipping_diag_third_shoc_moments               (SHOCClipthirdmomsData &d);
void shoc_diag_second_moments_srf                   (SHOCSecondMomentSrfData& d);
void linear_interp                                  (SHOCLinearInterpData &d);
void diag_third_shoc_moments                        (SHOCDiagThirdMomData &d);
void compute_diag_third_shoc_moment                 (SHOCCompThirdMomData &d);
void shoc_assumed_pdf                               (SHOCAssumedpdfData &d);
void shoc_assumed_pdf_tilde_to_real                 (SHOCPDFtildeData &d);
void shoc_assumed_pdf_vv_parameters                 (SHOCPDFvvparamData &d);
void shoc_assumed_pdf_thl_parameters                (SHOCPDFthlparamData &d);
void shoc_assumed_pdf_qw_parameters                 (SHOCPDFqwparamData &d);
void shoc_assumed_pdf_inplume_correlations          (SHOCPDFinplumeData &d);
void shoc_assumed_pdf_compute_temperature           (SHOCPDFcomptempData &d);
void shoc_assumed_pdf_compute_qs                    (SHOCPDFcompqsData &d);
void shoc_assumed_pdf_compute_s                     (SHOCPDFcompsData &d);
void shoc_assumed_pdf_compute_sgs_liquid            (SHOCPDFcompsgsliqData &d);
void shoc_assumed_pdf_compute_cloud_liquid_variance (SHOCPDFcompcloudvarData &d);
void shoc_assumed_pdf_compute_liquid_water_flux     (SHOCPDFcompliqfluxData &d);
void shoc_assumed_pdf_compute_buoyancy_flux         (SHOCPDFcompbuoyfluxData &d);
void shoc_diag_second_moments_ubycond               (SHOCSecondMomentUbycondData& d);
void shoc_pblintd_init_pot                          (SHOCPblintdInitPotData &d);
void shoc_pblintd_cldcheck                          (SHOCPblintdCldCheckData& d);
void diag_second_moments_lbycond                    (DiagSecondMomentsLbycondData& d);

void diag_second_moments(DiagSecondMomentsData& d);
void diag_second_shoc_moments(DiagSecondShocMomentsData& d);
void compute_shoc_vapor(ComputeShocVaporData& d);
void update_prognostics_implicit(UpdatePrognosticsImplicitData& d);
extern "C" { // _f function decls

void calc_shoc_varorcovar_f(Int shcol, Int nlev, Int nlevi, Real tunefac,
                            Real *isotropy_zi, Real *tkh_zi, Real *dz_zi,
                            Real *invar1, Real *invar2, Real *varorcovar);
void calc_shoc_vertflux_f(Int shcol, Int nlev, Int nlevi, Real *tkh_zi,
			  Real *dz_zi, Real *invar, Real *vertflux);
void shoc_diag_second_moments_srf_f(Int shcol, Real* wthl, Real* uw, Real* vw,
                          Real* ustar2, Real* wstar);
void shoc_diag_second_moments_ubycond_f(Int shcol, Real* thl, Real* qw, Real* wthl,
                          Real* wqw, Real* qwthl, Real* uw, Real* vw, Real* wtke);
void update_host_dse_f(Int shcol, Int nlev, Real* thlm, Real* shoc_ql, Real* exner, Real* zt_grid,
                       Real* phis, Real* host_dse);
void compute_diag_third_shoc_moment_f(Int shcol, Int nlev, Int nlevi, Real* w_sec,
                                      Real* thl_sec, Real* wthl_sec, Real* tke,
                                      Real* dz_zt, Real* dz_zi, Real* isotropy_zi,
                                      Real* brunt_zi, Real* w_sec_zi, Real* thetal_zi,
                                      Real* w3);
void shoc_pblintd_init_pot_f(Int shcol, Int nlev, Real* thl, Real* ql, Real* q, Real* thv);
void compute_shoc_mix_shoc_length_f(Int nlev, Int shcol, Real* tke, Real* brunt,
                                    Real* tscale, Real* zt_grid, Real* l_inf, Real* shoc_mix);
void check_tke_f(Int shcol, Int nlev, Real* tke);
void linear_interp_f(Real* x1, Real* x2, Real* y1, Real* y2, Int km1, Int km2, Int ncol, Real minthresh);
void clipping_diag_third_shoc_moments_f(Int nlevi, Int shcol, Real *w_sec_zi,
                                        Real *w3);
void shoc_energy_integrals_f(Int shcol, Int nlev, Real *host_dse, Real *pdel,
                             Real *rtm, Real *rcm, Real *u_wind, Real *v_wind,
                             Real *se_int, Real *ke_int, Real *wv_int, Real *wl_int);
void compute_brunt_shoc_length_f(Int nlev, Int nlevi, Int shcol, Real* dz_zt, Real* thv,
                                 Real* thv_zi, Real* brunt);
void compute_l_inf_shoc_length_f(Int nlev, Int shcol, Real *zt_grid, Real *dz_zt,
                                 Real *tke, Real *l_inf);
void check_length_scale_shoc_length_f(Int nlev, Int shcol, Real* host_dx, Real* host_dy,
                                      Real* shoc_mix);
void compute_conv_vel_shoc_length_f(Int nlev, Int shcol, Real *pblh, Real *zt_grid,
                                    Real *dz_zt, Real *thv, Real *wthv_sec,
                                    Real *conv_vel);
void diag_second_moments_lbycond_f(Int shcol, Real* wthl_sfc, Real* wqw_sfc, Real* uw_sfc, Real* vw_sfc, Real* ustar2, Real* wstar,
                                  Real* wthl_sec, Real* wqw_sec, Real* uw_sec, Real* vw_sec, Real* wtke_sec, Real* thl_sec,
                                  Real* qw_sec, Real* qwthl_sec);
void diag_second_moments_f(Int shcol, Int nlev, Int nlevi, Real* thetal, Real* qw, Real* u_wind, Real* v_wind, Real* tke, Real* isotropy, Real* tkh, Real* tk, Real* dz_zi, Real* zt_grid, Real* zi_grid, Real* shoc_mix, Real* thl_sec, Real* qw_sec, Real* wthl_sec, Real* wqw_sec, Real* qwthl_sec, Real* uw_sec, Real* vw_sec, Real* wtke_sec, Real* w_sec);
void diag_second_shoc_moments_f(Int shcol, Int nlev, Int nlevi, Real* thetal, Real* qw, Real* u_wind, Real* v_wind, Real* tke, Real* isotropy, Real* tkh, Real* tk, Real* dz_zi, Real* zt_grid, Real* zi_grid, Real* shoc_mix, Real* wthl_sfc, Real* wqw_sfc, Real* uw_sfc, Real* vw_sfc, Real* thl_sec, Real* qw_sec, Real* wthl_sec, Real* wqw_sec, Real* qwthl_sec, Real* uw_sec, Real* vw_sec, Real* wtke_sec, Real* w_sec);
void shoc_diag_obklen_f(Int shcol, Real* uw_sfc, Real* vw_sfc, Real* wthl_sfc, Real* wqw_sfc,
                        Real* thl_sfc, Real* cldliq_sfc, Real* qv_sfc, Real* ustar, Real* kbfs, Real* obklen);
void shoc_pblintd_cldcheck_f(Int shcol, Int nlev, Int nlevi, Real* zi, Real* cldn, Real* pblh);
void compute_conv_time_shoc_length_f(Int shcol, Real *pblh, Real *conv_vel,
                                     Real *tscale);
void shoc_length_f(Int shcol, Int nlev, Int nlevi, Real* host_dx, Real* host_dy, Real* pblh, Real* tke,
                   Real* zt_grid, Real* zi_grid, Real*dz_zt, Real* dz_zi, Real* wthv_sec, Real*thetal,
                   Real* thv, Real*brunt, Real* shoc_mix);
void shoc_energy_fixer_f(Int shcol, Int nlev, Int nlevi, Real dtime, Int nadv, Real* zt_grid,
                         Real* zi_grid, Real* se_b, Real* ke_b, Real* wv_b, Real* wl_b,
                         Real* se_a, Real* ke_a, Real* wv_a, Real* wl_a, Real* wthl_sfc,
                         Real* wqw_sfc, Real* rho_zt, Real* tke, Real* pint,
                         Real* host_dse);
void compute_shoc_vapor_f(Int shcol, Int nlev, Real* qw, Real* ql, Real* qv);
void update_prognostics_implicit_f(Int shcol, Int nlev, Int nlevi, Int num_tracer, Real dtime, Real* dz_zt, Real* dz_zi, Real* rho_zt, Real* zt_grid, Real* zi_grid, Real* tk, Real* tkh, Real* uw_sfc, Real* vw_sfc, Real* wthl_sfc, Real* wqw_sfc, Real* wtracer_sfc, Real* thetal, Real* qw, Real* tracer, Real* tke, Real* u_wind, Real* v_wind);
void diag_third_shoc_moments_f(Int shcol, Int nlev, Int nlevi, Real* w_sec, Real* thl_sec,
                               Real* wthl_sec, Real* isotropy, Real* brunt, Real* thetal,
                               Real* tke, Real* dz_zt, Real* dz_zi, Real* zt_grid, Real* zi_grid,
                               Real* w3);
void shoc_assumed_pdf_f(Int shcol, Int nlev, Int nlevi, Real* thetal, Real* qw, Real* w_field,
                        Real* thl_sec, Real* qw_sec, Real* wthl_sec, Real* w_sec, Real* wqw_sec,
                        Real* qwthl_sec, Real* w3, Real* pres, Real* zt_grid, Real* zi_grid,
                        Real* shoc_cldfrac, Real* shoc_ql, Real* wqls, Real* wthv_sec, Real* shoc_ql2);

} // end _f function decls

}  // namespace shoc
}  // namespace scream

#endif // SCREAM_SHOC_FUNCTIONS_F90_HPP
