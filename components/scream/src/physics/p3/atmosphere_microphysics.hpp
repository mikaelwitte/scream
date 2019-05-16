#ifndef SCREAM_P3_PHYSICS_HPP
#define SCREAM_P3_PHYSICS_HPP

// Include headers for scream atmospheric process
#include "share/atmosphere_process.hpp"
#include "share/parameter_list.hpp"

#include <string>

// Put everything into a scream namespace
namespace scream
{
/*
 * The class responsible to handle the atmosphere microphysics
 *
 * The AD should store exactly ONE instance of this class stored
 * in its list of subcomponents (the AD should make sure of this).
 *
 *  Note: for now, Scream is only going to accommodate P3 as a microphysics
 *  process.
*/

// Define the P3Microphysics class
class P3Microphysics : public AtmosphereProcess
{
public:
  using field_type       = Field<      Real,device_type>;
  using const_field_type = Field<const Real,device_type>;

  // Constructor(s)
  P3Microphysics (const Comm& comm, const ParameterList& params);

  // The type of subcomponent (dynamics or physics)
  AtmosphereProcessType type () const { return AtmosphereProcessType::Physics; }

  std:set<std::string> get_required_grids () const {
    static std::set<std::string> s;
    s.insert("Physics");
  }

  // The name of the subcomponent
  std::string name () const { return "Physics"; }

  // The communicator used by the physics
  const Comm& get_comm () { return m_physics_comm; }

  // The three main interfaces:
  void initialize (const std::shared_ptr<const GridsManager> grids_manager);
  void run        (/* some inputs */);
  void finalize   (/* some inputs */);

  // Register all fields in the given repo
  void register_fields (FieldRepository<Real, device_type>& field_repo) const;


protected:

  // Setting the field in the atmosphere process
  void set_required_field_impl (const Field<const Real, device_type>& f) {
    m_phys_fields_in.emplace(f.get_header().get_identifier().name(), f);
  }
  void set_computed_field_impl (const Field<Real, device_type>& f) {
    m_phys_fields_out.emplace(f.get_header().get_identifier().name(), f);
  }

  std::set<FieldIdentifier> m_required_fields;
  std::set<FieldIdentifier> m_computed_fields;

  std::map<std::string,const_field_type>  m_phys_fields_in;
  std::map<std::string,field_type>        m_phys_fields_out;

  Comm m_physics_comm;

/* 
 * AaronDonahue: Question
 * above you have m_dyn_fields in the HOMME code, does "dyn" refer to the process
 * or the subcomponent type.  In other words, should it be m_phys_fields here or
 * m_microphys_fields?  Or something like that.
 *
 * Same question for the Comm as it is defined.  Should it be m_physics_comm or
 * m_microphysics_comm?
 *
 */


}; class P3Microphysics
  

inline AtmosphereProcess*
create_atmosphere_microphysics(const Comm& comm, const ParameterList& p) {
  return new P3Microphysics(comm,p);
}


} // namespace scream

#endif // SCREAM_P3_PHYSICS_HPP
