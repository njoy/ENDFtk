// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section/1/455.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt455 {

  // declarations - components
  void wrapDecayConstants( python::module&, python::module& );
  void wrapEnergyIndependentConstants( python::module&, python::module& );
  void wrapEnergyDependentConstants( python::module&, python::module& );

}
}

void wrapSection_1_455( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 455 >;
  using DecayConstantData = Section::DecayConstantData;
  using Multiplicity = Section::Multiplicity;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT455",
    "MT455 - the number of delayed fission neutrons"
  );

  // wrap components
  mf1::mt455::wrapDecayConstants( submodule, viewmodule );
  mf1::mt455::wrapEnergyIndependentConstants( submodule, viewmodule );
  mf1::mt455::wrapEnergyDependentConstants( submodule, viewmodule );

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF1 MT455 section - the number of delayed fission neutrons"
  );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( int zaid, double awr, DecayConstantData constants,
                       Multiplicity multiplicity )
                     { return Section( zaid, awr,
                                       std::move( constants ),
                                       std::move( multiplicity ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "constants" ), python::arg( "multiplicity" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self            the section\n"
    "    zaid            the ZA value of the material\n"
    "    awr             the atomic weight ratio\n"
    "    constants       the decay constant data\n"
    "    multiplicity    the multiplicity data"
  )
  .def_property_readonly(

    "LNU",
    &Section::LNU,
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "representation",
    &Section::representation,
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "LDG",
    &Section::LDG,
    "The type of decay constants"
  )
  .def_property_readonly(

    "type",
    &Section::type,
    "The type of decay constants"
  )
  .def_property_readonly(

    "delayed_groups",
    &Section::delayedGroups,
    "The decay constant data for the delayed precursor groups"
  )
  .def_property_readonly(

    "nubar",
    &Section::nubar,
    "The fission multiplicity data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
