// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/455.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt455 {

void wrapDecayConstants( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 455 >;
  using Component = Section::DecayConstants;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "DecayConstants",
    "MF1 MT455 component - decay constants for delayed neutron precursors at "
    "                      a given incident energy"
  );

  // wrap the component
  component
  .def(

    python::init< double, std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "constants" ),
    python::arg( "abundances" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    energy        the incident neutron energy\n"
    "    constants     the precursor families decay constants\n"
    "    abundances    the precursor families decay abundances"
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

    "E",
    &Component::E,
    "The incident energy value"
  )
  .def_property_readonly(

    "incident_energy",
    &Component::incidentEnergy,
    "The incident energy value"
  )
  .def_property_readonly(

    "lambdas",
    [] ( const Component& self ) -> DoubleRange
       { return self.lambdas(); },
    "The decay constants"
  )
  .def_property_readonly(

    "decay_constants",
    [] ( const Component& self ) -> DoubleRange
       { return self.decayConstants(); },
    "The decay constants"
  )
  .def_property_readonly(

    "alphas",
    [] ( const Component& self ) -> DoubleRange
       { return self.alphas(); },
    "The abundance values"
  )
  .def_property_readonly(

    "abundances",
    [] ( const Component& self ) -> DoubleRange
       { return self.abundances(); },
    "The abundance values"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mt455
} // namespace mf1
