// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

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
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, int mat, int mf, int mt, int njsx ) -> Component {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      return Component( begin, end, lineNumber, mat, mf, mt, njsx );
    },
    python::arg( "string" ), python::arg( "mat" ),
    python::arg( "mf" ), python::arg( "mt" ),
    python::arg( "njsx" ),
    "Read the component from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "component\n\n"
    "Arguments:\n"
    "    string    the string representing the component\n"
    "    mat       the MAT number of the section\n"
    "    mf        the MF number of the section\n"
    "    mt        the MT number of the section\n"
    "    njsx      the number of spin groups"
  );

  // add standard component definitions
  addStandardComponentDefinitionsWithoutReading< Component >( component );
}

} // namespace mf32
