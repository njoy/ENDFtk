// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/26.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf26 {

void wrapEnergyTransfer( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 26 >;
  using Component = Section::EnergyTransfer;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "EnergyTransfer",
    "MF6 section - LAW=8 - only energy transfer during electro-atomic excitation\n"
    "                      or bremsstrahlung is given"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "transfer" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    transfer        the energy transfer values"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Component& self ) { return self.LAW(); },
    "The distribution type (the LAW flag)"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "ET",
    [] ( const Component& self ) -> DoubleRange
       { return self.ET(); },
    "The energy transfer values"
  )
  .def_property_readonly(

    "energy_transfer_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.energyTransferValues(); },
    "The energy transfer values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf26
