// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf2 {

void wrapUnresolvedEnergyDependentLValue( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::UnresolvedEnergyDependent::LValue;
  using JValue = Section::UnresolvedEnergyDependent::JValue;
  using JValueRange = RandomAccessAnyView< JValue >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< JValue >(
      viewmodule,
      "any_view< UnresolvedEnergyDependentJValue, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedEnergyDependentLValue",
    "MF2 MT151 section - unresolved resonance parameters for a given l value\n"
    "                    for energy dependent widths"
  );

  // wrap the section
  component
  .def(

    python::init< double, int, std::vector< JValue >&& >(),
    python::arg( "awri" ), python::arg( "l" ), python::arg( "jvalues" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    awri       the atomic weight ratio\n"
    "    l          the orbital angular momentum value\n"
    "    jvalues    the unresolved resonance parameters for every J value\n"
    "               (NJS elements)"
  )
  .def_property_readonly(

    "AWRI",
    [] ( const Component& self ) { return self.AWRI(); },
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    [] ( const Component& self ) { return self.atomicWeightRatio(); },
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "L",
    [] ( const Component& self ) { return self.L(); },
    "The value of the orbital momentum l"
  )
  .def_property_readonly(

    "orbital_momentum",
    [] ( const Component& self ) { return self.orbitalMomentum(); },
    "The value of the orbital momentum l"
  )
  .def_property_readonly(

    "NJS",
    [] ( const Component& self ) { return self.NJS(); },
    "The number of J values for this l value"
  )
  .def_property_readonly(

    "number_spin_values",
    [] ( const Component& self ) { return self.numberSpinValues(); },
    "The number of J values for this l value"
  )
  .def_property_readonly(

    "j_values",
    [] ( const Component& self ) -> JValueRange
       { return self.jValues(); },
    "The data for each of the J values"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf2
