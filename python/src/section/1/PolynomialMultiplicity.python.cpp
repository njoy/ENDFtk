// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrap_1_PolynomialMultiplicity( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::PolynomialMultiplicity;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "PolynomialMultiplicity",
    "MF1 component - fission multiplicity given as a polynomial expansion"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >&& >(),
    python::arg( "coefficients" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    coefficients    the polynomial coefficients"
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

    "NCO",
    &Component::NCO,
    "The number of coefficients in the polynomial expansion"
  )
  .def_property_readonly(

    "number_coefficients",
    &Component::numberCoefficients,
    "The number of coefficients in the polynomial expansion"
  )
  .def_property_readonly(

    "C",
    [] ( const Component& self ) -> DoubleRange
       { return self.C(); },
    "The coefficients"
  )
  .def_property_readonly(

    "coefficients",
    [] ( const Component& self ) -> DoubleRange
       { return self.coefficients(); },
    "The coefficients"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
