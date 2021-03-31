// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/makeTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeTape( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Tape = njoy::ENDFtk::tree::Tape< std::string >;
  using Material = Tape::Material_t;
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
    [] ( const Tape& self ) -> MaterialRange
       { return self.materials(); },
    "All materials in the tape"
  )
  .def(

    "MAT",
    [] ( const Tape& self, int mat )
       -> std::variant< std::reference_wrapper< const Material >, MaterialRange >
       {
         if ( self.numberMAT( mat ) == 1 ) {

           return self.MAT( mat ).front();
         }
         return self.MAT( mat ); },
    "Return the material(s) with the requested MAT number\n\n"
    "This function returns either a single material (if only a single material\n"
    "is present) or a sequence of materials (if more than one material is\n"
    "present) since a tape can contain multiple instances of the same material\n"
    "(e.g. at different temperatures).\n\n"
    "Arguments:\n"
    "    self    the tape\n"
    "    mat     the MAT number of the material to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "material",
    [] ( const Tape& self, int mat )
       -> std::variant< std::reference_wrapper< const Material >, MaterialRange >
       {
         if ( self.numberMaterial( mat ) == 1 ) {

           return self.material( mat ).front();
         }
         return self.material( mat ); },
    "Return the material(s) with the requested MAT number\n\n"
    "This function returns either a single material (if only a single material\n"
    "is present) or a sequence of materials (if more than one material is\n"
    "present) since a tape can contain multiple instances of the same material\n"
    "(e.g. at different temperatures).\n\n"
    "Arguments:\n"
    "    self    the tape\n"
    "    mat     the MAT number of the material to be returned",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "content",
    [] ( const Tape& self ) -> std::string
       { return self.buffer(); },
    "The content of the tape"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Tape {

      return njoy::ENDFtk::tree::makeTape( std::string( string ) );
    },
    "Read a tape from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "tape\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  )
  .def_static(

    "from_file",
    [] ( const std::string& filename ) -> Tape {

      return njoy::ENDFtk::tree::fromFile( filename );
    },
    "Read a tape from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "tape\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  );
}
