// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf2 {

void wrapResonanceRange( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::ResonanceRange;
  using ScatteringRadius = Section::ScatteringRadius;
  using ResonanceParameters = Section::ResonanceRange::ResonanceParameters;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceRange",
    "MF2 MT151 section - a resonance energy range with parameters"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int, ResonanceParameters&&,
                  std::optional< ScatteringRadius >&& >(),
    python::arg( "el" ), python::arg( "eh" ), python::arg( "naps" ),
    python::arg( "parameters" ), python::arg( "scattering_radius" ) = std::nullopt,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self                the component\n"
    "    el                  the lower energy of the resonance region\n"
    "    eh                  the upper energy of the resonance region\n"
    "    naps                the flag to indicate then on how to calculate\n"
    "                        the scattering radius (0 or 1 if no energy\n"
    "                        dependent scattering radius is given and 0, 1\n"
    "                        or 2 if energy dependent scattering radius is\n"
    "                        given)\n"
    "    parameters          the resonance parameters\n"
    "    scatteringRadius    An optional energy dependent scattering radius"
  )
  .def_property_readonly(

    "EL",
    &Component::EL,
    "The lower energy boundary of the resonance region"
  )
  .def_property_readonly(

    "lower_energy",
    &Component::lowerEnergy,
    "The lower energy boundary of the resonance region"
  )
  .def_property_readonly(

    "EH",
    &Component::EH,
    "The upper energy boundary of the resonance region"
  )
  .def_property_readonly(

    "upper_energy",
    &Component::upperEnergy,
    "The upper energy boundary of the resonance region"
  )
  .def_property_readonly(

    "LRU",
    &Component::LRU,
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "type",
    &Component::type,
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "LRF",
    &Component::LRF,
    "The resonance representation"
  )
  .def_property_readonly(

    "representation",
    &Component::representation,
    "The resonance representation"
  )
  .def_property_readonly(

    "LFW",
    &Component::LFW,
    "The average fission flag"
  )
  .def_property_readonly(

    "average_fission_width_flag",
    &Component::averageFissionWidthFlag,
    "The average fission flag"
  )
  .def_property_readonly(

    "NRO",
    &Component::NRO,
    "Flag to indicate whether the scattering radius is energy dependent or not"
  )
  .def_property_readonly(

    "energy_dependent_scattering_radius",
    &Component::energyDependentScatteringRadius,
    "Flag to indicate whether the scattering radius is energy dependent or not"
  )
  .def_property_readonly(

    "NAPS",
    &Component::NAPS,
    "The scattering radius calculation option flag"
  )
  .def_property_readonly(

    "scattering_radius_calculation_option",
    &Component::scatteringRadiusCalculationOption,
    "The scattering radius calculation option flag"
  )
  .def_property_readonly(

    "scattering_radius",
    &Component::scatteringRadius,
    "The optional scattering radius"
  )
  .def_property_readonly(

    "parameters",
    &Component::parameters,
    "The resonance parameters"
  )
  .def_property_readonly(

    "NC",
    &Component::NC,
    "The number of lines in this component"
  );
}

} // namespace mf2
