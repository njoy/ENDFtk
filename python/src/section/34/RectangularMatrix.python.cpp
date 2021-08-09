/*
 * File intentionally copied from MF33
 */

// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/34.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf34 {

void wrapRectangularMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 34 >;
  using Component = Section::RectangularMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "RectangularMatrix",
    "MF34 section - NI-type sub-subsection given as a rectangular matrix"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "row_energies" ),
    python::arg( "column_energies" ), python::arg( "values" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    row_energies           row energies\n"
    "    column_energies        column energies\n"
    "    values                 matrix values\n"
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

    "NER",
    &Component::NER,
    "the number of energies representing a row"
  )
  .def_property_readonly(

    "number_row_energies",
    &Component::numberRowEnergies,
    "the number of energies representing a row"
  )
  .def_property_readonly(

    "NEC",
    &Component::NEC,
    "the number of energies representing a column"
  )
  .def_property_readonly(

    "number_column_energies",
    &Component::numberColumnEnergies,
    "the number of energies representing a column"
  )
  .def_property_readonly(

    "row_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.rowEnergies(); },
    "the row energy values"
  )
  .def_property_readonly(

    "column_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.columnEnergies(); },
    "the column energy values"
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

} // namespace mf33
