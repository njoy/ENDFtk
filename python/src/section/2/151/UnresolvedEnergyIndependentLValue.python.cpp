// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapUnresolvedEnergyIndependentLValue( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::UnresolvedEnergyIndependent::LValue;
  using DoubleRange = RandomAccessAnyView< double >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedEnergyIndependentLValue",
    "MF2 MT151 section - the unresolved resonance parameters for a given\n"
    "                    l value or independent widths (with no fission given)"
  );

  // wrap the section
  component
  .def(

    python::init< double, int,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< int >&&, std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "awri" ), python::arg( "l" ),
    python::arg( "spins" ), python::arg( "d" ), python::arg( "amun" ),
    python::arg( "gn" ), python::arg( "gg" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self     the component\n"
    "    awri     the atomic weight ratio\n"
    "    l        the orbital angular momentum value\n"
    "    spins    the spin values (NJS values)\n"
    "    d        the level spacing values (NJS values)\n"
    "    amun     the degrees of freedom for the neutron width (NJS values)\n"
    "    gn       the average neutron widths (NJS values)\n"
    "    gg       the average gamma widths (NJS values)"
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

    "NJS",
    [] ( const Component& self ) { return self.NJS(); },
    "The number of J values for this l value"
  )
  .def_property_readonly(

    "number_spin_values",
    [] ( const Component& self ) { return self.numberSpinValues(); },
    "The number of J values for this l value"
  )
  .def_property_readonly(

    "D",
    [] ( const Component& self ) -> DoubleRange
       { return self.D(); },
    "The average level spacing values"
  )
  .def_property_readonly(

    "average_level_spacings",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageLevelSpacings(); },
       "The average level spacing values"
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

    "AMUN",
    [] ( const Component& self ) -> DoubleRange
       { return self.AMUN(); },
    "The degrees of freedom for the neutron width"
  )
  .def_property_readonly(

    "neutron_width_degrees_freedom",
    [] ( const Component& self ) -> DoubleRange
       { return self.neutronWidthDegreesFreedom(); },
    "The degrees of freedom for the neutron width"
  )
  .def_property_readonly(

    "AMUG",
    [] ( const Component& self ) -> DoubleRange
       { return self.AMUG(); },
    "The degrees of freedom for the gamma width"
  )
  .def_property_readonly(

    "gamma_width_degrees_freedom",
    [] ( const Component& self ) -> DoubleRange
       { return self.gammaWidthDegreesFreedom(); },
    "The degrees of freedom for the gamma width"
  )
  .def_property_readonly(

    "AMUF",
    [] ( const Component& self ) -> DoubleRange
       { return self.AMUF(); },
    "The degrees of freedom for the fission width"
  )
  .def_property_readonly(

    "fission_width_degrees_freedom",
    [] ( const Component& self ) -> DoubleRange
       { return self.gammaWidthDegreesFreedom(); },
    "The degrees of freedom for the gamma width"
  )
  .def_property_readonly(

    "AMUX",
    [] ( const Component& self ) -> DoubleRange
       { return self.AMUX(); },
    "The degrees of freedom for the competitive width"
  )
  .def_property_readonly(

    "competitive_width_degrees_freedom",
    [] ( const Component& self ) -> DoubleRange
       { return self.competitiveWidthDegreesFreedom(); },
    "The degrees of freedom for the competitive width"
  )
  .def_property_readonly(

    "GN",
    [] ( const Component& self ) -> DoubleRange
       { return self.GN(); },
    "The average neutron widths"
  )
  .def_property_readonly(

    "average_neutron_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageNeutronWidths(); },
    "The average neutron widths"
  )
  .def_property_readonly(

    "GG",
    [] ( const Component& self ) -> DoubleRange
       { return self.GG(); },
    "The average gamma widths"
  )
  .def_property_readonly(

    "average_gamma_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageGammaWidths(); },
    "The average gamma widths"
  )
  .def_property_readonly(

    "GF",
    [] ( const Component& self ) -> DoubleRange
       { return self.GF(); },
    "The average fission width values"
  )
  .def_property_readonly(

    "average_fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageFissionWidths(); },
    "The average fission width values"
  )
  .def_property_readonly(

    "GX",
    [] ( const Component& self ) -> DoubleRange
       { return self.GX(); },
    "The average competitive width values"
  )
  .def_property_readonly(

    "average_competitive_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageCompetitiveWidths(); },
    "The average competitive width values"
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
