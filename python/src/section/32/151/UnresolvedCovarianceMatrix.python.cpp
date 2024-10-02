// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapUnresolvedCovarianceMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::UnresolvedRelativeCovariances::CovarianceMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedCovarianceMatrix",
    "MF32 MT151 section - covariance data for the unresolved resonances"
  );

  // wrap the section
  component
  .def(

    python::init< unsigned int, std::vector< double >&& >(),
    python::arg( "mpar" ), python::arg( "values" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    mpar        the number of average parameters with covariance data\n"
    "    values      the values of the upper diagonal covaraince matrix"
  )
  .def_property_readonly(

    "MPAR",
    &Component::MPAR,
    "The number of average parameters for which covariance data is given"
  )
  .def_property_readonly(

    "number_average_parameters",
    &Component::numberAverageParameters,
    "The number of average parameters for which covariance data is given"
  )
  .def_property_readonly(

    "NPAR",
    &Component::NPAR,
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

} // namespace mf32
