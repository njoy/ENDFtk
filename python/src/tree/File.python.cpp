// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "range/v3/range/operations.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeFile( python::module& module, python::module& viewmodule ) {

  // type aliases
  using File = njoy::ENDFtk::tree::File;
  using Section = njoy::ENDFtk::tree::Section;
  using SectionRange = BidirectionalAnyView< Section >;
  using MF1 = njoy::ENDFtk::file::Type< 1 >;
  using MF2 = njoy::ENDFtk::file::Type< 2 >;
  using MF3 = njoy::ENDFtk::file::Type< 3 >;
  using MF4 = njoy::ENDFtk::file::Type< 4 >;
  using MF5 = njoy::ENDFtk::file::Type< 5 >;
  using MF6 = njoy::ENDFtk::file::Type< 6 >;
  using MF7 = njoy::ENDFtk::file::Type< 7 >;
  using MF8 = njoy::ENDFtk::file::Type< 8 >;
  using MF9 = njoy::ENDFtk::file::Type< 9 >;
  using MF10 = njoy::ENDFtk::file::Type< 10 >;
  using MF12 = njoy::ENDFtk::file::Type< 12 >;
  using MF13 = njoy::ENDFtk::file::Type< 13 >;
  using MF14 = njoy::ENDFtk::file::Type< 14 >;
  using MF15 = njoy::ENDFtk::file::Type< 15 >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< tree::Section, bidirectional >" );

  // create the tree component
  python::class_< File > tree(

    module,
    "File",
    "ENDF tree file"
  );

  // wrap the tree component
  // only copy is allowed since we do not want to create this object in python
  tree
  .def(

    python::init< const File& >(),
    python::arg( "file" ),
    "Initialise the file with another file\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    file    the file to be copied"
  )
  .def_property_readonly(

    "MAT",
    &File::MAT,
    "The MAT number of the file"
  )
  .def_property_readonly(

    "material_number",
    &File::materialNumber,
    "The MAT number of the file"
  )
  .def_property_readonly(

    "MF",
    &File::MF,
    "The MF number of the file"
  )
  .def_property_readonly(

    "file_number",
    &File::fileNumber,
    "The MF number of the file"
  )
  .def(

    "has_MT",
    &File::hasMT,
    "Return whether or not the file has a section with the given MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section"
  )
  .def(

    "has_section",
    &File::hasSection,
    "Return whether or not the file has a section with the given MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section"
  )
  .def_property_readonly(

    "section_numbers",
    [] ( const File& self ) -> std::vector< int >
       { return ranges::to< std::vector< int > >( self.sectionNumbers() ); },
    "All section numbers in the file"
  )
  .def_property_readonly(

    "sections",
    [] ( const File& self ) -> SectionRange
       { return self.sections(); },
    "All sections in the file"
  )
  .def(

    "section",
    ( Section& ( File::* )( int ) ) &File::section,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MT",
    ( Section& ( File::* )( int ) ) &File::MT,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "parse",
    [] ( const File& self ) -> std::variant< MF1, MF2, MF3, MF4, MF5, MF6,
                                             MF7, MF8, MF9, MF10, MF12, MF13,
                                             MF14, MF15 > {

      switch ( self.fileNumber() ) {

        case 1 : return self.parse< 1 >();
        case 2 : return self.parse< 2 >();
        case 3 : return self.parse< 3 >();
        case 4 : return self.parse< 4 >();
        case 5 : return self.parse< 5 >();
        case 6 : return self.parse< 6 >();
        case 7 : return self.parse< 7 >();
        case 8 : return self.parse< 8 >();
        case 9 : return self.parse< 9 >();
        case 10 : return self.parse< 10 >();
        case 12 : return self.parse< 12 >();
        case 13 : return self.parse< 13 >();
        case 14 : return self.parse< 14 >();
        case 15 : return self.parse< 15 >();
      }
      throw std::runtime_error( "File cannot be parsed yet" );
    },
    "Parse the file"
  )
  .def_property_readonly(

    "content",
    &File::content,
    "The content of the file"
  )
  .def(

    "remove",
    &File::remove,
    python::arg( "mt" ),
    "Remove the section in the file if it is present\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mt      the mt number of the section to be removed"
  )
  .def(

    "insert",
    [] ( File& self, Section section )
       { self.insert( std::move( section ) ); },
    python::arg( "section" ),
    "Insert the section in the file\n\n"
    "This function inserts the section in the ENDF file tree only if a\n"
    "section with that MT number is not present yet.\n\n"
    "An exception will be thrown if the MAT and MF number of the section do\n"
    "not match the MAT and MF number of the file, and when a section with the\n"
    "same MT number is already present.\n\n"
    "Arguments:\n"
    "    self      the ENDF tree file\n"
    "    section   the section to be inserted"
  )
  .def(

    "insert_or_replace",
    [] ( File& self, Section section )
       { self.insertOrReplace( std::move( section ) ); },
    python::arg( "section" ),
    "Insert or replace the section in the file\n\n"
    "This function inserts or replaces the section in the ENDF file tree.\n\n"
    "An exception will be thrown if the MAT and MF number of the section do\n"
    "not match the MAT and MF number of the file.\n\n"
    "Arguments:\n"
    "    self      the ENDF tree file\n"
    "    section   the section to be inserted or replaced"
  );
}
