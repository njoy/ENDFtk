// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/makeTape.hpp"
#include "header-utilities/slurpFileToMemory.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeTape( python::module& module ) {

  // type aliases
  using Tape = njoy::ENDFtk::tree::Tape< std::string >;

  // wrap views created by this tree component

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
  .def_static(

    "from_file",
    [] ( const std::string& filename ) -> Tape {

      std::string content = njoy::utility::slurpFileToMemory( filename );
      std::cout << "read string:" << std::endl;
      std::cout << content << std::endl;
      std::cout << "creating tape" << std::endl;
      Tape tape = njoy::ENDFtk::tree::makeTape( std::move( content ) );
      std::cout << "created tape" << std::endl;
      return tape;
    },
    "Read a tape from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "tape\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  );

//    .def("size", &Tape_t::size)
//    .def_property_readonly("materials",
//                           [](Tape_t& tape) {
//                             return tape | ranges::to_vector;
//                           });

}
