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
  void wrapMultiplicity( python::module&, python::module& );
  void wrapDefinedElsewhere( python::module&, python::module& );                 // law<0
  void wrapUnknownDistribution( python::module&, python::module& );              // law=0

  namespace law1 {

    void wrapLegendreCoefficients( python::module&, python::module& );           // law=1
    void wrapTabulatedDistribution( python::module&, python::module& );          // law=1
    void wrapKalbachMann( python::module&, python::module& );                    // law=1
    void wrapThermalScatteringData( python::module&, python::module& );          // law=1
  }

  void wrapContinuumEnergyAngle( python::module&, python::module& );             // law=1

  namespace law2 {

    void wrapLegendreCoefficients( python::module&, python::module& );           // law=2
    void wrapTabulatedDistribution( python::module&, python::module& );          // law=2

  }

  void wrapDiscreteTwoBodyScattering( python::module&, python::module& );        // law=2
  void wrapIsotropicDiscreteEmission( python::module&, python::module& );        // law=3
  void wrapDiscreteTwoBodyRecoils( python::module&, python::module& );           // law=4

  namespace law5 {

    void wrapLegendreCoefficients( python::module&, python::module& );           // law=5
    void wrapNuclearAmplitudeExpansion( python::module&, python::module& );      // law=5
    void wrapNuclearPlusInterference( python::module&, python::module& );        // law=5
  }

  void wrapChargedParticleElasticScattering( python::module&, python::module& ); // law=5
  void wrapNBodyPhaseSpace( python::module&, python::module& );                  // law=6

  namespace law7 {

    void wrapEnergyDistribution( python::module&, python::module& );             // law=7
    void wrapAngularDistribution( python::module&, python::module& );            // law=7

  }

  void wrapLaboratoryAngleEnergy( python::module&, python::module& );            // law=7
  void wrapReactionProduct( python::module&, python::module& );
}

void wrapSection_6( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using ReactionProduct = Section::ReactionProduct;
  using ReactionProductRange = RandomAccessAnyView< ReactionProduct >;

  // wrap components

  // LAW < 0 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapDefinedElsewhere( module, viewmodule );

  // LAW = 0 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapUnknownDistribution( module, viewmodule );

  // LAW = 1 - - - - - - - - - - - - - - - - - - - - - -

  // create the submodule for LAW=1
  python::module submodule = module.def_submodule(

    "LAW1",
    "LAW1 - continuum energy-angle data for secondary particles"
  );

  mf6::law1::wrapLegendreCoefficients( submodule, viewmodule );
  mf6::law1::wrapTabulatedDistribution( submodule, viewmodule );
  mf6::law1::wrapKalbachMann( submodule, viewmodule );
  mf6::law1::wrapThermalScatteringData( submodule, viewmodule );
  mf6::wrapContinuumEnergyAngle( module, viewmodule );

  // LAW = 2 - - - - - - - - - - - - - - - - - - - - - -

  // create the submodule for LAW=2
  submodule = module.def_submodule(

    "LAW2",
    "LAW2 - discrete two-body scattering data for secondary particles"
  );

  mf6::law2::wrapLegendreCoefficients( submodule, viewmodule );
  mf6::law2::wrapTabulatedDistribution( submodule, viewmodule );
  mf6::wrapDiscreteTwoBodyScattering( module, viewmodule );

  // LAW = 3 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapIsotropicDiscreteEmission( module, viewmodule );

  // LAW = 4 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapDiscreteTwoBodyRecoils( module, viewmodule );

  // LAW = 5 - - - - - - - - - - - - - - - - - - - - - -

  // create the submodule for LAW=5
  submodule = module.def_submodule(

    "LAW5",
    "LAW5 - charged particle elastic scattering"
  );

  mf6::law5::wrapLegendreCoefficients( submodule, viewmodule );
  mf6::law5::wrapNuclearAmplitudeExpansion( submodule, viewmodule );
  mf6::law5::wrapNuclearPlusInterference( submodule, viewmodule );
  mf6::wrapChargedParticleElasticScattering( module, viewmodule );

  // LAW = 6 - - - - - - - - - - - - - - - - - - - - - -

  mf6::wrapNBodyPhaseSpace( module, viewmodule );           // LAW=6

  // LAW = 7 - - - - - - - - - - - - - - - - - - - - - -

  // create the submodule for LAW=7
  submodule = module.def_submodule(

    "LAW7",
    "LAW7 - distributions are given in the E,mu,E' ordering"
  );

  mf6::law7::wrapEnergyDistribution( submodule, viewmodule );
  mf6::law7::wrapAngularDistribution( submodule, viewmodule );
  mf6::wrapLaboratoryAngleEnergy( module, viewmodule );

  mf6::wrapMultiplicity( module, viewmodule );
  mf6::wrapReactionProduct( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ReactionProduct >(
      viewmodule,
      "any_view< ReactionProduct, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF6 section - product energy-angle distributions"
  );

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
  .def(

    "has_reaction_product",
    &Section::hasReactionProduct,
    python::arg( "zap" ),
    "Return whether or not the reaction product is present\n\n"
    "Arguments:\n"
    "    self   the section\n"
    "    zap    the reaction product to retrieve"
  )
  .def(

    "reaction_product",
    &Section::reactionProduct,
    python::arg( "zap" ),
    "Return the requested reaction product\n\n"
    "Arguments:\n"
    "    self   the section\n"
    "    zap    the reaction product to retrieve"
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
