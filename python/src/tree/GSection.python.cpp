// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/GTape.hpp"
#include "variants.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeGSection( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::tree::GSection;


  // wrap views created by this component

  // create the tree component
  python::class_< Section > tree(

    module,
    "GSection",
    "GENDF tree section"
  );

  // wrap the tree component
  // only copy is allowed since we do not want to create this object in python
  tree
  .def(

    python::init< const Section& >(),
    python::arg( "section" ),
    "Initialise the section with another section\n\n"
    "Arguments:\n"
    "    self       the section\n"
    "    section    the section to be copied"
  )
  .def_property_readonly(

    "MAT",
    &Section::MAT,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "material_number",
    &Section::materialNumber,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "MF",
    &Section::MF,
    "The MF number of the section"
  )
  .def_property_readonly(

    "file_number",
    &Section::fileNumber,
    "The MF number of the section"
  )
  .def_property_readonly(

    "MT",
    &Section::MT,
    "The MT number of the section"
  )
  .def_property_readonly(

    "section_number",
    &Section::sectionNumber,
    "The MT number of the section"
  )
  .def(

    "parse",
    [] ( const Section& self ) -> GSectionVariant {

      int mf = self.fileNumber();
      int mt = self.sectionNumber();
      switch ( mf ) {

        case 1 : {

          switch ( mt ) {

            case 451 : return self.parse< 1, 451 >();
            default: throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " is not an official GENDF section" );
          }
        }
        case 3 : return self.parse< 3 >();
        case 5 : {

          switch ( mt ) {

            case  18 : return self.parse< 5, 18 >();
            case 455 : return self.parse< 5, 455 >();
            default: throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " is not an official GENDF section" );
          }
        }
        case 6 : return self.parse< 6 >();
        case 16 : return self.parse< 16 >();
        default: throw std::runtime_error(
                       "GENDF section from file " +  std::to_string( mf ) +
                       " cannot be parsed yet" );
      }
    },
    "Parse the section"
  )
  .def_property_readonly(

    "content",
    &Section::content,
    "The content of the section"
  )
  .def_property_readonly(

    "NC",
    &Section::NC,
    "The number of lines in this section"
  )
  .def(

    "clean",
    &Section::clean,
    "Clean up the section\n\n"
    "This function removes the sequence numbers from the section."
  );
}
