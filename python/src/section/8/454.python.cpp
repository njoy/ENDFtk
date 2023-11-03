// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/454.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_8_454( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 8, 454 >;
  using FissionYieldData = njoy::ENDFtk::section::FissionYieldData;
  using FissionYieldDataRange = RandomAccessAnyView< FissionYieldData >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT454",
    "MT454 - independent fission product yields"
  );

  // wrap components

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF8 MT454 section - independent fission product yields"
  );

  // wrap the section
  section
  .def(

    python::init< double, double, std::vector< FissionYieldData >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "yields" ),
    "Initialise the section with fission yield data\n\n"
    "Arguments:\n"
    "    self     the section\n"
    "    zaid     the material ZAID value\n"
    "    awr      the atomic weight ratio\n"
    "    yields   the fission yield data"
  )
  .def(

    python::init< double, double,
                  std::vector< unsigned int >&&,
                  std::vector< unsigned int >&&,
                  std::vector< std::array< double, 2 > >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "identifiers" ), python::arg( "states" ),
    python::arg( "yields" ),
    "Initialise the section with energy independent fission yields\n\n"
    "Arguments:\n"
    "    self          the section\n"
    "    zaid          the material ZAID value\n"
    "    awr           the atomic weight ratio\n"
    "    identifiers   the fission product identifiers (NFP values)\n"
    "    states        the isomeric states (NFP values)\n"
    "    yields        the fission yield values and uncertainties\n"
    "                  (NFP pairs)"
  )
  .def(

    python::init< double, double,
                  std::vector< unsigned int >&&,
                  std::vector< unsigned int >&&,
                  std::vector< double >&&,
                  std::vector< unsigned int >&&,
                  std::vector< std::vector< std::array< double, 2 > > >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "identifiers" ), python::arg( "states" ),
    python::arg( "energies" ), python::arg( "interpolants" ),
    python::arg( "yields" ),
    "Initialise the section with energy dependent fission yields\n\n"
    "Arguments:\n"
    "    self           the section\n"
    "    zaid           the material ZAID value\n"
    "    awr            the atomic weight ratio\n"
    "    identifiers    the fission product identifiers (NFP values)\n"
    "    states         the isomeric states (NFP values)\n"
    "    energies       the incident neutron energies (NE values)\n"
    "    interpolants   the interpolation types (NE-1 values)\n"
    "    yields         the fission yield values and uncertainties\n"
    "                   (NFP arrays of NE pairs)"
  )
  .def_property_readonly(

    "LE",
    &Section::LE,
    "Whether or not the fission yield data is energy independent"
  )
  .def_property_readonly(

    "is_energy_independent",
    &Section::isEnergyIndependent,
    "Whether or not the fission yield data is energy independent"
  )
  .def_property_readonly(

    "NE",
    &Section::NE,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "number_incident_energies",
    &Section::numberIncidentEnergies,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "E",
    [] ( const Section& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "incident_energies",
    [] ( const Section& self ) -> DoubleRange
       { return self.incidentEnergies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "yields",
    [] ( const Section& self ) -> FissionYieldDataRange
       { return self.yields(); },
    "The fission yield data, one for each incident energy"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
