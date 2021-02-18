// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/9.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf9 {

  // declarations - components
  void wrapReactionProduct( python::module&, python::module& );
}

void wrapSection_9( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 9 >;
  using ReactionProduct = Section::ReactionProduct;
  using ReactionProductRange = RandomAccessAnyView< ReactionProduct >;

  // wrap components
  mf9::wrapReactionProduct( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ReactionProduct >(
      viewmodule,
      "any_view< MF9::ReactionProduct, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF9 section - multiplicities for radioactive nuclide production"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, long,
                  std::vector< ReactionProduct >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "lis" ), python::arg( "multiplicities" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self             the section\n"
    "    mt               the MT number\n"
    "    zaid             the ZA  identifier\n"
    "    awr              the atomic mass ratio\n"
    "    lis              the target's excited level\n"
    "    multiplicities   the multiplicities for every state"
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

    "reaction_products",
    [] ( const Section& self ) -> ReactionProductRange
       { return self.reactionProducts(); },
    "The reaction product data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
