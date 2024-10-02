// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDistributionFunction( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 5 >;
  using Component = Section::DistributionFunction;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "DistributionFunction",
    "MF5 section - a distribution function y = f(x)"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "x" ), python::arg( "g" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    x               the x values\n"
    "    g               the function values"
  )
  .def_property_readonly(

    "X",
    [] ( const Component& self ) -> DoubleRange
       { return self.X(); },
    "The x values"
  )
  .def_property_readonly(

    "G",
    [] ( const Component& self ) -> DoubleRange
       { return self.G(); },
    "The function values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
