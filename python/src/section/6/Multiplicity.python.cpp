// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {

void wrapMultiplicity( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::Multiplicity;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "Multiplicity",
    "MF6 section - reaction product multiplicity"
  );

  // wrap the section
  component
  .def(

    python::init< int, double, int, int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "zap" ), python::arg( "awp" ),
    python::arg( "lip" ), python::arg( "law" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "multiplicities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component\n"
    "    zap               the ZAID value for the reaction product\n"
    "    awp               the atomic weight ratio for the reaction\n"
    "                      product\n"
    "    lip               the product modifier flag\n"
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

} // namespace mf6
