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

void wrapReactionBlock( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 34 >;
  using Component = Section::ReactionBlock;
  using LegendreBlock = Section::LegendreBlock;
  using LegendreBlockRange = RandomAccessAnyView< LegendreBlock >;


  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< LegendreBlock >(
      viewmodule,
      "any_view< MF34::LegendreBlock, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "ReactionBlock",
    "MF34 section - a subsection of an MF34 section"
  );

  // wrap the section
  component
  .def(

    python::init< int, int, int, int,
                  std::vector< LegendreBlock >&& >(),
    python::arg( "mt" ), python::arg( "mt1" ),
    python::arg( "nl" ), python::arg( "nl1" ),
    python::arg( "lblocks" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    mt             the section number\n"
    "    mt1            the section number of the second cross section\n"
    "    nl             the number of Legendre orders for the first cross section\n"
    "    nl1            the number of Legendre orders for the second cross section\n"
    "    lblocks        the Legendre blocks\n"
  )
  .def_property_readonly(

    "MAT1",
    [] ( const Component& self ) { return self.MAT1(); },
    "the material number for the second cross section (must be 0)"
  )
  .def_property_readonly(

    "second_material_number",
    &Component::secondMaterialNumber,
    "the material number for the second cross section (must be 0)"
  )
  .def_property_readonly(

    "MT1",
    &Component::MT1,
    "the section number for the second cross section"
  )
  .def_property_readonly(

    "second_section_number",
    &Component::secondSectionNumber,
    "the section number for the second cross section"
  )
  .def_property_readonly(

    "NL",
    &Component::NL,
    "the number of Legendre orders of the first cross section"
  )
  .def_property_readonly(

    "first_number_legendre",
    &Component::firstNumberLegendre,
    "the number of Legendre orders of the first cross section"
  )
  .def_property_readonly(

    "NL1",
    &Component::NL1,
    "the number of Legendre orders of the second cross section"
  )
  .def_property_readonly(

    "second_number_legendre",
    &Component::secondNumberLegendre,
    "the number of Legendre orders of the second cross section"
  )
  .def_property_readonly(

    "NSS",
    &Component::NSS,
    "the number of subsubsections (Legendre blocks)"
  )
  .def_property_readonly(

    "number_legendre_blocks",
    &Component::numberLegendreBlocks,
    "the number of subsubsections (Legendre blocks)"
  )
  .def_property_readonly(

    "legendre_blocks",
    [] ( const Component& self ) -> LegendreBlockRange
       { return self.legendreBlocks(); },
    "the Legendre blocks"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf34
