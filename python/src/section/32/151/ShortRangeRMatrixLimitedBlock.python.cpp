// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapShortRangeRMatrixLimitedBlock( python::module& module,
                                        python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::ShortRangeRMatrixLimitedBlock;
  using ResonanceParameters = Component::ResonanceParameters;
  using CovarianceMatrix = Component::CovarianceMatrix;
  using ResonanceParametersRange = RandomAccessAnyView< ResonanceParameters >;

  // wrap views created by this section
  wrapRandomAccessAnyViewOf< ResonanceParameters >(
      viewmodule,
      "any_view< mf32::ResonanceParameters, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "ShortRangeRMatrixLimitedBlock",
    "MF32 MT151 section - resonance parameters and variance/covariance block for\n"
    "                     in the R-matrix limited representation (LCOMP = 1)"
  );

  // wrap the section
  component
  .def(

    python::init( [] ( std::vector< ResonanceParameters >&& parameters,
                       CovarianceMatrix covariances )
                     { return Component( std::move( parameters ),
                                         std::move( covariances ) ); } ),
    python::arg( "parameters" ), python::arg( "covariances" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    parameters     the resonance parameters\n"
    "    covariances    the covariance matrix"
  )
  .def_property_readonly(

    "NJSX",
    [] ( const Component& self ) { return self.NJSX(); },
    "The number of spin groups for which resonance parameters are given"
  )
  .def_property_readonly(

    "number_spin_groups",
    [] ( const Component& self ) { return self.numberSpinGroups(); },
    "The number of spin groups for which resonance parameters are given"
  )
  .def_property_readonly(

    "resonance_parameters",
    [] ( const Component& self ) -> ResonanceParametersRange
       { return self.resonanceParameters(); },
    "The resonance parameters"
  )
  .def_property_readonly(

    "covariance_matrix",
    &Component::covarianceMatrix,
    "The covariance matrix"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
