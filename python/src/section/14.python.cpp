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
  using AnisotropicPhotonDistribution = Section::AnisotropicPhotonDistribution;
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

    python::init< int, int, double, unsigned int >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "nk" ),
    "Initialise the section for all isotropic photons\n\n"
    "Arguments:\n"
    "    self   the section\n"
    "    mt     the MT number\n"
    "    zaid   the ZA  identifier\n"
    "    awr    the atomic mass ratio\n"
    "    nk     the total number of photons"
  )
  .def(

    python::init< int, int, double,
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
  .def(

    python::init< int, int, double,
                  std::vector< std::array< double, 2 > >&&,
                  std::vector< AnisotropicPhotonDistribution >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "isotropic" ), python::arg( "anisotropic" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self          the section\n"
    "    mt            the MT number\n"
    "    zaid          the ZA  identifier\n"
    "    awr           the atomic mass ratio\n"
    "    isotropic     the photon and level energy for each isotropic photon\n"
    "    anisotropic   the distribution data for the anisotropic photons"
  )
  .def(

    python::init< int, int, double,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< AnisotropicPhotonDistribution >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "energies" ), python::arg( "levels" ),
    python::arg( "anisotropic" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self          the section\n"
    "    mt            the MT number\n"
    "    zaid          the ZA  identifier\n"
    "    awr           the atomic mass ratio\n"
    "    energies      the photon energy for each isotropic photon\n"
    "    levels        the level energy for each isotropic photon\n"
    "    anisotropic   the distribution data for the anisotropic photons"
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

    "isotropic_distributions",
    &Section::isotropicDistributions,
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
