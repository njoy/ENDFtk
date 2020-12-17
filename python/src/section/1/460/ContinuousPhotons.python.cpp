// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/460.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt460 {

void wrapContinuousPhotons( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 1, 460 >::ContinuousPhotons;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ContinuousPhotons",
    "MF1 MT460 component - decay constants for delayed photon precursors"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >&& >(),
    python::arg( "constants" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    constants     the precursor families decay constants"
  )
  .def_property_readonly(

    "LO",
    [] ( const Component& self ) { return self.LO(); },
    "The representation type for the delayed photon data"
  )
  .def_property_readonly(

    "representation",
    &Component::representation,
    "The representation type for the delayed photon data"
  )
  .def_property_readonly(

    "NG",
    [] ( const Component& self ) { return self.NG(); },
    "The number of discrete photons"
  )
  .def_property_readonly(

    "number_discrete_photons",
    &Component::numberDiscretePhotons,
    "The number of discrete photons"
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

} // namespace mt460
} // namespace mf1
