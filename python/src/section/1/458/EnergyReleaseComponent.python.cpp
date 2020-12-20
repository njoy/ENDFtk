// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/458.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt458 {

void wrapEnergyReleaseComponent( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 458 >;
  using Component = Section::EnergyReleaseComponent;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "EnergyReleaseComponent",
    "MF1 MT458 component - a tabulated fission energy release component"
  );

  // wrap the component
  component
  .def(

    python::init< bool, int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "ldrv" ), python::arg( "ifc" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "qvalues" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    ldrv            the primary evaluation flag (true/false)\n"
    "    ifc             the index for the fission energy release component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the incident energy values\n"
    "    qvalues         the fission q values"
  )
  .def_property_readonly(

    "LDRV",
    &Component::LDRV,
    "The primary evaluation flag (true/false)"
  )
  .def_property_readonly(

    "primary_evaluation_flag",
    &Component::primaryEvaluationFlag,
    "The primary evaluation flag (true/false)"
  )
  .def_property_readonly(

    "IFC",
    &Component::IFC,
    "The index for the fission energy release component"
  )
  .def_property_readonly(

    "component_index",
    &Component::componentIndex,
    "The index for the fission energy release component"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "EIFC",
    [] ( const Component& self ) -> DoubleRange
       { return self.EIFC(); },
       "The fission energy release values"
  )
  .def_property_readonly(

    "q_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.qValues(); },
    "The fission energy release values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mt458
} // namespace mf1
