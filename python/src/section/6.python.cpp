// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components
void wrapMultiplicity( python::module& );
void wrapDefinedElsewhere( python::module& );             // law<0
void wrapUnknownDistribution( python::module& );          // law=0
void wrapIsotropicDiscreteEmission( python::module& );    // law=3
void wrapDiscreteTwoBodyRecoils( python::module& );       // law=4
void wrapNBodyPhaseSpace( python::module& );              // law=6
void wrapEnergyDistribution( python::module& );           // law=7
void wrapReactionProduct( python::module& );

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
  wrapMultiplicity( module );
  wrapDefinedElsewhere( module );
  wrapUnknownDistribution( module );
  wrapIsotropicDiscreteEmission( module );
  wrapDiscreteTwoBodyRecoils( module );
  wrapNBodyPhaseSpace( module );
  wrapEnergyDistribution( module );
  wrapReactionProduct( module );

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
