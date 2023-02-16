// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf2 {

void wrapMultiLevelBreitWigner( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::MultiLevelBreitWigner;
  using BreitWignerLValue = Section::BreitWignerLValue;
  using BreitWignerLValueRange = RandomAccessAnyView< BreitWignerLValue >;

  // no need to wrap BreitWignerLValueRange since SLBW wrapped it already

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "MultiLevelBreitWigner",
    "MF2 MT151 section - Multi-level Breit-Wigner resonance parameters"
  );

  // wrap the section
  component
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

} // namespace mf2
