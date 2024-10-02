// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrap_1_TabulatedMultiplicity( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::TabulatedMultiplicity;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedMultiplicity",
    "MF1 component - energy dependent fission multiplicity"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "multiplicities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component\n"
    "    boundaries        the interpolation range boundaries\n"
    "    interpolants      the interpolation types for each range\n"
    "    energies          the cosine values\n"
    "    multiplicities    the fission multiplicity values"
  )
  .def_property_readonly(

    "LNU",
    [] ( const Component& self ) { return self.LNU(); },
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "representation",
    [] ( const Component& self ) { return self.representation(); },
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "NU",
    [] ( const Component& self ) -> DoubleRange
       { return self.NU(); },
    "The fission multiplicity values"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Component& self ) -> DoubleRange
       { return self.multiplicities(); },
    "The fission multiplicity values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
