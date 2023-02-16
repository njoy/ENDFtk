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

void wrapParticlePairs( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::RMatrixLimited::ParticlePairs;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ParticlePairs",
    "MF2 MT151 section - particle pair information"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< int >&&,
                  std::vector< int >&&, std::vector< int >&& >(),
    python::arg( "ma" ), python::arg( "mb" ),
    python::arg( "za" ), python::arg( "zb" ),
    python::arg( "ia" ), python::arg( "ib" ),
    python::arg( "pa" ), python::arg( "pb" ),
    python::arg( "q" ), python::arg( "pnt" ),
    python::arg( "shf" ), python::arg( "mt" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    ma      the mass of the first particle in each particle pair\n"
    "    mb      the mass of the first particle in each particle pair\n"
    "    za      the charge of the first particle in each particle pair\n"
    "    zb      the charge of the first particle in each particle pair\n"
    "    ia      the spin of the first particle in each particle pair\n"
    "    ib      the spin of the first particle in each particle pair\n"
    "    pa      the parity of the first particle in each particle pair\n"
    "    pb      the parity of the first particle in each particle pair\n"
    "    q       the mass of the first particle in each particle pair\n"
    "    pnt     the mass of the first particle in each particle pair\n"
    "    shf     the charge of the first particle in each particle pair\n"
    "    mt      the charge of the first particle in each particle pair"
  )
  .def_property_readonly(

    "NPP",
    &Component::NPP,
    "The number of particle pairs"
  )
  .def_property_readonly(

    "number_particle_pairs",
    &Component::numberParticlePairs,
    "The number of particle pairs"
  )
  .def_property_readonly(

    "MA",
    [] ( const Component& self ) -> DoubleRange
       { return self.MA(); },
    "The mass of the first particle in each particle pair"
  )
  .def_property_readonly(

    "mass_particle_A",
    [] ( const Component& self ) -> DoubleRange
       { return self.massParticleA(); },
    "The mass of the first particle in each particle pair"
  )
  .def_property_readonly(

    "MB",
    [] ( const Component& self ) -> DoubleRange
       { return self.MB(); },
    "The mass of the second particle in each particle pair"
  )
  .def_property_readonly(

    "mass_particle_B",
    [] ( const Component& self ) -> DoubleRange
       { return self.massParticleB(); },
    "The mass of the second particle in each particle pair"
  )
  .def_property_readonly(

    "ZA",
    [] ( const Component& self ) -> DoubleRange
       { return self.ZA(); },
    "The charge of the first particle in each particle pair"
  )
  .def_property_readonly(

    "charge_particle_A",
    [] ( const Component& self ) -> DoubleRange
       { return self.chargeParticleA(); },
    "The mass of the first particle in each particle pair"
  )
  .def_property_readonly(

    "ZB",
    [] ( const Component& self ) -> DoubleRange
       { return self.ZB(); },
    "The charge of the second particle in each particle pair"
  )
  .def_property_readonly(

    "charge_particle_B",
    [] ( const Component& self ) -> DoubleRange
       { return self.chargeParticleB(); },
    "The charge of the second particle in each particle pair"
  )
  .def_property_readonly(

    "IA",
    [] ( const Component& self ) -> DoubleRange
       { return self.IA(); },
    "The spin of the first particle in each particle pair"
  )
  .def_property_readonly(

    "spin_particle_A",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinParticleA(); },
    "The spin of the first particle in each particle pair"
  )
  .def_property_readonly(

    "IB",
    [] ( const Component& self ) -> DoubleRange
       { return self.IB(); },
    "The spin of the second particle in each particle pair"
  )
  .def_property_readonly(

    "spin_particle_B",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinParticleB(); },
    "The spin of the second particle in each particle pair"
  )
  .def_property_readonly(

    "PA",
    [] ( const Component& self ) -> DoubleRange
       { return self.PA(); },
    "The parity of the first particle in each particle pair"
  )
  .def_property_readonly(

    "parity_particle_A",
    [] ( const Component& self ) -> DoubleRange
       { return self.parityParticleA(); },
    "The parity of the first particle in each particle pair"
  )
  .def_property_readonly(

    "PB",
    [] ( const Component& self ) -> DoubleRange
       { return self.PB(); },
    "The parity of the second particle in each particle pair"
  )
  .def_property_readonly(

    "parity_particle_B",
    [] ( const Component& self ) -> DoubleRange
       { return self.parityParticleB(); },
    "The parity of the second particle in each particle pair"
  )
  .def_property_readonly(

    "PNT",
    [] ( const Component& self ) -> IntRange
       { return self.PNT(); },
    "The penetrability flag for each particle pair"
  )
  .def_property_readonly(

    "penetrability_flag",
    [] ( const Component& self ) -> IntRange
       { return self.penetrabilityFlag(); },
    "The penetrability flag for each particle pair"
  )
  .def_property_readonly(

    "SHF",
    [] ( const Component& self ) -> IntRange
       { return self.SHF(); },
    "The shift factor flag for each particle pair"
  )
  .def_property_readonly(

    "shift_factor_flag",
    [] ( const Component& self ) -> IntRange
       { return self.shiftFactorFlag(); },
    "The shift factor flag for each particle pair"
  )
  .def_property_readonly(

    "MT",
    [] ( const Component& self ) -> IntRange
       { return self.MT(); },
    "The MT value associated to each particle pair"
  )
  .def_property_readonly(

    "Q",
    [] ( const Component& self ) -> IntRange
       { return self.Q(); },
    "The Q value for each particle pair"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf2
