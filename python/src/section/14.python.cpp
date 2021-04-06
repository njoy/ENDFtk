// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/14.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components
namespace mf14 {

  void wrapIsotropicDiscretePhoton( python::module&, python::module& );
  void wrapLegendreCoefficients( python::module&, python::module& );
  void wrapTabulatedDistribution( python::module&, python::module& );
  void wrapLegendreDistributions( python::module&, python::module& );
  void wrapTabulatedDistributions( python::module&, python::module& );
}

void wrapSection_14( python::module& module, python::module& viewmodule ) {

  // type aliases

  // wrap components
  mf14::wrapIsotropicDiscretePhoton( module, viewmodule );
  mf14::wrapLegendreCoefficients( module, viewmodule );
  mf14::wrapTabulatedDistribution( module, viewmodule );
  mf14::wrapLegendreDistributions( module, viewmodule );
  mf14::wrapTabulatedDistributions( module, viewmodule );

  // wrap views created by this section
  using Section = njoy::ENDFtk::section::Type< 14 >;
  using PhotonDistribution = Section::PhotonDistribution;
  using PhotonDistributionRange = RandomAccessAnyView< PhotonDistribution >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< PhotonDistribution >(
      viewmodule,
      "any_view< PhotonDistribution, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF14 section - angular distributions of secondary photons"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    "Initialise the section for all isotropic photons\n\n"
    "Arguments:\n"
    "    self   the section\n"
    "    mt     the MT number\n"
    "    zaid   the ZA  identifier\n"
    "    awr    the atomic mass ratio"
  )
  .def(

    python::init< int, double, double,
                  std::vector< PhotonDistribution >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "photons" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self      the section\n"
    "    mt        the MT number\n"
    "    zaid      the ZA  identifier\n"
    "    awr       the atomic mass ratio\n"
    "    photons   the photon distribution data"
  )
  .def_property_readonly(

    "NI",
    &Section::NI,
    "The number of photons with an isotropic angular distribution"
  )
  .def_property_readonly(

    "number_isotropic_photons",
    &Section::numberIsotropicPhotons,
    "The number of photons with an isotropic angular distribution"
  )
  .def_property_readonly(

    "NK",
    &Section::NK,
    "The number of photons (discrete and continuum) with angular distributions"
  )
  .def_property_readonly(

    "number_photons",
    &Section::numberPhotons,
    "The number of photons (discrete and continuum) with angular distributions"
  )
  .def_property_readonly(

    "LTT",
    &Section::LTT,
    "The distribution law"
  )
  .def_property_readonly(

    "LAW",
    &Section::LAW,
    "The distribution law"
  )
  .def_property_readonly(

    "LI",
    &Section::LI,
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "isotropic_angular_distributions",
    &Section::isotropicAngularDistributions,
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "photon_angular_distributions",
    &Section::photonAngularDistributions,
    "The secondary photons with their angular distribution"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
