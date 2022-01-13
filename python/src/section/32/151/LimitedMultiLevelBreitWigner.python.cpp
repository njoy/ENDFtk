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

void wrapLimitedMultiLevelBreitWigner( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::LimitedMultiLevelBreitWigner;
  using BreitWignerLValue = Section::BreitWignerLValue;
  using BreitWignerLValueRange = RandomAccessAnyView< BreitWignerLValue >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "LimitedMultiLevelBreitWigner",
    "MF32 MT151 section - Single level Breit-Wigner resonance parameters and\n"
    "                     covariances using LCOMP=0"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, double, std::vector< BreitWignerLValue >&& >(),
    python::arg( "spin" ), python::arg( "ap" ), python::arg( "dap" ), python::arg( "lvalues" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    spin       the target spin\n"
    "    ap         the scattering radius\n"
    "    ap         the scattering radius uncertainty\n"
    "    lvalues    l values and the resonance parameters"
  )
  .def(

    python::init< double, double, std::vector< BreitWignerLValue >&& >(),
    python::arg( "spin" ), python::arg( "ap" ), python::arg( "lvalues" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    spin       the target spin\n"
    "    ap         the scattering radius\n"
    "    lvalues    l values and the resonance parameters"
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

    "LCOMP",
    [] ( const Component& self ) { return self.LCOMP(); },
    "The covariance representation type"
  )
  .def_property_readonly(

    "covariance_representation",
    [] ( const Component& self ) { return self.covarianceRepresentation(); },
    "The covariance representation type"
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
    "The scattering radius"
  )
  .def_property_readonly(

    "scattering_radius",
    [] ( const Component& self ) { return self.scatteringRadius(); },
    "The scattering radius"
  )
  .def_property_readonly(

    "DAP",
    [] ( const Component& self ) { return self.DAP(); },
    "The scattering radius uncertainty"
  )
  .def_property_readonly(

    "scattering_radius_uncertainty",
    [] ( const Component& self ) { return self.scatteringRadiusUncertainty(); },
    "The scattering radius uncertainty"
  )
  .def_property_readonly(

    "ISR",
    [] ( const Component& self ) { return self.ISR(); },
    "The scattering radius uncertainty flag"
  )
  .def_property_readonly(

    "scattering_radius_uncertainty_flag",
    [] ( const Component& self ) { return self.scatteringRadiusUncertaintyFlag(); },
    "The scattering radius uncertainty flag"
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
    [] ( const Component& self ) -> BreitWignerLValueRange
       { return self.lValues(); },
    "The l values and its resonance parameters"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
