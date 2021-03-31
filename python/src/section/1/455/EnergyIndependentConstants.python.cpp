// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/455.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt455 {

void wrapEnergyIndependentConstants( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 455 >;
  using Component = Section::EnergyIndependentConstants;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "EnergyIndependentConstants",
    "MF1 MT455 component - energy independent decay constants for delayed\n"
    "                      neutron precursor families (LDG = 0)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >&& >(),
    python::arg( "constants" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    constants    the precursor families decay constants"
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
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mt455
} // namespace mf1
