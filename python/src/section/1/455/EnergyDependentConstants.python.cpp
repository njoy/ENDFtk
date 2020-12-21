// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt455 {

void wrapEnergyDependentConstants( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 1, 455 >::EnergyDependentConstants;
  using DecayConstants = njoy::ENDFtk::section::Type< 1, 455 >::DecayConstants;
  using DecayConstantsRange = RandomAccessAnyView< DecayConstants >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< DecayConstants >(
      module,
      "any_view< DecayConstants, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "EnergyDependentConstants",
    "MF1 MT455 component - energy dependent decay constants for delayed "
    "                      neutron precursor families (LDG = 1)"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< DecayConstants >&& >(),
    python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "constants" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    constants       the decay constants"
  )
  .def_property_readonly(

    "LDG",
    [] ( const Component& self ) { return self.LDG(); },
    "The type of decay constants"
  )
  .def_property_readonly(

    "type",
    &Component::type,
    "The type of decay constants"
  )
  .def_property_readonly(

    "NNF",
    &Component::NNF,
    "The number of delayed neutron precursors"
  )
  .def_property_readonly(

    "number_precursors",
    &Component::numberPrecursors,
    "The number of delayed neutron precursors"
  )
  .def_property_readonly(

    "NE",
    &Component::NE,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "incident_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.incidentEnergies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "constants",
    [] ( const Component& self ) -> DecayConstantsRange
       { return self.constants(); },
    "The decay contants"
  );

  // add standard tab1 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mt455
} // namespace mf1
