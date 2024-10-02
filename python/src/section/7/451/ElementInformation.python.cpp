// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/451.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapElementInformation( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 7, 451 >;
  using Component = Section::ElementInformation;

  // wrap views of this component

  // create the component
  python::class_< Component > component(

    module,
    "ElementInformation",
    "MF7 MT451 component - element information for thermal scattering moderators"
  );

  // wrap the component
  component
  .def(

    python::init< unsigned int,
                  std::vector< unsigned int >&&, std::vector< unsigned int >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "atoms" ), python::arg( "identifiers" ), python::arg( "states" ),
    python::arg( "abundances" ), python::arg( "weights" ),
    python::arg( "xs" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    atoms          the number of atoms in the molecule or unit cell\n"
    "    identifiers    the isotope identifiers (ZA identifier)\n"
    "    states         the isomeric state for each isotope\n"
    "    abundances     the isotope abundances\n"
    "    weights        the atomic weight ratios\n"
    "    xs             the free atom scattering cross sections"
  )
  .def_property_readonly(

    "NAS",
    &Component::NAS,
    "The number of atoms in the molecule or unit cell"
  )
  .def_property_readonly(

    "number_atoms",
    &Component::numberAtoms,
    "The number of atoms in the molecule or unit cell"
  )
  .def_property_readonly(

    "NI",
    &Component::NI,
    "The number of isotopes in the element"
  )
  .def_property_readonly(

    "number_isotopes",
    &Component::numberIsotopes,
    "The number of isotopes in the element"
  )
  .def_property_readonly(

    "ZAI",
    [] ( const Component& self ) -> IntRange
       { return self.ZAI(); },
    "The isotope ZA identifiers"
  )
  .def_property_readonly(

    "isotope_identifiers",
    [] ( const Component& self ) -> IntRange
       { return self.isotopeIdentifiers(); },
    "The isotope ZA identifiers"
  )
  .def_property_readonly(

    "LISI",
    [] ( const Component& self ) -> IntRange
       { return self.LISI(); },
    "The isotope isomeric states"
  )
  .def_property_readonly(

    "isomeric_states",
    [] ( const Component& self ) -> IntRange
       { return self.isomericStates(); },
    "The isotope isomeric states"
  )
  .def_property_readonly(

    "AFI",
    [] ( const Component& self ) -> DoubleRange
       { return self.AFI(); },
    "The isotope abundancies"
  )
  .def_property_readonly(

    "abundances",
    [] ( const Component& self ) -> DoubleRange
       { return self.abundances(); },
    "The isotope abundancies"
  )
  .def_property_readonly(

    "AWRI",
    [] ( const Component& self ) -> DoubleRange
       { return self.AWRI(); },
    "The isotope atomic weight ratios"
  )
  .def_property_readonly(

    "atomic_weight_ratios",
    [] ( const Component& self ) -> DoubleRange
       { return self.atomicWeightRatios(); },
     "The isotope atomic weight ratios"
  )
  .def_property_readonly(

    "SFI",
    [] ( const Component& self ) -> DoubleRange
       { return self.SFI(); },
    "The isotope free atom scattering cross sections"
  )
  .def_property_readonly(

    "free_scattering_cross_sections",
    [] ( const Component& self ) -> DoubleRange
       { return self.freeScatteringCrossSections(); },
     "The isotope free atom scattering cross sections"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf7
