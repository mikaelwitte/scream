#ifndef P3_FUNCTIONS_ICE_MELTING_IMPL_HPP
#define P3_FUNCTIONS_ICE_MELTING_IMPL_HPP

#include "p3_functions.hpp" // for ETI only but harmless for GPU

namespace scream {
namespace p3 {

template<typename S, typename D>
KOKKOS_FUNCTION
void Functions<S,D>
::ice_melting(const Spack& rho, const Spack& t, const Spack& pres, const Spack& rhofaci,
	      const Spack& f1pr05, const Spack& f1pr14, const Spack& xxlv, const Spack& xlf, 
	      const Spack& dv, const Spack& sc, const Spack& mu, const Spack& kap, 
	      const Spack& qv, const Spack& qitot_incld, const Spack& nitot_incld,
	      Spack& qimlt, Spack& nimlt)
{
}

} // namespace p3
} // namespace scream

#endif
