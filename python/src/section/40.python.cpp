// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/40.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf40 {

  // declarations - components
  void wrapLevelBlock( python::module&, python::module& );
}

void wrapSection_40( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 40 >;
  using LevelBlock = Section::LevelBlock;
  using LevelBlockRange = RandomAccessAnyView< LevelBlock >;

  // wrap components
  mf40::wrapLevelBlock( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< LevelBlock >(
      module,
      "any_view< MF40::LevelBlock, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF40 section - covariances for radionuclide production"
  );

  // wrap the section
  section
  .def(

    python::init< int, int, double, int, std::vector< LevelBlock >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "lis" ), python::arg( "blocks" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self       the section\n"
    "    mt         the MT number\n"
    "    zaid       the ZA  identifier\n"
    "    awr        the atomic mass ratio\n"
    "    lis        the level number of target\n"
    "    blocks     the level blocks (subsections) (at least 1)\n"
  )
  .def_property_readonly(

    "LIS",
    &Section::LIS,
    "the excited level number of the target"
  )
  .def_property_readonly(

    "excited_level",
    &Section::excitedLevel,
    "the excited level number of the target"
  )
  .def_property_readonly(

    "NS",
    &Section::NS,
    "the number of level blocks (subsections)"
  )
  .def_property_readonly(

    "number_level_blocks",
    &Section::numberLevelBlocks,
    "the number of level blocks (subsections)"
  )
  .def_property_readonly(

    "level_blocks",
    [] ( const Section& self ) -> LevelBlockRange
       { return self.levelBlocks(); },
    "the level blocks (subsections) defined in this section"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
