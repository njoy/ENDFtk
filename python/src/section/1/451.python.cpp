// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section/1/451.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_1_451( python::module& module ) {

  // type aliases
  using DirectoryRecord = njoy::ENDFtk::DirectoryRecord;
  using Section = njoy::ENDFtk::section::Type< 1, 451 >;
  using DirectoryRange = RandomAccessAnyView< DirectoryRecord >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< DirectoryRecord >(
      module,
      "any_view< DirectoryRecord, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section_1_451",
    "MF1 MT451 section - descriptive data and directory"
  );

  // wrap the section
  section
  .def(

    python::init< double, double, int, int, int, int,
                  double, double, int, int, int,
                  double, double, int, int, int,
                  double, int,
                  const std::string&,
                  std::vector< DirectoryRecord >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lrp" ),
    python::arg( "lfi" ), python::arg( "nlib" ), python::arg( "nmod" ),
    python::arg( "elis" ), python::arg( "sta" ), python::arg( "lis" ),
    python::arg( "liso" ), python::arg( "nfor" ), python::arg( "awi" ),
    python::arg( "emax" ), python::arg( "lrel" ), python::arg( "nsub" ),
    python::arg( "nver" ), python::arg( "temp" ), python::arg( "ldrv" ),
    python::arg( "description" ), python::arg( "index" ),
    "Initialise the MF1 MT451 section\n\n"
    "Arguments:\n"
    "    self           the MF1 MT451 section\n"
    "    zaid           the ZA value of the material\n"
    "    awr            the atomic weight ratio\n"
    "    lrp            the resonance parameter flag\n"
    "    lfi            the fissile flag\n"
    "    nlib           the library type\n"
    "    nmod           the modification number\n"
    "    elis           the excitation energy\n"
    "    sta            the stability flag\n"
    "    lis            the excited level number\n"
    "    liso           the isomeric state number\n"
    "    nfor           the library format version number\n"
    "    awi            the atomic weight ratio of the incident particle\n"
    "    emax           the maximum incident energy\n"
    "    lrel           the release number\n"
    "    nsub           the sublibrary number\n"
    "    nver           the version number\n"
    "    temp           the temperature\n"
    "    ldrv           the derived material flag\n"
    "    description    the descriptive information\n"
    "    index          the index"
  )
  .def_property_readonly(

    "LRP",
    &Section::LRP,
    "The resonance parameter flag"
  )
  .def_property_readonly(

    "resonance_parameter_flag",
    &Section::resonanceParameterFlag,
    "The resonance parameter flag"
  )
  .def_property_readonly(

    "LFI",
    &Section::LFI,
    "The fissile flag"
  )
  .def_property_readonly(

    "is_fissile",
    &Section::isFissile,
    "The fissile flag"
  )
  .def_property_readonly(

    "NLIB",
    &Section::NLIB,
    "The library type"
  )
  .def_property_readonly(

    "library_type",
    &Section::libraryType,
    "The library type"
  )
  .def_property_readonly(

    "NMOD",
    &Section::NMOD,
    "The modification number"
  )
  .def_property_readonly(

    "modification_number",
    &Section::modificationNumber,
    "The modification number"
  )
  .def_property_readonly(

    "ELIS",
    &Section::ELIS,
    "The excitation energy"
  )
  .def_property_readonly(

    "excitation_energy",
    &Section::excitationEnergy,
    "The excitation energy"
  )
  .def_property_readonly(

    "STA",
    &Section::STA,
    "The stability flag"
  )
  .def_property_readonly(

    "is_stable",
    &Section::isStable,
    "The stability flag"
  )
  .def_property_readonly(

    "LIS",
    &Section::LIS,
    "The excited level number"
  )
  .def_property_readonly(

    "excited_level",
    &Section::excitedLevel,
    "The excited level number"
  )
  .def_property_readonly(

    "LISO",
    &Section::LISO,
    "The isomeric state number"
  )
  .def_property_readonly(

    "isomeric_level",
    &Section::isomericLevel,
    "The isomeric state number"
  )
  .def_property_readonly(

    "NFOR",
    &Section::NFOR,
    "The library format version number"
  )
  .def_property_readonly(

    "library_format",
    &Section::libraryFormat,
    "The library format version number"
  )
  .def_property_readonly(

    "AWI",
    &Section::AWI,
    "The atomic weight ratio of the incident particle"
  )
  .def_property_readonly(

    "projectile_atomic_mass_ratio",
    &Section::projectileAtomicMassRatio,
    "The atomic weight ratio of the incident particle"
  )
  .def_property_readonly(

    "EMAX",
    &Section::EMAX,
    "The maximum incident energy"
  )
  .def_property_readonly(

    "maximum_energy",
    &Section::maximumEnergy,
    "The maximum incident energy"
  )
  .def_property_readonly(

    "LREL",
    &Section::LREL,
    "The release number"
  )
  .def_property_readonly(

    "release_number",
    &Section::releaseNumber,
    "The release number"
  )
  .def_property_readonly(

    "NSUB",
    &Section::NSUB,
    "The sublibrary number"
  )
  .def_property_readonly(

    "sublibrary",
    &Section::subLibrary,
    "The sublibrary number"
  )
  .def_property_readonly(

    "NVER",
    &Section::NVER,
    "The version number"
  )
  .def_property_readonly(

    "version_number",
    &Section::versionNumber,
    "The version number"
  )
  .def_property_readonly(

    "TEMP",
    &Section::TEMP,
    "The temperature"
  )
  .def_property_readonly(

    "temperature",
    &Section::temperature,
    "The temperature"
  )
  .def_property_readonly(

    "LDRV",
    &Section::LDRV,
    "The derived material flag"
  )
  .def_property_readonly(

    "derived_material",
    &Section::derivedMaterial,
    "The derived material flag"
  )
  .def_property_readonly(

    "description",
    [] ( const Section& type ) -> std::string
       { return type.description(); },
    "The descriptive information"
  )
  .def_property_readonly(

    "index",
    [] ( const Section& type ) -> DirectoryRange
       { return type.index(); },
    "The index"
  )
  .def_property_readonly(

    "NWD",
    &Section::NWD,
    "The number of lines of descriptive data"
  )
  .def_property_readonly(

    "NXC",
    &Section::NXC,
    "The number of index entries"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
