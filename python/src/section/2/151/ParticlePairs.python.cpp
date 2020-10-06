// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapParticlePairs( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs;
  using DoubleRange = RandomAccessAnyView< double >;

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
    "Initialise the scattering radius\n\n"
    "Arguments:\n"
    "    self    the particle pair object\n"
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

    "NP",
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
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
