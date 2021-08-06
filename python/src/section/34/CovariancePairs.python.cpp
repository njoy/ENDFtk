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

void wrapCovariancePairs( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 34 >;
  using Component = Section::CovariancePairs;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CovariancePairs",
    "MF34 section - NI-type sub-subsection with {{E,F}} pairs"
  );

  // wrap the section
  component
  .def(

    python::init< int,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "lb" ),
    python::arg( "energies" ), python::arg( "fvalues" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    lb             covariance procedure\n"
    "    energies       energies\n"
    "    fvalues        F-values\n"
  )
  .def(

    python::init< int,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "lb" ),
    python::arg( "ek" ), python::arg( "fk" ),
    python::arg( "el" ), python::arg( "fl" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    lb             covariance procedure\n"
    "    ek             first array energies\n"
    "    fk             first array F-values\n"
    "    el             second array energies\n"
    "    fl             second array F-values\n"
  )
  .def_property_readonly(

    "LT",
    &Component::LT,
    "the number of pairs in the second array"
  )
  .def_property_readonly(

    "number_second_pairs",
    &Component::numberSecondPairs,
    "the number of pairs in the second array"
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

    "NP",
    &Component::NP,
    "the total number of pairs"
  )
  .def_property_readonly(

    "number_pairs",
    &Component::numberPairs,
    "the total number of pairs"
  )
  .def_property_readonly(

    "EK",
    [] ( const Component& self ) -> DoubleRange
       { return self.EK(); },
    "the energy values from the first array"
  )
  .def_property_readonly(

    "first_array_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.firstArrayEnergies(); },
    "the F values from the first array"
  )
  .def_property_readonly(

    "FK",
    [] ( const Component& self ) -> DoubleRange
       { return self.FK(); },
    "the F values from the first array"
  )
  .def_property_readonly(

    "first_array_fvalues",
    [] ( const Component& self ) -> DoubleRange
       { return self.firstArrayFValues(); },
    "the F values from the first array"
  )
  .def_property_readonly(

    "EL",
    [] ( const Component& self ) -> DoubleRange
       { return self.EL(); },
    "the energy values from the second array"
  )
  .def_property_readonly(

    "second_array_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.secondArrayEnergies(); },
    "the F values from the second array"
  )
  .def_property_readonly(

    "FL",
    [] ( const Component& self ) -> DoubleRange
       { return self.FL(); },
    "the F values from the second array"
  )
  .def_property_readonly(

    "second_array_fvalues",
    [] ( const Component& self ) -> DoubleRange
       { return self.secondArrayFValues(); },
    "the F values from the second array"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf33
