// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/451.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

  // declarations - components
  void wrapElementInformation( python::module&, python::module& );

}

void wrapSection_7_451( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 7, 451 >;
  using ElementInformation = Section::ElementInformation;

  // wrap views created by this section

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT451",
    "MT451 - thermal scattering general information"
  );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF7 MT451 section - thermal scattering general information"
  );

  // wrap components
  mf7::wrapElementInformation( submodule, viewmodule );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init< double, double, std::vector< ElementInformation >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "elements" ),
    "Initialise the section using isotopes\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    zaid        the ZA value of the material\n"
    "    awr         the atomic weight ratio\n"
    "    elements    the elements (at least 1)"
  )
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr,
                       ElementInformation element )
                     { return Section( zaid, awr, std::move( element ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "element" ),
    "Initialise the section using isotopes\n\n"
    "Arguments:\n"
    "    self       the section\n"
    "    zaid       the ZA value of the material\n"
    "    awr        the atomic weight ratio\n"
    "    element    the element information"
  )
  .def_property_readonly(

    "NA",
    &Section::NA,
    "The number of elements"
  )
  .def_property_readonly(

    "number_elements",
    &Section::numberElements,
    "The number of elements"
  )
  .def_property_readonly(

    "elements",
    &Section::elements,
    "The element data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
