// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/35.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf35 {

void wrapSquareMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 35 >;
  using Component = Section::SquareMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "SquareMatrix",
    "MF35 section - energy block (subsection) given as a square matrix"
  );

  // wrap the section
  component
  .def(

    python::init< double, double,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "e1" ), python::arg("e2"),
    python::arg( "energies" ), python::arg( "values" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    e1             lowest incident energy\n"
    "    e2             highest incident energy\n"
    "    energies       energies\n"
    "    values         matrix values\n"
  )
  .def_property_readonly(

    "E1",
    &Component::E1,
    "the lowest incident energy"
  )
  .def_property_readonly(

    "lowest_energy",
    &Component::lowestEnergy,
    "the lowest incident energy"
  )
  .def_property_readonly(

    "E2",
    &Component::E2,
    "the highest incident energy"
  )
  .def_property_readonly(

    "highest_energy",
    &Component::highestEnergy,
    "the highest incident energy"
  )
  .def_property_readonly(

    "LB",
    &Component::LB,
    "the procedure"
  )
  .def_property_readonly(

    "procedure",
    &Component::procedure,
    "the procedure"
  )
  .def_property_readonly(

    "NT",
    &Component::NT,
    "the number of values in this component"
  )
  .def_property_readonly(

    "number_values",
    &Component::numberValues,
    "the number of values in this component"
  )
  .def_property_readonly(

    "NE",
    &Component::NE,
    "the number of energies in the array"
  )
  .def_property_readonly(

    "number_energies",
    &Component::numberEnergies,
    "the number of energies in the array"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "the energy values"
  )
  .def_property_readonly(

    "values",
    [] ( const Component& self ) -> DoubleRange
       { return self.values(); },
    "the matrix values"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf35
