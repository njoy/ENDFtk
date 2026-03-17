// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/gsection/1/451g.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGSection_1_451( python::module& module, python::module& ) {

  // type aliases
  using GSection = njoy::ENDFtk::section::GType< 1, 451 >;

  // create submodule
  python::module submodule = module.def_submodule(

    "MT451",
    "MT451 - descriptive data and directory"
  );


  // create the section
  python::class_< GSection > gsection(

    submodule,
    "GSection",
    "MF1 MT451 gsection - descriptive data and directory"
  );

  // wrap the section
  gsection
  .def(

    python::init< int, double, double,
                  std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "temp" ),
    python::arg( "sigz" ), python::arg( "egn" ), python::arg( "egg" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self           the section\n"
    "    zaid           the ZA value of the material\n"
    "    awr            the atomic weight ratio\n"
    "    temp           the temperature\n"
    "    sigz           the dilution values\n"
    "    egn            the neutron group structure\n"
    "    egg            the photon group structure"
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

    "NGG",
    &GSection::NGG,
    "The number of photon groups"
  )
  .def_property_readonly(

    "number_photon_groups",
    &GSection::numberPhotonGroups,
    "The number of photon groups"
  )
  .def_property_readonly(

    "SIGZ",
    [] ( const GSection& self) -> DoubleRange
        { return self.SIGZ(); },
    "The dilution values"
  )
  .def_property_readonly(

    "dilutions",
    [] ( const GSection& self ) -> DoubleRange
        { return self.dilutions(); },
    "The dilution values"
  )
  .def_property_readonly(

    "EGN",
    [] ( const GSection& self ) -> DoubleRange
        { return self.EGN(); },
    "The neutron group structure"
  )
  .def_property_readonly(

    "neutron_structure",
    [] ( const GSection& self ) -> DoubleRange
        { return self.neutronStructure(); },
    "The neutron group structure"
  )
  .def_property_readonly(

    "EGG",
    [] ( const GSection& self) -> DoubleRange
        { return self.EGG(); },
    "The photon group structure"
  )
  .def_property_readonly(

    "photon_structure",
    [] ( const GSection& self) -> DoubleRange
        { return self.photonStructure(); },
    "The photon group structure"
  );

  // add standard section definitions
  addStandardGSectionDefinitions< GSection >( gsection );
}
