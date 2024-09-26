// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "ENDFtk/tree/updateDirectory.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeTape( python::module& module, python::module& viewmodule ) {

  // type aliases
  using TapeIdentification = njoy::ENDFtk::TapeIdentification;
  using Tape = njoy::ENDFtk::tree::Tape;
  using ParsedMaterial = njoy::ENDFtk::Material;
  using Material = njoy::ENDFtk::tree::Material;
  using MaterialRange = BidirectionalAnyView< Material >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Material >(
      viewmodule,
      "any_view< tree::Material, bidirectional >" );

  // create the tree component
  python::class_< Tape > tree(

    module,
    "Tape",
    "ENDF tape"
  );

  // wrap the tree component
  tree
  .def(

    python::init( [] ( TapeIdentification id )
                     { return Tape( std::move( id ) ); } ),
    python::arg( "id" ),
    "Initialise the tape\n\n"
    "Arguments:\n"
    "    self   the tape\n"
    "    id     the tape identifier"
  )
  .def(

    python::init< std::string >(),
    python::arg( "content" ),
    "Initialise the tape\n\n"
    "Arguments:\n"
    "    self       the tape\n"
    "    content    the content of the tape"
  )
  .def(

    python::init< const Tape& >(),
    python::arg( "tape" ),
    "Initialise the tape\n\n"
    "Arguments:\n"
    "    self    the tape\n"
    "    tape    the tape to be copied"
  )
  .def(

    "has_MAT",
    &Tape::hasMAT,
    "Return whether or not the tape has a material with the given MAT number\n\n"
    "Arguments:\n"
    "    self    the tape\n"
    "    mat     the MAT number of the material"
  )
  .def(

    "has_material",
    &Tape::hasMaterial,
    "Return whether or not the tape has a material with the given MAT number\n\n"
    "Arguments:\n"
    "    self    the tape\n"
    "    mat     the MAT number of the material"
  )
  .def_property_readonly(

    "tape_id",
    &Tape::TPID,
    "The tape identification (the first line in the file)"
  )
  .def_property_readonly(

    "TPID",
    &Tape::TPID,
    "The tape identification (the first line in the file)"
  )
  .def_property_readonly(

    "material_numbers",
    &Tape::materialNumbers,
    "All unique material numbers in the tape"
  )
  .def_property_readonly(

    "materials",
    [] ( Tape& self ) -> MaterialRange
       { return self.materials(); },
    "All materials in the tape"
  )
  .def(

    "MAT",
    [] ( Tape& self, int mat ) -> MaterialRange
       { return self.MAT( mat ); },
    python::arg( "mat" ),
    "Return the material(s) with the requested MAT number\n\n"
    "This function returns  a sequence of materials since a tape can contain multiple\n"
    "instances of the same material (e.g. at different temperatures).\n\n"
    "Arguments:\n"
    "    self    the tape\n"
    "    mat     the MAT number of the material to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "material",
    [] ( Tape& self, int mat ) -> MaterialRange
       { return self.MAT( mat ); },
    python::arg( "mat" ),
    "Return the material(s) with the requested MAT number\n\n"
    "This function returns  a sequence of materials since a tape can contain multiple\n"
    "instances of the same material (e.g. at different temperatures).\n\n"
    "Arguments:\n"
    "    self    the tape\n"
    "    mat     the MAT number of the material to be returned",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "content",
    &Tape::content,
    "The content of the tape"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Tape {

      return Tape( string );
    },
    python::arg( "string" ),
    "Read a tape from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "tape\n\n"
    "Arguments:\n"
    "    string    the content of the tape"
  )
  .def_static(

    "from_file",
    [] ( const std::string& filename ) -> Tape {

      return njoy::ENDFtk::tree::fromFile( filename );
    },
    python::arg( "filename" ),
    "Read a tape from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "tape\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  )
  .def(

    "to_file",
    [] ( const Tape& self, const std::string& filename ) {

      std::ofstream out( filename );
      out << self.content();
      out.close();
    },
    python::arg( "filename" ),
    "Write the tape to a file\n\n"
    "Arguments:\n"
    "    self        the tape\n"
    "    filename    the file name and path"
  )
  .def(

    "remove",
    &Tape::remove,
    python::arg( "mat" ),
    "Remove all materials with the given MAT number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree file\n"
    "    mat     the mat number of the materials to be removed"
  )
  .def(

    "insert",
    [] ( Tape& self, Material material ) { self.insert( std::move( material ) ); },
    python::arg( "material" ),
    "Insert the material in the tape\n\n"
    "This function inserts the material in the ENDF tape tree. If one or more\n"
    "materials are already present, the new material is inserted after the\n"
    "materials that are already there.\n\n"
    "Arguments:\n"
    "    self       the tape\n"
    "    material   the material to be inserted"
  )
  .def(

    "insert",
    [] ( Tape& self, const ParsedMaterial& material ) { self.insert( material ); },
    python::arg( "material" ),
    "Insert the material in the tape\n\n"
    "This function inserts the material in the ENDF tape tree. If one or more\n"
    "materials are already present, the new material is inserted after the\n"
    "materials that are already there.\n\n"
    "Arguments:\n"
    "    self       the tape\n"
    "    material   the material to be inserted"
  )
  .def(

    "replace",
    [] ( Tape& self, Material material ) { self.replace( std::move( material ) ); },
    python::arg( "material" ),
    "Insert or replace the material in the tape\n\n"
    "This function inserts the material in the ENDF tape tree. If one or more\n"
    "materials are already present, the old materials are removed before inserting\n"
    "the new material.\n\n"
    "Arguments:\n"
    "    self       the tape\n"
    "    material   the material to be inserted"
  )
  .def(

    "replace",
    [] ( Tape& self, const ParsedMaterial& material ) { self.replace( material ); },
    python::arg( "material" ),
    "Insert or replace the material in the tape\n\n"
    "This function inserts the material in the ENDF tape tree. If one or more\n"
    "materials are already present, the old materials are removed before inserting\n"
    "the new material.\n\n"
    "Arguments:\n"
    "    self       the tape\n"
    "    material   the material to be inserted"
  )
  .def(

    "update_directory",
    [] ( Tape& self, bool copy_mod = false )
       { njoy::ENDFtk::tree::updateDirectory( self, copy_mod ); },
    python::arg( "copy_mod" ) = false,
    "Update the MF1 MT451 directory for all materials in the tape\n\n"
    "An exception will be thrown if a material in the tape has no MF1 MT451\n"
    "section is not present, or if there was an issue parsing it.\n\n"
    "Arguments:\n"
    "    self        the tape\n"
    "    copy_mod    copy mod numbers if available (default is False)\n"
  )
  .def(

    "clean",
    &Tape::clean,
    "Clean up the tape\n\n"
    "This function removes the sequence numbers from the tape."
  );
}
