// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/152.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components

void wrapSection_2_152( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 152 >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT152",
    "MT152 - internal NJOY section"
  );

  // wrap components

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF2 MT152 section - internal NJOY section"
  );

  // wrap components

  // wrap the section
  section
  .def(

    python::init< int, double, bool, int, double,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< std::vector< double > >&&,
                  std::vector< std::vector< double > >&&,
                  std::vector< std::vector< double > >&&,
                  std::vector< std::vector< double > >&&,
                  std::vector< std::vector< double > >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lssf" ),
    python::arg( "interpolation" ), python::arg( "temperature" ),
    python::arg( "dilutions" ), python::arg( "energies" ),
    python::arg( "total" ), python::arg( "elastic" ), python::arg( "fission" ),
    python::arg( "capture" ), python::arg( "cwtotal" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self             the section\n"
    "    zaid             the material ZAID value\n"
    "    awr              the atomic weight ratio\n"
    "    lssf             the lssf flag\n"
    "    interpolation    the interpolation scheme\n"
    "    temperature      the temperature\n"
    "    dilutions        the dilution values (nsigz values)\n"
    "    energies         the energy values (nunr values)\n"
    "    total            the total cross section values (nunr values of\n"
    "                     nsigz values)\n"
    "    elastic          the elastic cross section values (nunr values of\n"
    "                     nsigz values)\n"
    "    fission          the fission cross section values (nunr values of\n"
    "                     nsigz values)\n"
    "    capture          the capture cross section values (nunr values of\n"
    "                     nsigz values)\n"
    "    cwTotal          the current weighted total cross section values\n"
    "                     (nunr values of nsigz values)"
  )
  .def(

    python::init< double, double, bool, int, double,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lssf" ),
    python::arg( "interpolation" ), python::arg( "temperature" ),
    python::arg( "energies" ), python::arg( "total" ), python::arg( "elastic" ),
    python::arg( "fission" ), python::arg( "capture" ), python::arg( "cwtotal" ),
    "Initialise the section for infinite dilution only\n\n"
    "Arguments:\n"
    "    self             the section\n"
    "    zaid             the material ZAID value\n"
    "    awr              the atomic weight ratio\n"
    "    lssf             the lssf flag\n"
    "    interpolation    the interpolation scheme\n"
    "    temperature      the temperature\n"
    "    energies         the energy values (nunr values)\n"
    "    total            the total cross section values (nunr values)\n"
    "    elastic          the elastic cross section values (nunr values)\n"
    "    fission          the fission cross section values (nunr values)\n"
    "    capture          the capture cross section values (nunr values)\n"
    "    cwTotal          the current weighted total cross section values\n"
    "                     (nunr values)"
  )
  .def_property_readonly(

    "LSSF",
    &Section::LSSF,
    "The self-shielding only flag"
  )
  .def_property_readonly(

    "self_shielding_only",
    &Section::selfShieldingOnly,
    "The self-shielding only flag"
  )
  .def_property_readonly(

    "interpolation",
    &Section::interpolation,
    "The interpolation flag"
  )
  .def_property_readonly(

    "TEMZ",
    &Section::TEMZ,
    "The temperature"
  )
  .def_property_readonly(

    "temperature",
    &Section::temperature,
    "The temperature"
  )
  .def_property_readonly(

    "NW",
    &Section::NW,
    "The number of data values"
  )
  .def_property_readonly(

    "NREAC",
    &Section::NREAC,
    "The number of reactions (normally 5)"
  )
  .def_property_readonly(

    "number_reactions",
    &Section::numberReactions,
    "The number of reactions (normally 5)"
  )
  .def_property_readonly(

    "NSIGZ",
    &Section::NSIGZ,
    "The number of dilution or sigma zero values"
  )
  .def_property_readonly(

    "number_dilutions",
    &Section::numberDilutions,
    "The number of dilution or sigma zero values"
  )
  .def_property_readonly(

    "SIGZ",
    [] ( const Section& self ) -> DoubleRange
       { return self.SIGZ(); },
    "The dilution or sigma zero values"
  )
  .def_property_readonly(

    "dilutions",
    [] ( const Section& self ) -> DoubleRange
       { return self.dilutions(); },
    "The dilution or sigma zero values"
  )
  .def_property_readonly(

    "NUNR",
    &Section::NUNR,
    "The number of energy values"
  )
  .def_property_readonly(

    "number_energies",
    &Section::numberEnergies,
    "The number of energy valuess"
  )
  .def_property_readonly(

    "EUNR",
    [] ( const Section& self ) -> DoubleRange
       { return self.EUNR(); },
    "The unresolved resonance energies"
  )
  .def_property_readonly(

    "energies",
    [] ( const Section& self ) -> DoubleRange
       { return self.energies(); },
    "The unresolved resonance energies"
  )
  .def_property_readonly(

    "total",
    [] ( const Section& self ) -> DoubleRange2D
       { return self.total(); },
    "The total cross section values for each energy and dilution"
  )
  .def_property_readonly(

    "elastic",
    [] ( const Section& self ) -> DoubleRange2D
       { return self.elastic(); },
    "The elastic cross section values for each energy and dilution"
  )
  .def_property_readonly(

    "fission",
    [] ( const Section& self ) -> DoubleRange2D
       { return self.fission(); },
    "The fission cross section values for each energy and dilution"
  )
  .def_property_readonly(

    "capture",
    [] ( const Section& self ) -> DoubleRange2D
       { return self.capture(); },
    "The capture cross section values for each energy and dilution"
  )
  .def_property_readonly(

    "current_weighted_total",
    [] ( const Section& self ) -> DoubleRange2D
       { return self.currentWeightedTotal(); },
    "The current weighted total cross section values for each energy and dilution"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
