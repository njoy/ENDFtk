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
  void wrapTabulatedComponents( python::module& );

}
}

void wrapSection_1_458( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 458 >;
  using FissionEnergyReleaseData = njoy::ENDFtk::section::Type< 1, 458 >::FissionEnergyReleaseData;

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
  mf1::mt458::wrapTabulatedComponents( submodule );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF1 MT458 section - fission energy release components"
  );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr,
                       FissionEnergyReleaseData fissionq )
                     { return Section( zaid, awr,
                                       std::move( fissionq ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "fissionq" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    zaid        the ZA value of the material\n"
    "    awr         the atomic weight ratio\n"
    "    fissionq    the fission energy release data"
  )
  .def_property_readonly(

    "LFC",
    &Section::LFC,
    "The tabulated energy release flag"
  )
  .def_property_readonly(

    "tabulated_energy_release",
    &Section::tabulatedEnergyRelease,
    "The tabulated energy release flag"
  )
  .def_property_readonly(

    "NPLY",
    &Section::NPLY,
    "The polynomial expansion order"
  )
  .def_property_readonly(

    "order",
    &Section::order,
    "The polynomial expansion order"
  )
  .def_property_readonly(

    "NFC",
    &Section::NFC,
    "The number of tabulated energy release components"
  )
  .def_property_readonly(

    "number_tabulated_components",
    &Section::numberTabulatedComponents,
    "The number of tabulated energy release components"
  )
  .def_property_readonly(

    "energy_release",
    &Section::energyRelease,
    "The fission energy release data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
