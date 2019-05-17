// Include headers for scream and for microphysics
// #include "share/scream_assert.hpp"
// #include "Context.hpp"
// #include "mpi/MpiContext.hpp"
#include "atmosphere_microphysics.hpp"

// Put everything into a local "scream namespace"
namespace scream
{

// Construct the P3 microphysics atmospheric object.
P3Microphysics::P3Microphysics (const Comm& comm, const ParameterList& /* params */)
{

} //P3Microphysics

// Set grid for p3 microphysics
void P3Microphysics::set_grid (const std:shared_ptr<const GridsManager> /* grids_manager */)
{
  // Get the grid from the grids manager.
}

// Define the intialization of P3Microphysics
void P3Microphysics::initialize ()
{

   p3_init_f90();

} // initialize

// Define the run sequence of P3Microphysics
void P3Microphysics::run (/* some inputs */)
{

  try {
    p3_main_f90();
  } catch (std:exception& e) {
    error:runtime_abort(e.what());
  } catch (...) {
    error::runtime_abort("Something went wrong in P3 microphysics, but we don't know what.\n");
  }
} //run

// Define the finalization sequence of P3Microphysics
void P3Microphysics::finalize (/* what inputs */)
{
  p3_finalize_f90();
} // finalize

void P3Microphysics::register_fields (FieldRepository<Real, device_type>& /*field_repo*/) const {
  // register device fields in the repo
}
void P3Microphysics::set_required_field_impl (const Field<const Real, device_type>& /*f*/) {
  /* impl */
}
void P3Microphysics::set_computed_field_impl (const Field<      Real, device_type>& /*f*/) {
  /* impl */
}

} // namespace scream
