// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/31.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_31( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 31 >;
  using ReactionBlock = njoy::ENDFtk::section::ReactionBlock;
  using ReactionBlockRange = RandomAccessAnyView< ReactionBlock >;

  // wrap components

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF31 section - covariances of fission multiplicities"
  );

  // wrap the section
  section
  .def(

    python::init< int, int, double, std::vector< ReactionBlock >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "reactions" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number\n"
    "    zaid        the ZA  identifier\n"
    "    awr         the atomic mass ratio\n"
    "    reactions   the reactions (subsections) (at least 1)\n"
  )
  .def_property_readonly(

    "NL",
    &Section::NL,
    "the number of reaction blocks (subsections)"
  )
  .def_property_readonly(

    "number_reactions",
    &Section::numberReactions,
    "the number of reaction blocks (subsections)"
  )
  .def_property_readonly(

    "reactions",
    [] ( const Section& self ) -> ReactionBlockRange
       { return self.reactions(); },
    "the reactions (subsections) defined in this section"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
