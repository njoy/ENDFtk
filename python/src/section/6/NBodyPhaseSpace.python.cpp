// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapNBodyPhaseSpace( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 6 >::NBodyPhaseSpace;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "NBodyPhaseSpace",
    "MF6 section - LAW=6 - a simplified distribution for neutron and charged\n"
    "                       particles"
  );

  // wrap the section
  component
  .def(

    python::init< double, int >(),
    python::arg( "apsx" ), python::arg( "npsx" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    apsx    the particle mass (in neutron mass units)\n"
    "    npsx    the number of particles"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Component& self ) { return self.LAW(); },
    "The distribution type (the LAW flag)"
  )
  .def_property_readonly(

    "APSX",
    &Component::APSX,
    "The total mass of all particles (in neutron mass units)"
  )
  .def_property_readonly(

    "total_mass",
    &Component::totalMass,
    "The total mass of all particles (in neutron mass units)"
  )
  .def_property_readonly(

    "NPSX",
    &Component::NPSX,
    "The number of particles"
  )
  .def_property_readonly(

    "number_particles",
    &Component::numberParticles,
    "The number of particles"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
