// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/33.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf33 {

void wrapDerivedRedundant( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 33 >;
  using Component = Section::DerivedRedundant;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "DerivedRedundant",
    "MF33 section - NC-type sub-subsection for derived redundant quantities"
  );

  // wrap the section
  component
  .def(

    python::init< double, double,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "e1" ), python::arg( "e2" ),
    python::arg( "coefficients" ), python::arg( "reactions" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    e1             the lower energy\n"
    "    e2             the upper energy\n"
    "    coefficients   the coefficients for linear combination\n"
    "    reactions      the reaction MTs\n"
  )
  .def_property_readonly(

    "LTY",
    [] ( const Component& self ) { return self.LTY(); },
    "the procedure"
  )
  .def_property_readonly(

    "procedure",
    &Component::procedure,
    "the procedure"
  )
  .def_property_readonly(

    "E1",
    &Component::E1,
    "the lower energy bound"
  )
  .def_property_readonly(

    "lower_energy",
    &Component::lowerEnergy,
    "the lower energy bound"
  )
  .def_property_readonly(

    "E2",
    &Component::E2,
    "the upper energy bound"
  )
  .def_property_readonly(

    "upper_energy",
    &Component::upperEnergy,
    "the upper energy bound"
  )
  .def_property_readonly(

    "NCI",
    &Component::NCI,
    "the number of reactions"
  )
  .def_property_readonly(

    "number_reactions",
    &Component::numberReactions,
    "the number of reactions"
  )
  .def_property_readonly(

    "CI",
    [] ( const Component& self ) -> DoubleRange
       { return self.CI(); },
    "the coefficients"
  )
  .def_property_readonly(

    "coefficients",
    [] ( const Component& self ) -> DoubleRange
       { return self.coefficients(); },
    "the coefficients"
  )
  .def_property_readonly(

    "XMTI",
    [] ( const Component& self ) -> DoubleRange
       { return self.XMTI(); },
    "the reaction MTs"
  )
  .def_property_readonly(

    "reactions",
    [] ( const Component& self ) -> DoubleRange
       { return self.reactions(); },
    "the reaction MTs"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf33
