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
  void wrapDiscretePhotonMultiplicity( python::module&, python::module& );
  void wrapContinuousPhotons( python::module&, python::module& );
  void wrapDiscretePhotons( python::module&, python::module& );

}
}

void wrapSection_1_460( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 460 >;
  using DelayedPhotonData = njoy::ENDFtk::section::Type< 1, 460 >::DelayedPhotonData;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT460",
    "MT460 - delayed photon data for particle induced or spontaneous fission"
  );

  // wrap components
  mf1::mt460::wrapDiscretePhotonMultiplicity( submodule, viewmodule );
  mf1::mt460::wrapContinuousPhotons( submodule, viewmodule );
  mf1::mt460::wrapDiscretePhotons( submodule, viewmodule );

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF1 MT460 section - delayed photon data for particle induced or \n"
    "                    spontaneous fission"
  );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr,
                       DelayedPhotonData photons )
                     { return Section( zaid, awr,
                                       std::move( photons ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "photons" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self       the section\n"
    "    zaid       the ZA value of the material\n"
    "    awr        the atomic weight ratio\n"
    "    photons    the fission energy release data"
  )
  .def_property_readonly(

    "LO",
    &Section::LO,
    "The representation type for the delayed photon data"
  )
  .def_property_readonly(

    "representation",
    &Section::representation,
    "The representation type for the delayed photon data"
  )
  .def_property_readonly(

    "NG",
    &Section::NG,
    "The number of discrete photons"
  )
  .def_property_readonly(

    "number_discrete_photons",
    &Section::numberDiscretePhotons,
    "The number of discrete photons"
  )
  .def_property_readonly(

    "delayed_photons",
    &Section::delayedPhotons,
    "The delayed photon data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
