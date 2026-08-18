// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/gsection/3g.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGSection_3( python::module& module, python::module& ) {

  // type aliases
  using GSection = njoy::ENDFtk::section::GType< 3 >;

  // create the section
  python::class_< GSection > gsection(

    module,
    "GSection",
    "MF3 gsection - reaction cross sections and ratio quantities"
  );

  // wrap the section
  gsection
  .def(

    python::init< int, int, double, int, double,
                  std::vector< std::vector< std::vector< double > > >&&,
                  std::vector< std::vector< std::vector< double > > >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "lr" ), python::arg( "temp" ), python::arg( "flux" ),
    python::arg( "xs" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self     the section\n"
    "    mt       the MT number\n"
    "    zaid     the ZA identifier\n"
    "    awr      the atomic mass ratio\n"
    "    lr       the complex breakup flag\n"
    "    temp     the temperature\n"
    "    flux     3D array of the group-wise fluxes (nl, nz, ngn)\n"
    "    xs       3D array of the group-wise cross sections (nl, nz, ngn)"
  )
  .def(

    python::init< int, int, double, int, double,
                  std::vector< std::vector< std::vector< double > > >&&,
                  std::vector< std::vector< std::vector< double > > >&&,
                  std::vector< std::vector< std::vector< double > > >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "lr" ), python::arg( "temp" ), python::arg( "flux" ),
    python::arg( "xs" ), python::arg( "ratio" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self     the section\n"
    "    mt       the MT number\n"
    "    zaid     the ZA  identifier\n"
    "    awr      the atomic mass ratio\n"
    "    lr       the complex breakup flag (default 0)\n"
    "    temp     the temperature\n"
    "    flux     3D array of the group-wise fluxes (nl, nz, ngn)\n"
    "    xs       3D array of the group-wise cross sections (nl, nz, ngn)\n"
    "    ratio    3D array of the group-wise ratios (nl, nz, ngn)"
  )
  .def(

    python::init< int, int, double, std::vector< double >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "xs" ),
    "Initialise an ERRORR formatted section\n\n"
    "Arguments:\n"
    "    self     the section\n"
    "    mt       the MT number\n"
    "    zaid     the ZA identifier\n"
    "    awr      the atomic mass ratio\n"
    "    xs       the group-wise cross sections (ngn)"
  )
  .def_property_readonly(

    "is_groupr",
    &GSection::isGroupr,
    "Flag to indicate whether or not this is a GROUPR formatted section"
  )
  .def_property_readonly(

    "is_errorr",
    &GSection::isErrorr,
    "Flag to indicate whether or not this is an ERRORR formatted section"
  )
  .def_property_readonly(

    "NL",
    &GSection::NL,
    "The number of legendre moments"
  )
  .def_property_readonly(

    "number_moments",
    &GSection::numberMoments,
    "The number of legendre moments"
  )
  .def_property_readonly(

    "NZ",
    &GSection::NZ,
    "The number of dilution values"
  )
  .def_property_readonly(

    "number_dilutions",
    &GSection::numberDilutions,
    "The number of dilution values"
  )
  .def_property_readonly(

    "LR",
    &GSection::LR,
    "The complex break up flag"
  )
  .def_property_readonly(

    "break_up",
    &GSection::breakUp,
    "The complex break up flag"
  )
  .def_property_readonly(

    "NGN",
    &GSection::NGN,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "number_groups",
    &GSection::numberNeutronGroups,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "temperature",
    &GSection::temperature,
    "The temperature"
  )
  .def(

    "cross_section",
    &GSection::crossSection,
    python::arg("moment"), python::arg("dilution"),
    "The group cross sections for a given moment and dilution index"
  )
  .def(

    "flux",
    &GSection::flux,
    python::arg("moment"), python::arg("dilution"),
    "The group fluxes for a given moment and dilution index"
  )
  .def(

    "ratio",
    &GSection::ratio,
    python::arg("moment"), python::arg("dilution"),
    "The group ratios for a given moment and dilution index"
  );

  // add standard section definitions
  addStandardGSectionDefinitions< GSection >( gsection );
}
