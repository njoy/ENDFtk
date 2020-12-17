// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section/1/456.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_1_456( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 456 >;
  using Multiplicity = njoy::ENDFtk::section::Type< 1, 456 >::Multiplicity;

  // wrap views created by this section

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT456",
    "MT456 - the number of prompt fission neutrons"
  );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF1 MT456 section - the number of prompt fission neutrons"
  );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr, Multiplicity multiplicity )
                     { return Section( zaid, awr,
                                       std::move( multiplicity ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "multiplicity" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self            the section\n"
    "    zaid            the ZA value of the material\n"
    "    awr             the atomic weight ratio\n"
    "    multiplicity    the multiplicity data"
  )
  .def_property_readonly(

    "LNU",
    &Section::LNU,
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "representation",
    &Section::representation,
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "nubar",
    &Section::nubar,
    "The fission multiplicity data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
