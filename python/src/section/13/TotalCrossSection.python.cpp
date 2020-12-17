// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/13.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTotalCrossSection( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 13 >::TotalCrossSection;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "TotalCrossSection",
    "MF13 section - the total photon production cross section"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component\n"
    "    boundaries        the interpolation range boundaries\n"
    "    interpolants      the interpolation types for each range\n"
    "    energies          the energy values\n"
    "    xs                the cross section values"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "XS",
    [] ( const Component& self ) -> DoubleRange
       { return self.XS(); },
    "The cross section values"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Component& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
