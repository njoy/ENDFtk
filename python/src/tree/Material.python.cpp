// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Tape.hpp"
#include "range/v3/range/operations.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeMaterial( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Material = njoy::ENDFtk::tree::Material;
  using File = njoy::ENDFtk::tree::File;
  using Section = njoy::ENDFtk::tree::Section;
  using ParsedMaterial = njoy::ENDFtk::Material;
  using FileRange = BidirectionalAnyView< File >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< File >(
      viewmodule,
      "any_view< tree::File, bidirectional >" );

  // create the tree component
  python::class_< Material > tree(

    module,
    "Material",
    "ENDF tree material"
  );

  // wrap the tree component
  // only copy is allowed since we do not want to create this object in python
  tree
  .def(

    python::init< const Material& >(),
    python::arg( "material" ),
    "Initialise the material with another material\n\n"
    "Arguments:\n"
    "    self        the material\n"
    "    material    the material to be copied"
  )
  .def_property_readonly(

    "MAT",
    &Material::MAT,
    "The MAT number of the material"
  )
  .def_property_readonly(

    "material_number",
    &Material::materialNumber,
    "The MAT number of the material"
  )
  .def(

    "has_MF",
    &Material::hasMF,
    "Return whether or not the material has a file with the given MF number\n\n"
    "Arguments:\n"
    "    self    the material\n"
    "    mf      the MF number of the file"
  )
  .def(

    "has_file",
    &Material::hasFile,
    "Return whether or not the material has a file with the given MF number\n\n"
    "Arguments:\n"
    "    self    the material\n"
    "    mf      the MF number of the file"
  )
  .def_property_readonly(

    "file_numbers",
    [] ( const Material& self ) -> std::vector< int >
       { return ranges::to< std::vector< int > >( self.fileNumbers() ); },
    "All file numbers in the material"
  )
  .def_property_readonly(

    "files",
    [] ( const Material& self ) -> FileRange
       { return self.files(); },
    "All files in the material"
  )
  .def_property_readonly(

    "content",
    &Material::content,
    "The content of the material"
  )
  .def(

    "file",
    ( File& ( Material::* )( int ) ) &Material::file,
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MF",
    ( File& ( Material::* )( int ) ) &Material::MF,
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "parse",
    [] ( const Material& self ) -> ParsedMaterial {

      return self.parse();
    },
    "Parse the material"
  )
  .def(

    "remove",
    python::overload_cast< int >( &Material::remove ),
    python::arg( "mf" ),
    "Remove the file in the material if it is present\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mf      the mf number of the file to be removed"
  )
  .def(

    "remove",
    python::overload_cast< int, int >( &Material::remove ),
    python::arg( "mf" ), python::arg( "mt" ),
    "Remove the section in the material if it is present\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mf      the mf number of the section to be removed\n"
    "    mt      the mt number of the section to be removed"
  )
  .def(

    "insert",
    [] ( Material& self, Section section )
       { self.insert( std::move( section ) ); },
    python::arg( "section" ),
    "Insert the section in the material\n\n"
    "This function inserts the section in the ENDF material tree only if a\n"
    "section with that MT number is not present yet. If the file the section is\n"
    "to be added to is missing, it is added.\n\n"
    "An exception will be thrown if the MAT number of the section does\n"
    "not match the MAT number of the file, and when a section with the\n"
    "same MT number is already present.\n\n"
    "Arguments:\n"
    "    self      the ENDF tree material\n"
    "    section   the section to be inserted"
  )
  .def(

    "insert",
    [] ( Material& self, File file )
       { self.insert( std::move( file ) ); },
    python::arg( "section" ),
    "Insert the file in the material\n\n"
    "This function inserts the file in the ENDF material tree only if a\n"
    "file with that MF number is not present yet.\n\n"
    "An exception will be thrown if the MAT number of the file does\n"
    "not match the MAT number of the file, and when a file with the\n"
    "same MF number is already present.\n\n"
    "Arguments:\n"
    "    self   the ENDF tree material\n"
    "    file   the file to be inserted"
  )
  .def(

    "insert_or_replace",
    [] ( Material& self, Section section )
       { self.insertOrReplace( std::move( section ) ); },
    python::arg( "section" ),
    "Insert or replace the section in the material\n\n"
    "This function inserts or replaces the section in the ENDF material tree.\n\n"
    "An exception will be thrown if the MAT number of the section does\n"
    "not match the MAT number of the material.\n\n"
    "Arguments:\n"
    "    self      the ENDF tree material\n"
    "    section   the section to be inserted or replaced"
  )
  .def(

    "insert_or_replace",
    [] ( Material& self, File file )
       { self.insertOrReplace( std::move( file ) ); },
    python::arg( "section" ),
    "Insert or replace the file in the material\n\n"
    "This function inserts or replaces the file in the ENDF material tree. This\n"
    "does not merge sections if the file is already present: the old file is\n"
    "removed prior to inserting the new file.\n\n"
    "An exception will be thrown if the MAT number of the file does\n"
    "not match the MAT number of the file.\n\n"
    "Arguments:\n"
    "    self   the ENDF tree material\n"
    "    file   the file to be inserted or replaced"
  );
}
