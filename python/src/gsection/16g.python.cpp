// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/gsection/16g.hpp"
#include "definitions.hpp"

// namesapce aliasees
namespace python = pybind11;

void wrapGSection_16( python::module& module, python::module& ) {

  // type alias
  using GSection = njoy::ENDFtk::section::GType< 16 >;

  // create the section
  python::class_< GSection > gsection(
      module,
      "GSection",
      "MF16 gsection - neutron-gamma matrices"
  );

  // wrap section
  gsection
  .def(

    python::init< int, int, double, int, int, double,
                  std::vector < std::vector< std::vector< double > > >&&,
                  std::vector < std::vector< std::vector< std::vector< double > > > >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "lr" ), python::arg( "ngn" ),
    python::arg( "temp" ), python::arg( "flux" ), python::arg( "matrix" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "   self        the section\n"
    "   mt          the MT number\n"
    "   zaid        the ZA identifier\n"
    "   awr         the atomic mass ratio\n"
    "   lr          the complex breakup flag (default 0)\n"
    "   ngn         the number of neutron groups\n"
    "   temp        the temperature\n"
    "   flux        3D array of the group-wise fluxes (nl, nz, ngn)\n"
    "   matrix      4D array of photon yields ( nl, nz, ngn, ngg )"
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
    "The number of diltuion values"
  )
  .def_property_readonly(

    "LRFLAG",
    &GSection::LRFLAG,
    "The break up identifier flag"
  )
  .def_property_readonly(

    "break_up_id",
    &GSection::breakUpID,
    "The break up identifier flag"
  )
  .def_property_readonly(

    "NGN",
    &GSection::NGN,
    "The number of neutron energy bins"
  )
  .def_property_readonly(

    "number_groups",
    &GSection::numberNeutronGroups,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "TEMP",
    &GSection::TEMP,
    "The temperature"
  )
  .def_property_readonly(

    "temperature",
    &GSection::temperature,
    "The temperature"
  )
  .def(

    "flux",
    &GSection::flux,
    python::arg( "moment" ), python::arg( "dilution" ),
    "The group fluxes for a given moment and dilution index"
  )
  .def(

    "matrix",
    &GSection::matrix,
    python::arg( "moment" ), python::arg( "dilution" ),
    "The matrix for a given moment and dilution index"
  );

  addStandardGSectionDefinitions< GSection >( gsection );
}