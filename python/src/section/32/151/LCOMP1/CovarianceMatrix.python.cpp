// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {
namespace lcomp1 {

void wrapCovarianceMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::ShortRangeRMatrixLimitedBlock::CovarianceMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CovarianceMatrix",
    "MF32 MT151 section - covariance data for the R-matrix limited\n"
    "                     representation (LCOMP = 1)"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< double >&& >(),
    python::arg( "values" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    values      the values of the upper diagonal covaraince matrix"
  )
  .def_property_readonly(

    "NPARB",
    &Component::NPARB,
    "The order of the covariance matrix"
  )
  .def_property_readonly(

    "covariance_matrix_order",
    &Component::covarianceMatrixOrder,
    "The order of the covariance matrix"
  )
  .def_property_readonly(

    "NVS",
    &Component::NVS,
    "The number of values in the upper triangular covariance matrix"
  )
  .def_property_readonly(

    "number_values",
    &Component::numberValues,
    "The number of values in the upper triangular covariance matrix"
  )
  .def_property_readonly(

    "covariance_matrix",
    [] ( const Component& self ) -> DoubleRange
       { return self.covarianceMatrix(); },
    "The upper triangular covariance matrix"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace lcomp1
} // namespace mf32
