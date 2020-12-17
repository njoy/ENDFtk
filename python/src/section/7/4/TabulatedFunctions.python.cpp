// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapTabulatedFunctions( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 7, 4 >::TabulatedFunctions;
  using ScatteringFunction = njoy::ENDFtk::section::Type< 7, 4 >::TabulatedFunctions::ScatteringFunction;
  using ScatteringFunctionRange = RandomAccessAnyView< ScatteringFunction >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ScatteringFunction >(
      viewmodule,
      "any_view< ScatteringFunction, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedFunctions",
    "MF7 MT4 section - tabulated incoherent inelastic scattering law"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< ScatteringFunction >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "functions" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    functions       the beta values and associated S(alpha,T) functions"
  )
  .def_property_readonly(

    "NB",
    &Component::NB,
    "The number of beta values"
  )
  .def_property_readonly(

    "number_betas",
    &Component::numberBetas,
    "The number of beta values"
  )
  .def_property_readonly(

    "B",
    [] ( const Component& self ) -> DoubleRange
       { return self.B(); },
    "The beta values"
  )
  .def_property_readonly(

    "betas",
    [] ( const Component& self ) -> DoubleRange
       { return self.betas(); },
    "The beta values"
  )
  .def_property_readonly(

    "S",
    [] ( const Component& self ) -> ScatteringFunctionRange
       { return self.S(); },
    "The beta values and associated S(alpha,T) functions"
  )
  .def_property_readonly(

    "scattering_functions",
    [] ( const Component& self ) -> ScatteringFunctionRange
       { return self.scatteringFunctions(); },
    "The beta values and associated S(alpha,T) functions"
  );

  // add standard tab1 definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf7
