// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section/1/458.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt458 {

  // declarations - components
  void wrapEnergyReleaseComponent( python::module& );
  void wrapThermalPointComponents( python::module& );
  void wrapPolynomialComponents( python::module& );

}
}

void wrapSection_1_458( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 458 >;

  // wrap views created by this section

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT458",
    "MT458 - fission energy release components"
  );

  // wrap components
  mf1::mt458::wrapEnergyReleaseComponent( submodule );
  mf1::mt458::wrapThermalPointComponents( submodule );
  mf1::mt458::wrapPolynomialComponents( submodule );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF1 MT458 section - fission energy release components"
  );

  // wrap the section
//  section
//  .def(
//
//    //! @todo pybind11 lambda move custom type workaround
//    python::init( [] ( double zaid, double awr, DecayConstantData constants,
//                       Multiplicity multiplicity )
//                     { return Section( zaid, awr,
//                                       std::move( constants ),
//                                       std::move( multiplicity ) ); } ),
//    python::arg( "zaid" ), python::arg( "awr" ),
//    python::arg( "constants" ), python::arg( "multiplicity" ),
//    "Initialise the section\n\n"
//    "Arguments:\n"
//    "    self            the section\n"
//    "    zaid            the ZA value of the material\n"
//    "    awr            the atomic weight ratio\n"
//    "    constants       the decay constant data\n"
//    "    multiplicity    the multiplicity data"
//  )
//  .def_property_readonly(
//
//    "LNU",
//    &Section::LNU,
//    "The fission multiplicity representation type"
//  )
//  .def_property_readonly(
//
//    "representation",
//    &Section::representation,
//    "The fission multiplicity representation type"
//  )
//  .def_property_readonly(
//
//    "LDG",
//    &Section::LDG,
//    "The type of decay constants"
//  )
//  .def_property_readonly(
//
//    "type",
//    &Section::type,
//    "The type of decay constants"
//  )
//  .def_property_readonly(
//
//    "delayed_groups",
//    &Section::delayedGroups,
//    "The decay constant data for the delayed precursor groups"
//  )
//  .def_property_readonly(
//
//    "nubar",
//    &Section::nubar,
//    "The fission multiplicity data"
//  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
