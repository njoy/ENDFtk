// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "range/v3/range/operations.hpp"
#include "views.hpp"
#include "variants.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeSection( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::tree::Section;


  // wrap views created by this component

  // create the tree component
  python::class_< Section > tree(

    module,
    "Section",
    "ENDF tree section"
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
    [] ( const Section& self ) -> SectionVariant {

      int mf = self.fileNumber();
      int mt = self.sectionNumber();
      switch ( mf ) {

        case 1 : {

          switch ( mt ) {

            case 451 : return self.parse< 1, 451 >();
            case 452 : return self.parse< 1, 452 >();
            case 455 : return self.parse< 1, 455 >();
            case 456 : return self.parse< 1, 456 >();
            case 458 : return self.parse< 1, 458 >();
            case 460 : return self.parse< 1, 460 >();
            default: throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " is not an official ENDF section" );
          }
        }
        case 2 : {

          switch ( mt ) {

            case 151 : return self.parse< 2, 151 >();
            case 152 : return self.parse< 2, 152 >();
            case 153 : throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " cannot be parsed yet" );
            default : throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " is not an official ENDF section" );
          }
        }
        case 3 : return self.parse< 3 >();
        case 4 : return self.parse< 4 >();
        case 5 : return self.parse< 5 >();
        case 6 : return self.parse< 6 >();
        case 7 : {

          switch ( mt ) {

            case 2 : return self.parse< 7, 2 >();
            case 4 : return self.parse< 7, 4 >();
            default: throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " is not an official ENDF section" );
          }
        }
        case 8 : {

          switch ( mt ) {

            case 454 : return self.parse< 8, 454 >();
            case 457 : return self.parse< 8, 457 >();
            case 459 : return self.parse< 8, 459 >();
            default : throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " is not an official ENDF section" );
          }
        }
        case 9 : return self.parse< 9 >();
        case 10 : return self.parse< 10 >();
        case 12 : return self.parse< 12 >();
        case 13 : return self.parse< 13 >();
        case 14 : return self.parse< 14 >();
        case 15 : return self.parse< 15 >();
        case 23 : return self.parse< 23 >();
        case 26 : return self.parse< 26 >();
        case 27 : return self.parse< 27 >();
        case 28 : return self.parse< 28 >();
        case 31 : return self.parse< 31 >();
        case 32 : {

          switch ( mt ) {

            case 151 : return self.parse< 32, 151 >();
            default : throw std::runtime_error(
                           "Section " + std::to_string( mt ) + " from file " +
                           std::to_string( mf ) +
                           " is not an official ENDF section" );
          }
        }
        case 33 : return self.parse< 33 >();
        case 34 : return self.parse< 34 >();
        case 35 : return self.parse< 35 >();
        case 40 : return self.parse< 40 >();
        default: throw std::runtime_error(
                       "Section from file " +  std::to_string( mf ) +
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
