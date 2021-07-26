// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/FissionYieldData.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrap_8_FissionYieldData( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Component = njoy::ENDFtk::section::FissionYieldData;

  // wrap views of this component
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Component >(
      viewmodule,
      "any_view< FissionYieldData, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "FissionYieldData",
    "MF8 component - fission yield data for a specific incident energy (or \n"
    "                energy independent yields)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< unsigned int >&&, std::vector< unsigned int >&&,
                  std::vector< std::array< double, 2 > >&&,
                  double, int >(),
    python::arg( "identifiers" ), python::arg( "states" ),
    python::arg( "yields" ), python::arg( "energy" ) = 0.,
    python::arg( "interpolation" ) = 0,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    identifiers     the fission product identifiers (ZA identifier)\n"
    "    states          the isomeric state for each fission product\n"
    "    yields          the fission yield values and uncertainties\n"
    "    energy          the incident neutron energy (equal to zero for\n"
    "                    energy independent yields)\n"
    "    interpolation   the interpolation type (equal to zero for\n"
    "                    energy independent yields)"
  )
  .def_property_readonly(

    "LE",
    &Component::LE,
    "Whether or not the fission yield data is energy independent"
  )
  .def_property_readonly(

    "is_energy_independent",
    &Component::isEnergyIndependent,
    "Whether or not the fission yield data is energy independent"
  )
  .def_property_readonly(

    "I",
    &Component::I,
    "The interpolation type (or LE value)"
  )
  .def_property_readonly(

    "interpolation_type",
    &Component::interpolationType,
    "The interpolation type (or LE value)"
  )
  .def_property_readonly(

    "E",
    &Component::E,
    "The incident energy value"
  )
  .def_property_readonly(

    "incident_energy",
    &Component::incidentEnergy,
    "The incident energy value"
  )
  .def_property_readonly(

    "NFP",
    &Component::NFP,
    "The number of fission products"
  )
  .def_property_readonly(

    "number_fission_products",
    &Component::numberFissionProducts,
    "The number of fission products"
  )
  .def_property_readonly(

    "ZAFP",
    [] ( const Component& self ) -> IntRange
       { return self.ZAFP(); },
    "The fission product ZA identifiers"
  )
  .def_property_readonly(

    "fission_product_identifiers",
    [] ( const Component& self ) -> IntRange
       { return self.fissionProductIdentifiers(); },
    "The fission product ZA identifiers"
  )
  .def_property_readonly(

    "FPS",
    [] ( const Component& self ) -> IntRange
       { return self.FPS(); },
    "The fission product isomeric states"
  )
  .def_property_readonly(

    "isomeric_states",
    [] ( const Component& self ) -> IntRange
       { return self.isomericStates(); },
    "The fission product isomeric states"
  )
  .def_property_readonly(

    "Y",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.Y(); },
    "The fission yield values and uncertainties"
  )
  .def_property_readonly(

    "fission_yields",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.fissionYields(); },
    "The fission yield values and uncertainties"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
