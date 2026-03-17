// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/gsection/5/18g.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGSection_5_18( python::module& module, python::module& ) {

  // type alias
  using GSection = njoy::ENDFtk::section::GType< 5, 18 >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT18",
    "MT18 - prompt fission neutron spectra"
  );

  // create the section
  python::class_< GSection > gsection(

    submodule,
    "GSection",
    "MF5 MT18 gsection - prompt fission neutron spectra"
  );

  // wrap section
  gsection
  .def(

    python::init< double, double, int, double,
                  std::vector< double >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lr" ) = 0,
    python::arg( "temp" ), python::arg( "chi" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "   self            the section\n"
    "   zaid            the ZA identifier\n"
    "   awr             the atomic weight ratio\n"
    "   lr              the complex breakup flag\n"
    "   temp            the temperature\n"
    "   chi             delayed neutron spectra (ngn)"
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

    "chi",
    &GSection::chi,
    "The prompt fission neutron spectra"
  );

  addStandardGSectionDefinitions< GSection >( gsection );
}