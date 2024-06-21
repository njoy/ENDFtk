// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/RectangularMatrix.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapRectangularMatrix( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::RectangularMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "RectangularMatrix",
    "Covariance component - NI-type sub-subsection given as a rectangular matrix"
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
    "The procedure"
  )
  .def_property_readonly(

    "procedure",
    &Component::procedure,
    "The procedure"
  )
  .def_property_readonly(

    "NT",
    &Component::NT,
    "The number of values in this component"
  )
  .def_property_readonly(

    "number_values",
    &Component::numberValues,
    "The number of values in this component"
  )
  .def_property_readonly(

    "NER",
    &Component::NER,
    "The number of energies representing a row"
  )
  .def_property_readonly(

    "number_row_energies",
    &Component::numberRowEnergies,
    "The number of energies representing a row"
  )
  .def_property_readonly(

    "NEC",
    &Component::NEC,
    "The number of energies representing a column"
  )
  .def_property_readonly(

    "number_column_energies",
    &Component::numberColumnEnergies,
    "The number of energies representing a column"
  )
  .def_property_readonly(

    "row_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.rowEnergies(); },
    "The row energy values"
  )
  .def_property_readonly(

    "column_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.columnEnergies(); },
    "The column energy values"
  )
  .def_property_readonly(

    "values",
    [] ( const Component& self ) -> DoubleRange
       { return self.values(); },
    "The matrix values"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
