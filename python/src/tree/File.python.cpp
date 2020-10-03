// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/file/3.hpp"
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
  using SectionRange = BiDirectionalAnyView< Section >;
  using MF3 = njoy::ENDFtk::file::Type< 3 >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBiDirectionalAnyViewOf< Section >(
      module,
      "any_view< tree::Section, bidirectional >" );

  // create the tree component
  python::class_< File > tree(

    module,
    "File",
    "ENDF tree file"
  );

  // wrap the tree component
  // no __init__ since we do not want to create this object in python
  tree
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
    [] ( const File& self ) -> std::variant< MF3 > {

      switch ( self.fileNumber() ) {

        case 3 : return self.parse< 3 >();
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

//    .def("size", &File_t::size)
//    .def_property_readonly("sections",
//                           [](File_t& file) {
//                             return file | ranges::to_vector;
//                           })
//    .def_property_readonly("buffer",
//                           [](File_t& file) {
//                             return std::string(file.buffer().begin(),
//                                                file.buffer().end());
//                           })
//    .def("parse3", (File_3_t (File_t::*)() const)
//                   &File_t::parse<3>)
//    .def("parse3", (File_3_t (File_t::*)(long&) const)
//                   &File_t::parse<3>);

}
