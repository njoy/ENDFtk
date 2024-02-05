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

void wrapMultiplicity( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 26 >;
  using Component = Section::Multiplicity;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "Multiplicity",
    "MF26 section - multiplicity for a photon or electron"
  );

  // wrap the section
  component
  .def(

    python::init< int, double, int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "zap" ), python::arg( "awi" ), python::arg( "law" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "multiplicities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component\n"
    "    zap               the ZAID value for the reaction product\n"
    "    awi               the atomic weight ratio for the projectile\n"
    "    law               the distribution type\n"
    "    boundaries        the interpolation range boundaries\n"
    "    interpolants      the interpolation types for each range\n"
    "    energies          the x values\n"
    "    multiplicities    the function values"
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

    "AWI",
    &Component::AWI,
    "The atomic weight ratio of the projectile"
  )
  .def_property_readonly(

    "projectile_weight_ratio",
    &Component::projectileWeightRatio,
    "The atomic weight ratio of the projectile"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution type (the LAW flag)"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "Y",
    [] ( const Component& self ) -> DoubleRange
       { return self.Y(); },
    "The multiplicity values"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Component& self ) -> DoubleRange
       { return self.multiplicities(); },
    "The multiplicity values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf26
