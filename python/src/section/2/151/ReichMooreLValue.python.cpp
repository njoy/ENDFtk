// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReichMooreLValue( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::ReichMooreLValue;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ReichMooreLValue",
    "MF2 MT151 section - resonance parameters for a given l value in the\n"
    "                    Reich-Moore representation"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "awri" ), python::arg( "apl" ), python::arg( "l" ),
    python::arg( "energies" ), python::arg( "spins" ), python::arg( "gn" ),
    python::arg( "gg" ), python::arg( "gfa" ), python::arg( "gfb" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    awri        the atomic weight ratio\n"
    "    apl         the l dependent scattering radius\n"
    "    l           the orbital angular momentum value\n"
    "    energies    the resonance energies (NRS values)\n"
    "    spins       the spin values (NRS values)\n"
    "    gn          the neutron widths (NRS values)\n"
    "    gg          the gamma widths (NRS values)\n"
    "    gfa         the first fission widths (NRS values)\n"
    "    gfb         the second fission widths (NRS values)"
  )
  .def_property_readonly(

    "AWRI",
    [] ( const Component& self ) { return self.AWRI(); },
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    [] ( const Component& self ) { return self.atomicWeightRatio(); },
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "APL",
    &Component::APL,
    "The l dependent scattering radius"
  )
  .def_property_readonly(

    "l_dependent_scattering_radius",
    &Component::lDependentScatteringRadius,
    "The l dependent scattering radius"
  )
  .def_property_readonly(

    "L",
    [] ( const Component& self ) { return self.L(); },
    "The value of the orbital momentum l"
  )
  .def_property_readonly(

    "orbital_momentum",
    [] ( const Component& self ) { return self.orbitalMomentum(); },
    "The value of the orbital momentum l"
  )
  .def_property_readonly(

    "NRS",
    [] ( const Component& self ) { return self.NRS(); },
    "The number of resonances for this l value"
  )
  .def_property_readonly(

    "number_resonances",
    [] ( const Component& self ) { return self.numberResonances(); },
    "The number of resonances for this l value"
  )
  .def_property_readonly(

    "ER",
    [] ( const Component& self ) -> DoubleRange
       { return self.ER(); },
    "The resonance energies"
  )
  .def_property_readonly(

    "resonance_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.resonanceEnergies(); },
    "The resonance energies"
  )
  .def_property_readonly(

    "AJ",
    [] ( const Component& self ) -> DoubleRange
       { return self.AJ(); },
    "The spin values"
  )
  .def_property_readonly(

    "spin_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinValues(); },
    "The spin values"
  )
  .def_property_readonly(

    "GN",
    [] ( const Component& self ) -> DoubleRange
       { return self.GN(); },
    "The neutron widths"
  )
  .def_property_readonly(

    "neutron_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.neutronWidths(); },
    "The neutron widths"
  )
  .def_property_readonly(

    "GG",
    [] ( const Component& self ) -> DoubleRange
       { return self.GG(); },
    "The gamma widths"
  )
  .def_property_readonly(

    "gamma_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.gammaWidths(); },
    "The gamma widths"
  )
  .def_property_readonly(

    "GFA",
    [] ( const Component& self ) -> DoubleRange
       { return self.GFA(); },
    "The first fission widths"
  )
  .def_property_readonly(

    "first_fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.firstFissionWidths(); },
    "The first fission widths"
  )
  .def_property_readonly(

    "GFB",
    [] ( const Component& self ) -> DoubleRange
       { return self.GFB(); },
    "The second fission widths"
  )
  .def_property_readonly(

    "second_fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.secondFissionWidths(); },
    "The second fission widths"
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
