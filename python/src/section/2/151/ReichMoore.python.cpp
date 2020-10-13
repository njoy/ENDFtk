// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReichMoore( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::ReichMoore;
  using ReichMooreLValue = njoy::ENDFtk::section::Type< 2, 151 >::ReichMooreLValue;
  using ReichMooreLValueRange = RandomAccessAnyView< ReichMooreLValue >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ReichMooreLValue >(
      module,
      "any_view< ReichMooreLValue, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "ReichMoore",
    "MF2 MT151 section - Reich-Moore resonance parameters"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, bool, int,
                  std::vector< ReichMooreLValue >&& >(),
    python::arg( "spin" ), python::arg( "ap" ), python::arg( "lad" ),
    python::arg( "nlsc" ), python::arg( "lvalues" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    spin       the target spin\n"
    "    ap         the scattering radius\n"
    "    lad        the angular distributions flag\n"
    "    nlsc       the number of l values for convergence\n"
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

    "LAD",
    [] ( const Component& self ) { return self.LAD(); },
    "The angular distribution flag"
  )
  .def_property_readonly(

    "angular_distributions_flag",
    [] ( const Component& self ) { return self.angularDistributionsFlag(); },
    "The angular distribution flag"
  )
  .def_property_readonly(

    "NLSC",
    [] ( const Component& self ) { return self.NLSC(); },
    "The number of l values required for convergence"
  )
  .def_property_readonly(

    "number_l_values_for_convergence",
    [] ( const Component& self ) { return self.numberLValuesForConvergence(); },
    "The number of l values required for convergence"
  )
  .def_property_readonly(

    "l_values",
    [] ( const Component& self ) -> ReichMooreLValueRange
       { return self.lValues(); },
    "The l values and its resonance parameters"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
