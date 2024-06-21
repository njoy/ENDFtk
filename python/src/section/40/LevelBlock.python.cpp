// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/40.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf40 {

void wrapLevelBlock( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 40 >;
  using Component = Section::LevelBlock;
  using ReactionBlock = njoy::ENDFtk::section::ReactionBlock;
  using ReactionBlockRange = RandomAccessAnyView< ReactionBlock >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "LevelBlock",
    "MF40 section - a subsection of an MF40 section"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int, int,
                  std::vector< ReactionBlock >&& >(),
    python::arg( "qm" ), python::arg( "qi" ),
    python::arg( "izap" ), python::arg( "lfs" ),
    python::arg( "reactions" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    qm            the mass difference Q-value\n"
    "    qi            the reaction Q-value\n"
    "    izap          the product identifier (ZA)\n"
    "    lfs           the excited level of the product\n"
    "    reactions     the reaction blocks\n"
  )
  .def_property_readonly(

    "QM",
    &Component::QM,
    "the mass-difference Q-value"
  )
  .def_property_readonly(

    "mass_difference_q_value",
    &Component::massDifferenceQValue,
    "the mass-difference Q-value"
  )
  .def_property_readonly(

    "QI",
    &Component::QI,
    "the reaction Q-value"
  )
  .def_property_readonly(

    "reaction_q_value",
    &Component::reactionQValue,
    "the reaction Q-value"
  )
  .def_property_readonly(

    "IZAP",
    &Component::IZAP,
    "the product ZA identifier"
  )
  .def_property_readonly(

    "product_identifier",
    &Component::productIdentifier,
    "the product ZA identifier"
  )
  .def_property_readonly(

    "LFS",
    &Component::LFS,
    "the level number of the product"
  )
  .def_property_readonly(

    "excited_level",
    &Component::excitedLevel,
    "the level number of the product"
  )
  .def_property_readonly(

    "NL",
    &Component::NL,
    "the number of reaction blocks"
  )
  .def_property_readonly(

    "number_reactions",
    &Component::numberReactions,
    "the number of reaction blocks"
  )
  .def_property_readonly(

    "reaction_blocks",
    [] ( const Component& self ) -> ReactionBlockRange
       { return self.reactionBlocks(); },
    "the reaction blocks"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf40
