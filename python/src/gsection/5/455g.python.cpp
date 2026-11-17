// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/gsection/5/455g.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGSection_5_455( python::module& module, python::module& ) {

  // type alias
  using GSection = njoy::ENDFtk::section::GType< 5, 455 >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT455",
    "MT455 - delayed neutron spectra"
  );

  // create the section
  python::class_< GSection > gsection(

    submodule,
    "GSection",
    "MF5 MT455 gsection - delayed neutron spectra"
  );

  // wrap section
  gsection
  .def(

    python::init< double, double, int, double, int,
                  std::vector< std::vector< double > >&&,
                  std::vector< double >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lr" ) = 0,
    python::arg( "temp" ), python::arg( "ng2" ), python::arg( "chi" ), python::arg( "time_constants" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "   self            the section\n"
    "   zaid            the ZA identifier\n"
    "   awr             the atomic weight ratio\n"
    "   lr              the complex breakup flag\n"
    "   temp            the temperature\n"
    "   ng2             number of secondary positions\n"
    "   time_constants  delayed neutron time constants (nt)\n"
    "   chi             delayed neutron spectra (nt, ngn)"
  )
  .def_property_readonly(

    "NT",
    &GSection::NT,
    "The number of time constants"
  )
  .def_property_readonly(

    "number_time_constants",
    &GSection::numberTimeConstants,
    "The number of time constants"
  )
  .def_property_readonly(

    "NZ",
    &GSection::NZ,
    "The number of dilutions"
  )
  .def_property_readonly(

    "number_dilutions",
    &GSection::numberDilutions,
    "The number of dilutions"
  )
  .def_property_readonly(

    "LR",
    &GSection::LR,
    "The complex breakup flag"
  )
  .def_property_readonly(

    "break_up",
    &GSection::breakUp,
    "The complex breakup flag"
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
  .def_property_readonly(

    "NGN",
    &GSection::NGN,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "number_neutron_groups",
    &GSection::numberNeutronGroups,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "time_constants",
    &GSection::lambda,
    "The delayed time constants"
  )
  .def(

    "chi",
    &GSection::chi,
    python::arg( "time_constant" ),
    "The delayed neutron spectra for a given time constant"
  );

  addStandardGSectionDefinitions< GSection >( gsection );
}