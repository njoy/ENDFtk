// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapBreitWignerLValue( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::BreitWignerLValue;
  using DoubleRange = RandomAccessAnyView< double >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "BreitWignerLValue",
    "MF2 MT151 section - resonance parameters for a given l value in the SLBW\n"
    "                    or MLBW representation"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int, bool,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "awri" ), python::arg( "qx" ), python::arg( "l" ),
    python::arg( "lrx" ), python::arg( "energies" ), python::arg( "spins" ),
    python::arg( "gt" ), python::arg( "gn" ), python::arg( "gg" ),
    python::arg( "gf" ),
    "Initialise the Breit-Wigner l value data\n\n"
    "Arguments:\n"
    "    awri        the atomic weight ratio\n"
    "    qx          the competitive Q value\n"
    "    l           the orbital angular momentum value\n"
    "    lrx         the competitive width flag\n"
    "    energies    the resonance energies (NRS values)\n"
    "    spins       the spin values (NRS values)\n"
    "    gt          the total widths (NRS values)\n"
    "    gn          the neutron widths (NRS values)\n"
    "    gg          the gamma widths (NRS values)\n"
    "    gf          the fission widths (NRS values)"
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

    "QX",
    &Component::QX,
    "The Q value of the competitive reaction"
  )
  .def_property_readonly(

    "competitive_qvalue",
    &Component::competitiveQValue,
    "The Q value of the competitive reaction"
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

    "LRX",
    &Component::LRX,
    "The competitive width flag"
  )
  .def_property_readonly(

    "competitive_width_flag",
    &Component::competitiveWidthFlag,
    "The competitive width flag"
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

    "GT",
    [] ( const Component& self ) -> DoubleRange
       { return self.GT(); },
    "The total widths"
  )
  .def_property_readonly(

    "total_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.totalWidths(); },
    "The total widths"
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

    "GF",
    [] ( const Component& self ) -> DoubleRange
       { return self.GF(); },
    "The fission widths"
  )
  .def_property_readonly(

    "fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.fissionWidths(); },
    "The fission widths"
  )
  .def_property_readonly(

    "GX",
    [] ( const Component& self ) -> DoubleRange
       { return self.GX(); },
    "The competitive widths"
  )
  .def_property_readonly(

    "competitive_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.competitiveWidths(); },
    "The competitive widths"
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
