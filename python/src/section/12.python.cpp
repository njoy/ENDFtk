// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/12.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components
void wrapTotalMultiplicity( python::module&, python::module& );
void wrapPartialMultiplicity( python::module&, python::module& );
void wrapMultiplicities( python::module&, python::module& );
void wrapTransitionProbabilities( python::module&, python::module& );

void wrapSection_12( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 12 >;
  using PhotonProduction = njoy::ENDFtk::section::Type< 12 >::PhotonProduction;

  // wrap components
  wrapTotalMultiplicity( module, viewmodule );
  wrapPartialMultiplicity( module, viewmodule );
  wrapMultiplicities( module, viewmodule );
  wrapTransitionProbabilities( module, viewmodule );

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF12 section - photon production multiplicities and transition\n"
    "               probability arrays"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, PhotonProduction&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "production" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self          the section\n"
    "    mt            the MT number for the section\n"
    "    zaid          the material ZAID value\n"
    "    awr           the atomic weight ratio\n"
    "    production    the photon production data"
  )
  .def_property_readonly(

    "LO",
    &Section::LO,
    "The data type for the photon production data"
  )
  .def_property_readonly(

    "representation",
    &Section::representation,
    "The data type for the photon production data"
  )
  .def_property_readonly(

    "photon_production",
    &Section::photonProduction,
    "The photon production data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
