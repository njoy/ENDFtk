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

void wrapUnresolvedRelativeCovariances( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::UnresolvedRelativeCovariances;
  using CovarianceMatrix = Section::UnresolvedRelativeCovariances::CovarianceMatrix;
  using LValue = Section::UnresolvedRelativeCovariances::LValue;
  using LValueRange = RandomAccessAnyView< LValue >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< LValue >(
      viewmodule,
      "any_view< UnresolvedRelativeCovariancesLValueRange, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedRelativeCovariances",
    "MF32 MT151 section - unresolved resonance relative covariance data"
  );

  // wrap the section
  component
  .def(

    python::init( [] ( double spin, double ap, std::vector< LValue > lvalues,
                       CovarianceMatrix matrix )
                     { return Component( spin, ap,
                                         std::move( lvalues ),
                                         std::move( matrix ) ); } ),
    python::arg( "spin" ), python::arg( "ap" ),
    python::arg( "lvalues" ), python::arg( "matrix" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    spi        the target spin value\n"
    "    ap         the scattering radius\n"
    "    lvalues    the l values and the resonance parameters\n"
    "    matrix     the covariance matrix"
  )
  .def_property_readonly(

    "LRU",
    [] ( const Component& self ) { return self.LRU(); },
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "type",
    [] ( const Component& self ) { return self.type(); },
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "LRF",
    [] ( const Component& self ) { return self.LRF(); },
    "The resonance representation"
  )
  .def_property_readonly(

    "representation",
    [] ( const Component& self ) { return self.representation(); },
    "The resonance representation"
  )
  .def_property_readonly(

    "LFW",
    [] ( const Component& self ) { return self.LFW(); },
    "The average fission flag"
  )
  .def_property_readonly(

    "average_fission_width_flag",
    [] ( const Component& self ) { return self.averageFissionWidthFlag(); },
    "The average fission flag"
  )
  .def_property_readonly(

    "SPI",
    [] ( const Component& self ) { return self.SPI(); },
    "The target spin"
  )
  .def_property_readonly(

    "spin",
    [] ( const Component& self ) { return self.spin(); },
    "The scattering radius"
  )
  .def_property_readonly(

    "AP",
    [] ( const Component& self ) { return self.AP(); },
    "The target spin"
  )
  .def_property_readonly(

    "scattering_radius",
    [] ( const Component& self ) { return self.scatteringRadius(); },
    "The target spin"
  )
  .def_property_readonly(

    "NLS",
    [] ( const Component& self ) { return self.NLS(); },
    "The number of l values for which resonance parameters are given"
  )
  .def_property_readonly(

    "number_l_values",
    [] ( const Component& self ) { return self.numberLValues(); },
    "The number of l values for which resonance parameters are given"
  )
  .def_property_readonly(

    "l_values",
    [] ( const Component& self ) -> LValueRange
       { return self.lValues(); },
    "The l values and its resonance parameters"
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
