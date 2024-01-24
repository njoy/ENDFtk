// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/34.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf34 {

  // declarations - components
  void wrapReactionBlock( python::module&, python::module& );
  void wrapLegendreBlock( python::module&, python::module& );
}

void wrapSection_34( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 34 >;
  using ReactionBlock = Section::ReactionBlock;
  using ReactionBlockRange = RandomAccessAnyView< ReactionBlock >;

  // wrap components
  mf34::wrapReactionBlock( module, viewmodule );
  mf34::wrapLegendreBlock( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ReactionBlock >(
      module,
      "any_view< MF34::ReactionBlock, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF34 section - covariances for angular distributions"
  );

  // wrap the section
  section
  .def(

    python::init< int, int, double, int,
                  std::vector< ReactionBlock >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "ltt" ), python::arg( "reactions" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number\n"
    "    zaid        the ZA  identifier\n"
    "    awr         the atomic mass ratio\n"
    "    ltt         the representation\n"
    "    reactions   the reactions (subsections) (at least 1)\n"
  )
  .def_property_readonly(

    "LTT",
    &Section::LTT,
    "the covariance representation"
  )
  .def_property_readonly(

    "representation",
    &Section::representation,
    "the covariance representation"
  )
  .def_property_readonly(

    "NMT1",
    &Section::NMT1,
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
