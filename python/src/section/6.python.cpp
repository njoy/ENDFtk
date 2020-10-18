// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {

  // declarations - components
  void wrapMultiplicity( python::module& );
  void wrapDefinedElsewhere( python::module& );                 // law<0
  void wrapUnknownDistribution( python::module& );              // law=0

  namespace law1 {

    void wrapLegendreCoefficients( python::module& );           // law=1
    void wrapTabulatedDistribution( python::module& );          // law=1
  }

  namespace law2 {

    void wrapLegendreCoefficients( python::module& );           // law=2
    void wrapTabulatedDistribution( python::module& );          // law=2

  }

  void wrapDiscreteTwoBodyScattering( python::module& );        // law=2
  void wrapIsotropicDiscreteEmission( python::module& );        // law=3
  void wrapDiscreteTwoBodyRecoils( python::module& );           // law=4

  namespace law5 {

    void wrapLegendreCoefficients( python::module& );           // law=5
    void wrapNuclearAmplitudeExpansion( python::module& );      // law=5
    void wrapNuclearPlusInterference( python::module& );        // law=5
  }

  void wrapChargedParticleElasticScattering( python::module& ); // law=5
  void wrapNBodyPhaseSpace( python::module& );                  // law=6

  namespace law7 {

    void wrapEnergyDistribution( python::module& );             // law=7
    void wrapAngularDistribution( python::module& );            // law=7

  }

  void wrapLaboratoryAngleEnergy( python::module& );            // law=7
  void wrapReactionProduct( python::module& );
}

void wrapSection_6( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using ReactionProduct = njoy::ENDFtk::section::Type< 6 >::ReactionProduct;
  using ReactionProductRange = RandomAccessAnyView< ReactionProduct >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ReactionProduct >(
      module,
      "any_view< ReactionProduct, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF6 section - product energy-angle distributions"
  );

  // wrap components
  mf6::wrapMultiplicity( module );
  mf6::wrapReactionProduct( module );

  // LAW < 0 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapDefinedElsewhere( module );

  // LAW = 0 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapUnknownDistribution( module );

  // LAW = 1 - - - - - - - - - - - - - - - - - - - - - -

  // mf6::wrapContinuumEnergyAngle( module );

  // create the submodule for LAW=1
  python::module submodule = module.def_submodule(

    "LAW1",
    "LAW1 - continuum energy-angle data for secondary particles"
  );

  mf6::law1::wrapLegendreCoefficients( submodule );
  mf6::law1::wrapTabulatedDistribution( submodule );

  // LAW = 2 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapDiscreteTwoBodyScattering( module );

  // create the submodule for LAW=2
  submodule = module.def_submodule(

    "LAW2",
    "LAW2 - discrete two-body scattering data for secondary particles"
  );

  mf6::law2::wrapLegendreCoefficients( submodule );
  mf6::law2::wrapTabulatedDistribution( submodule );

  // LAW = 3 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapIsotropicDiscreteEmission( module );

  // LAW = 4 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapDiscreteTwoBodyRecoils( module );

  // LAW = 5 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapChargedParticleElasticScattering( module );

  // create the submodule for LAW=5
  submodule = module.def_submodule(

    "LAW5",
    "LAW5 - charged particle elastic scattering"
  );

  mf6::law5::wrapLegendreCoefficients( submodule );
  mf6::law5::wrapNuclearAmplitudeExpansion( submodule );
  mf6::law5::wrapNuclearPlusInterference( submodule );

  // LAW = 6 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapNBodyPhaseSpace( module );           // LAW=6

  // LAW = 7 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapLaboratoryAngleEnergy( module );

  // create the submodule for LAW=7
  submodule = module.def_submodule(

    "LAW7",
    "LAW7 - distributions are given in the E,mu,E' ordering"
  );

  mf6::law7::wrapEnergyDistribution( submodule );
  mf6::law7::wrapAngularDistribution( submodule );

  // wrap the section
  section
  .def(

    python::init< int, double, double, int, int,
                  std::vector< ReactionProduct >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "jp" ), python::arg( "lct" ), python::arg( "products" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number\n"
    "    zaid        the ZA  identifier\n"
    "    awr         the atomic mass ratio\n"
    "    jp          the particle spectrum type flag\n"
    "    lct         the reference frame\n"
    "    products    the reaction products (at least 1)"
  )
  .def_property_readonly(

    "JP",
    &Section::JP,
    "The particle spectrum type flag"
  )
  .def_property_readonly(

    "average_multiple_particles_flag",
    &Section::averageMultipleParticlesFlag,
    "The particle spectrum type flag"
  )
  .def_property_readonly(

    "LCT",
    &Section::LCT,
    "The reference frame (LAB or CM)"
  )
  .def_property_readonly(

    "reference_frame",
    &Section::referenceFrame,
    "The reference frame (LAB or CM)"
  )
  .def_property_readonly(

    "NK",
    &Section::NK,
    "The number of reaction products"
  )
  .def_property_readonly(

    "number_reaction_products",
    &Section::numberReactionProducts,
    "The number of reaction products"
  )
  .def_property_readonly(

    "reaction_products",
    [] ( const Section& self ) -> ReactionProductRange
       { return self.reactionProducts(); },
    "The reaction products defined in this section"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
