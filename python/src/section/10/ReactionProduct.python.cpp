// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/10.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf10 {

void wrapReactionProduct( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 10 >;
  using Component = Section::ReactionProduct;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ReactionProduct",
    "MF10 section - production cross sections for a specific excited state of "
    "               the reaction product"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int, int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "qm" ), python::arg( "qi" ),
    python::arg( "izap" ), python::arg( "lfs" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    qm             the mass difference Q value\n"
    "    qi             the reaction Q value\n"
    "    izap           the za identifier of the product\n"
    "    lfs            the excited level number\n"
    "    boundaries     the interpolation range boundaries\n"
    "    interpolants   the interpolation types for each range\n"
    "    energies       the energy values\n"
    "    xs             the cross section values"
  )
  .def(

    python::init< double, double, int, int,
                  std::vector< double >&&, std::vector< double >&&,
                  long >(),
    python::arg( "qm" ), python::arg( "qi" ),
    python::arg( "izap" ), python::arg( "lfs" ),
    python::arg( "energies" ), python::arg( "xs" ),
    python::arg( "interpolant" ) = 2,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    qm            the mass difference Q value\n"
    "    qi            the reaction Q value\n"
    "    izap          the za identifier of the product\n"
    "    lfs           the excited level number\n"
    "    energies      the energy values\n"
    "    xs            the cross section values\n"
    "    interpolant   the interpolation type (default 2 - linlin)"
  )
  .def_property_readonly(

    "QM",
    &Component::QM,
    "The mass difference Q value"
  )
  .def_property_readonly(

    "mass_difference_qvalue",
    &Component::massDifferenceQValue,
    "The mass difference Q value"
  )
  .def_property_readonly(

    "QI",
    &Component::QI,
    "The reaction Q value"
  )
  .def_property_readonly(

    "reaction_qvalue",
    &Component::reactionQValue,
    "The mass difference Q value"
  )
  .def_property_readonly(

    "IZAP",
    &Component::IZAP,
    "The ZA identifier of the reaction product"
  )
  .def_property_readonly(

    "product_identifier",
    &Component::productIdentifier,
    "The ZA identifier of the reaction product"
  )
  .def_property_readonly(

    "LFS",
    &Component::LFS,
    "The excited level number of the product"
  )
  .def_property_readonly(

    "excited_level",
    &Component::excitedLevel,
    "The product modifier flag"
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

    "XS",
    [] ( const Component& self ) -> DoubleRange
       { return self.XS(); },
    "The cross section values"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Component& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf6
