// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/DerivedRatioToStandard.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDerivedRatioToStandard( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::DerivedRatioToStandard;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "DerivedRatioToStandard",
    "Covariance component - NC-type sub-subsection for ratios to standards"
  );

  // wrap the section
  component
  .def(

    python::init< int, double, double, int, int, double, double,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "lty" ), python::arg( "e1" ), python::arg( "e2" ),
    python::arg( "mats" ), python::arg( "mts" ),
    python::arg( "xmfs" ), python::arg( "xlfss" ),
    python::arg( "energies" ), python::arg( "weights" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    lty            covariance procedure\n"
    "    e1             lower energy\n"
    "    e2             upper energy\n"
    "    mats           standard's material number\n"
    "    mts            standard's MT number\n"
    "    xmfs           standard's MF number\n"
    "    xlfss          standard's final excited state\n"
    "    energies       energy boundaries of intervals\n"
    "    weights        weights of energies\n"
  )
  .def_property_readonly(

    "LTY",
    &Component::LTY,
    "the procedure"
  )
  .def_property_readonly(

    "procedure",
    &Component::procedure,
    "the procedure"
  )
  .def_property_readonly(

    "E1",
    &Component::E1,
    "the lower energy bound"
  )
  .def_property_readonly(

    "lower_energy",
    &Component::lowerEnergy,
    "the lower energy bound"
  )
  .def_property_readonly(

    "E2",
    &Component::E2,
    "the upper energy bound"
  )
  .def_property_readonly(

    "upper_energy",
    &Component::upperEnergy,
    "the upper energy bound"
  )
  .def_property_readonly(

    "MATS",
    &Component::MATS,
    "the standard's material number"
  )
  .def_property_readonly(

    "standard_material_number",
    &Component::standardMaterialNumber,
    "the standard's material number"
  )
  .def_property_readonly(

    "MTS",
    &Component::MTS,
    "the standard's section number"
  )
  .def_property_readonly(

    "standard_section_number",
    &Component::standardSectionNumber,
    "the standard's section number"
  )
  .def_property_readonly(

    "NEI",
    &Component::NEI,
    "the number of energies"
  )
  .def_property_readonly(

    "number_energies",
    &Component::numberEnergies,
    "the number of energies"
  )
  .def_property_readonly(

    "XMFS",
    &Component::XMFS,
    "the standard's file number"
  )
  .def_property_readonly(

    "standard_file_number",
    &Component::standardFileNumber,
    "the standard's file number"
  )
  .def_property_readonly(

    "XLFSS",
    &Component::XLFSS,
    "the standard's final excited state"
  )
  .def_property_readonly(

    "standard_final_excited_state",
    &Component::standardFinalExcitedState,
    "the standard's final excited state"
  )
  .def_property_readonly(

    "EI",
    [] ( const Component& self ) -> DoubleRange
       { return self.EI(); },
    "the energies"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "the energies"
  )
  .def_property_readonly(

    "WEI",
    [] ( const Component& self ) -> DoubleRange
       { return self.WEI(); },
    "the weights"
  )
  .def_property_readonly(

    "weights",
    [] ( const Component& self ) -> DoubleRange
       { return self.weights(); },
    "the weights"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
