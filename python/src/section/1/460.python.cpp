// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section/1/460.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt460 {

  // declarations - components
  void wrapDiscretePhotonMultiplicity( python::module& );
  void wrapContinuousPhotons( python::module& );

}
}

void wrapSection_1_460( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 460 >;
  using DelayedPhotonData = njoy::ENDFtk::section::Type< 1, 460 >::DelayedPhotonData;

  // wrap views created by this section

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT460",
    "MT460 - delayed photon data for particle induced or spontaneous fission"
  );

  // wrap components
  mf1::mt460::wrapDiscretePhotonMultiplicity( submodule );
  mf1::mt460::wrapContinuousPhotons( submodule );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF1 MT460 section - delayed photon data for particle induced or \n"
    "                    spontaneous fission"
  );

  // wrap the section
//  section
//  .def(
//
//    //! @todo pybind11 lambda move custom type workaround
//    python::init( [] ( double zaid, double awr,
//                       FissionEnergyReleaseData fissionq )
//                     { return Section( zaid, awr,
//                                       std::move( fissionq ) ); } ),
//    python::arg( "zaid" ), python::arg( "awr" ),
//    python::arg( "fissionq" ),
//    "Initialise the section\n\n"
//    "Arguments:\n"
//    "    self        the section\n"
//    "    zaid        the ZA value of the material\n"
//    "    awr         the atomic weight ratio\n"
//    "    fissionq    the fission energy release data"
//  )
//  .def_property_readonly(
//
//    "LFC",
//    &Section::LFC,
//    "The tabulated energy release flag"
//  )
//  .def_property_readonly(
//
//    "tabulated_energy_release",
//    &Section::tabulatedEnergyRelease,
//    "The tabulated energy release flag"
//  )
//  .def_property_readonly(
//
//    "NPLY",
//    &Section::NPLY,
//    "The polynomial expansion order"
//  )
//  .def_property_readonly(
//
//    "order",
//    &Section::order,
//    "The polynomial expansion order"
//  )
//  .def_property_readonly(
//
//    "NFC",
//    &Section::NFC,
//    "The number of tabulated energy release components"
//  )
//  .def_property_readonly(
//
//    "number_tabulated_components",
//    &Section::numberTabulatedComponents,
//    "The number of tabulated energy release components"
//  )
//  .def_property_readonly(
//
//    "energy_release",
//    &Section::energyRelease,
//    "The fission energy release data"
//  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
