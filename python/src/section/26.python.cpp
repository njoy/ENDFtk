// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/26.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf26 {

  // declarations - components
  void wrapMultiplicity( python::module&, python::module& );

  namespace law1 {

    void wrapLegendreCoefficients( python::module&, python::module& );           // law=1
  }

  void wrapContinuumEnergyAngle( python::module&, python::module& );             // law=1

  namespace law2 {

    void wrapTabulatedDistribution( python::module&, python::module& );          // law=2

  }

  void wrapDiscreteTwoBodyScattering( python::module&, python::module& );        // law=2

  void wrapEnergyTransfer( python::module&, python::module& );                   // law=8
  void wrapReactionProduct( python::module&, python::module& );
}

void wrapSection_26( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 26 >;
  using ReactionProduct = Section::ReactionProduct;
  using ReactionProductRange = RandomAccessAnyView< ReactionProduct >;

  // wrap components

  // LAW = 1 - - - - - - - - - - - - - - - - - - - - - -

  // create the submodule for LAW=1
  python::module submodule = module.def_submodule(

    "LAW1",
    "LAW1 - continuum energy-angle data for secondary particles"
  );

  mf26::law1::wrapLegendreCoefficients( submodule, viewmodule );
  mf26::wrapContinuumEnergyAngle( module, viewmodule );

  // LAW = 2 - - - - - - - - - - - - - - - - - - - - - -

  // create the submodule for LAW=2
  submodule = module.def_submodule(

    "LAW2",
    "LAW2 - discrete two-body scattering data for secondary particles"
  );

  mf26::law2::wrapTabulatedDistribution( submodule, viewmodule );
  mf26::wrapDiscreteTwoBodyScattering( module, viewmodule );

  // LAW = 8 - - - - - - - - - - - - - - - - - - - - - -

  mf26::wrapEnergyTransfer( module, viewmodule );

  mf26::wrapMultiplicity( module, viewmodule );
  mf26::wrapReactionProduct( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ReactionProduct >(
      viewmodule,
      "any_view< mf26::ReactionProduct, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF26 section - secondary distributions for photo- and electro-atomic interactions"
  );

  // wrap the section
  section
  .def(

    python::init< int, int, double,
                  std::vector< ReactionProduct >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "products" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number\n"
    "    zaid        the ZA  identifier\n"
    "    awr         the atomic mass ratio\n"
    "    products    the reaction products (at least 1)"
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
