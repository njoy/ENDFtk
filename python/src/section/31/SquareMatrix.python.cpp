// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/31.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf31 {

void wrapSquareMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 31 >;
  using Component = Section::SquareMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "SquareMatrix",
    "MF31 section - NI-type sub-subsection given as a square matrix"
  );

  // wrap the section
  component
  .def(

    python::init< int,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "ls" ),
    python::arg( "energies" ), python::arg( "values" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    ls             symmetry flag (0=asymmetric, 1=symmetric)\n"
    "    energies       energies\n"
    "    values         matrix values\n"
  )
  .def_property_readonly(

    "LS",
    &Component::LS,
    "the symmetry flag"
  )
  .def_property_readonly(

    "symmetry_flag",
    &Component::symmetryFlag,
    "the symmetry flag"
  )
  .def_property_readonly(

    "is_symmetric",
    &Component::isSymmetric,
    "the symmetry flag as a boolean"
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

} // namespace mf31
