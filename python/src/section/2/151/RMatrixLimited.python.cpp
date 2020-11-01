// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapRMatrixLimited( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited;
  using ParticlePairs = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs;
  using SpinGroup = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup;
  using SpinGroupRange = RandomAccessAnyView< SpinGroup >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< SpinGroup >(
      module,
      "any_view< SpinGroup, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "RMatrixLimited",
    "MF2 MT151 section - R-matrix limited resonance parameters"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( bool ifg, bool krl, int krm, ParticlePairs pairs,
                       std::vector< SpinGroup >&& groups )
                     { return Component( ifg, krl, krm, std::move( pairs ),
                                         std::move( groups ) ); } ),
    python::arg( "ifg" ), python::arg( "krl" ), python::arg( "krm" ),
    python::arg( "pairs" ), python::arg( "groups" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    ifg       flag to indicate whether or not the widths are reduced\n"
    "    krl       the non relativistic kinematics flag\n"
    "    krm       the resonance formalism to be used\n"
    "    pairs     the particle pairs\n"
    "    groups    the spin groups"
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

    "IFG",
    &Component::IFG,
    "The flag to indicate whether or not the widths are reduced"
  )
  .def_property_readonly(

    "reduced_widths",
    &Component::reducedWidths,
    "The flag to indicate whether or not the widths are reduced"
  )
  .def_property_readonly(

    "KRM",
    &Component::KRM,
    "The resonance formalism to be employed"
  )
  .def_property_readonly(

    "formalism",
    &Component::formalism,
    "The resonance formalism to be employed"
  )
  .def_property_readonly(

    "KRL",
    &Component::KRL,
    "The non relativistic kinematics flag"
  )
  .def_property_readonly(

    "non_relativistic_kinematics",
    &Component::nonRelativisticKinematics,
    "The non relativistic kinematics flag"
  )
  .def_property_readonly(

    "NJS",
    &Component::NJS,
    "The number of spin groups"
  )
  .def_property_readonly(

    "number_spin_groups",
    &Component::numberSpinGroups,
    "The number of spin groups"
  )
  .def_property_readonly(

    "particle_pairs",
    &Component::particlePairs,
    "The particle pair information"
  )
  .def_property_readonly(

    "spin_groups",
    [] ( const Component& self ) -> SpinGroupRange
       { return self.spinGroups(); },
    "The spin groups"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
