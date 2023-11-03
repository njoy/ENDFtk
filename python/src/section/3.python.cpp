// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/3.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_3( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 3 >;

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF3 section - reaction cross sections"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, double, double, long,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "qm" ), python::arg( "qi" ), python::arg( "lr" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self           the section\n"
    "    mt             the MT number\n"
    "    zaid           the ZA  identifier\n"
    "    awr            the atomic mass ratio\n"
    "    qm             the mass difference Q value\n"
    "    qi             the reaction Q value\n"
    "    lr             the complex breakup flag\n"
    "    boundaries     the interpolation range boundaries\n"
    "    interpolants   the interpolation types for each range\n"
    "    energies       the energy values\n"
    "    xs             the cross section values"
  )
  .def(

    python::init< int, double, double, double, double,
                  std::vector< double >&&, std::vector< double >&&,
                  long, long >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "qm" ), python::arg( "qi" ),
    python::arg( "energies" ), python::arg( "xs" ),
    python::arg( "interpolant" ) = 2, python::arg( "lr" ) = 0,
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self          the section\n"
    "    mt            the MT number\n"
    "    zaid          the ZA  identifier\n"
    "    awr           the atomic mass ratio\n"
    "    qm            the mass difference Q value\n"
    "    qi            the reaction Q value\n"
    "    energies      the energy values\n"
    "    xs            the cross section values\n"
    "    interpolant   the interpolation type (default 2 - linlin)\n"
    "    lr            the complex breakup flag (default 0)"
  )
  .def_property_readonly(

    "QM",
    &Section::QM,
    "The mass difference Q value"
  )
  .def_property_readonly(

    "mass_difference_qvalue",
    &Section::massDifferenceQValue,
    "The mass difference Q value"
  )
  .def_property_readonly(

    "QI",
    &Section::QI,
    "The reaction Q value"
  )
  .def_property_readonly(

    "reaction_qvalue",
    &Section::reactionQValue,
    "The mass difference Q value"
  )
  .def_property_readonly(

    "LR",
    &Section::LR,
    "The complex break up flag"
  )
  .def_property_readonly(

    "complex_breakup",
    &Section::complexBreakUp,
    "The complex break up flag"
  )
  .def_property_readonly(

    "energies",
    [] ( const Section& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Section& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Section >( section );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
