// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/CovariancePairs.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapCovariancePairs( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::CovariancePairs;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CovariancePairs",
    "Covariance component - NI-type sub-subsection with {{E,F}} pairs"
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
    "The number of pairs in the second array"
  )
  .def_property_readonly(

    "number_second_pairs",
    &Component::numberSecondPairs,
    "The number of pairs in the second array"
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

    "NP",
    &Component::NP,
    "The total number of pairs"
  )
  .def_property_readonly(

    "number_pairs",
    &Component::numberPairs,
    "The total number of pairs"
  )
  .def_property_readonly(

    "EK",
    [] ( const Component& self ) -> DoubleRange
       { return self.EK(); },
    "The energy values from the first array"
  )
  .def_property_readonly(

    "first_array_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.firstArrayEnergies(); },
    "The F values from the first array"
  )
  .def_property_readonly(

    "FK",
    [] ( const Component& self ) -> DoubleRange
       { return self.FK(); },
    "The F values from the first array"
  )
  .def_property_readonly(

    "first_array_fvalues",
    [] ( const Component& self ) -> DoubleRange
       { return self.firstArrayFValues(); },
    "The F values from the first array"
  )
  .def_property_readonly(

    "EL",
    [] ( const Component& self ) -> DoubleRange
       { return self.EL(); },
    "The energy values from the second array"
  )
  .def_property_readonly(

    "second_array_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.secondArrayEnergies(); },
    "The F values from the second array"
  )
  .def_property_readonly(

    "FL",
    [] ( const Component& self ) -> DoubleRange
       { return self.FL(); },
    "The F values from the second array"
  )
  .def_property_readonly(

    "second_array_fvalues",
    [] ( const Component& self ) -> DoubleRange
       { return self.secondArrayFValues(); },
    "The F values from the second array"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
