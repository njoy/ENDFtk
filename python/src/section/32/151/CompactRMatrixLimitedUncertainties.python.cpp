// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapCompactRMatrixLimitedUncertainties( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using ParticlePairs = Section::CompactRMatrixLimitedUncertainties::ParticlePairs;
  using SpinGroup = Section::CompactRMatrixLimitedUncertainties::SpinGroup;
  using SpinGroupRange = RandomAccessAnyView< SpinGroup >;
  using Component = Section::CompactRMatrixLimitedUncertainties;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< SpinGroup >(
      viewmodule,
      "any_view< MF32::SpinGroup, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "CompactRMatrixLimitedUncertainties",
    "MF32 MT151 section - The resonance parameters and uncertainties in the "
    "                     R-matrix limited representation (LCOMP = 2)"
  );

  // wrap the section
  component
  .def(

    python::init( [] ( ParticlePairs pairs,
                       std::vector< SpinGroup > groups )
                     { return Component( std::move( pairs ),
                                         std::move( groups ) ); } ),
    python::arg( "pairs" ), python::arg( "groups" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self     the component\n"
    "    pairs    the particle pairs\n"
    "    groups   the spin groups"
  )
  .def_property_readonly(

    "NJSX",
    &Component::NJSX,
    "The number of spin groups"
  )
  .def_property_readonly(

    "number_spin_groups",
    &Component::numberSpinGroups,
    "The number of spin groups"
  )
  .def_property_readonly(

    "particle_pairs",
    &Component::particlePairs,
    "The particle pair information"
  )
  .def_property_readonly(

    "spin_groups",
    [] ( const Component& self ) -> SpinGroupRange
       { return self.spinGroups(); },
    "The spin groups"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
