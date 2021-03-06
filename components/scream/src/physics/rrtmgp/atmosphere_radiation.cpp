#include "ekat/ekat_assert.hpp"
#include "physics/rrtmgp/scream_rrtmgp_interface.hpp"
#include "physics/rrtmgp/atmosphere_radiation.hpp"

namespace scream {
    RRTMGPRadiation::RRTMGPRadiation (const ekat::Comm& comm, const ekat::ParameterList& params) : m_rrtmgp_comm (comm), m_rrtmgp_params (params) {
        /*
         * Anything that can be initialized without grid information can be initialized here.
         * I.e., universal constants, options, etc.
         */
    }  // RRTMGPRadiation::RRTMGPRadiation

    void RRTMGPRadiation::set_grids(const std::shared_ptr<const GridsManager> grids_manager) {

    }  // RRTMGPRadiation::set_grids

    void RRTMGPRadiation::initialize_impl(const util::TimeStamp& t0) {
        // Call RRTMGP initialize routine
        //rrtmgp_initialize()
    }
    void RRTMGPRadiation::run_impl      (const Real dt) {}
    void RRTMGPRadiation::finalize_impl  () {}

    // Register all required and computed field in the field repository
    void RRTMGPRadiation::register_fields(FieldRepository<Real>& field_repo) const {
        for (auto& fid: m_required_fields) { field_repo.register_field(fid); }
        for (auto& fid: m_computed_fields) { field_repo.register_field(fid); }
    }

    void RRTMGPRadiation::set_required_field_impl(const Field<const Real>& f) {
        /* The following copied from the P3 code */
        //const auto& name = f.get_header().get_identifier().name();
        //m_rrtmgp_fields_in.emplace(name,f);
        //m_rrtmgp_host_views_in[name] = Kokkos::create_mirror_view(f.get_view());
        //m_raw_ptrs_in[name] = m_rrtmgp_host_views_in[name].data();

        // Add myself as customer to the field
        //add_me_as_customer(f);
    }

    void RRTMGPRadiation::set_computed_field_impl(const Field<      Real>& f) {
        /* The following copied from the P3 code */
        //const auto& name = f.get_header().get_identifier().name();
        //m_rrtmgp_fields_out.emplace(name,f);
        //m_rrtmgp_host_views_out[name] = Kokkos::create_mirror_view(f.get_view());
        //m_raw_ptrs_out[name] = m_rrtmgp_host_views_out[name].data();

        // Add myself as provider for the field
        //add_me_as_provider(f);
    }

}  // namespace scream
