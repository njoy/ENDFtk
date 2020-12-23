// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/file/3.hpp"
#include "ENDFtk/file/4.hpp"
#include "ENDFtk/file/5.hpp"
#include "ENDFtk/file/6.hpp"
#include "ENDFtk/file/12.hpp"
#include "ENDFtk/file/13.hpp"
#include "range/v3/utility/iterator.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeFile( python::module& module ) {

  // type aliases
  using Tape = njoy::ENDFtk::tree::Tape< std::string >;
  using Material = Tape::Material_t;
  using File = Material::File_t;
  using Section = File::Section_t;
  using SectionRange = BidirectionalAnyView< Section >;
  using MF1 = njoy::ENDFtk::file::Type< 1 >;
  using MF2 = njoy::ENDFtk::file::Type< 2 >;
  using MF3 = njoy::ENDFtk::file::Type< 3 >;
  using MF4 = njoy::ENDFtk::file::Type< 4 >;
  using MF5 = njoy::ENDFtk::file::Type< 5 >;
  using MF6 = njoy::ENDFtk::file::Type< 6 >;
  using MF7 = njoy::ENDFtk::file::Type< 7 >;
  using MF8 = njoy::ENDFtk::file::Type< 8 >;
  using MF12 = njoy::ENDFtk::file::Type< 12 >;
  using MF13 = njoy::ENDFtk::file::Type< 13 >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      module,
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
       { return self.sectionNumbers(); },
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
                                             MF7, MF8, MF12, MF13 > {

      switch ( self.fileNumber() ) {

        case 3 : return self.parse< 3 >();
        case 4 : return self.parse< 4 >();
        case 5 : return self.parse< 5 >();
        case 6 : return self.parse< 6 >();
        case 12 : return self.parse< 12 >();
        case 13 : return self.parse< 13 >();
      }
      throw std::runtime_error( "File cannot be parsed yet" );
    },
    "Parse the file"
  )
  .def_property_readonly(

    "content",
    [] ( const File& self ) -> std::string
       { return self.buffer(); },
    "The content of the file"
  );
}
