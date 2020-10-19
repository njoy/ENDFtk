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

void wrapReactionProduct( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 6 >::ReactionProduct;
  using Multiplicity = njoy::ENDFtk::section::Type< 6 >::Multiplicity;
  using Distribution = njoy::ENDFtk::section::Type< 6 >::Distribution;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ReactionProduct",
    "MF6 section - a reaction product with multiplicity and distribution data"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( Multiplicity multiplicity,
                       Distribution&& distribution )
                     { return Component( std::move( multiplicity ),
                                         std::move( distribution ) ); } ),
    python::arg( "multiplicity" ), python::arg( "distribution" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    multiplicity    the multiplicity\n"
    "    distribution    the distribution"
  )
  .def_property_readonly(

    "ZAP",
    &Component::ZAP,
    "The ZA identifier of the reaction product"
  )
  .def_property_readonly(

    "product_identifier",
    &Component::productIdentifier,
    "The ZA identifier of the reaction product"
  )
  .def_property_readonly(

    "AWP",
    &Component::AWP,
    "The atomic weight ratio of the reaction product"
  )
  .def_property_readonly(

    "product_weight_ratio",
    &Component::productWeightRatio,
    "The atomic weight ratio of the reaction product"
  )
  .def_property_readonly(

    "LIP",
    &Component::LIP,
    "The product modifier flag"
  )
  .def_property_readonly(

    "product_modifier_flag",
    &Component::productModifierFlag,
    "The product modifier flag"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution type (the LAW flag)"
  )
  .def_property_readonly(

    "multiplicity",
    &Component::multiplicity,
    "The multiplicity"
  )
  .def_property_readonly(

    "distribution",
    &Component::distribution,
    "The distribution"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf6
