// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "print.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDirectoryRecord( python::module& module ) {

  // type aliases
  using Record = njoy::ENDFtk::DirectoryRecord;

  // wrap the record
  python::class_< Record >(

    module,
    "DirectoryRecord",
    "Directory record"
  )
  .def(

    python::init< long, long, long, long >(),
    python::arg( "mf" ), python::arg( "mt" ),
    python::arg( "nc" ), python::arg( "mod" ),
    "Initialise the directory record\n\n"
    "Arguments:\n"
    "    self   the directory object\n"
    "    mf     the MF number\n"
    "    mt     the MT number\n"
    "    nc     the number of lines that make up this section\n"
    "    mod    the modification number"
  )
  .def_property_readonly(

    "MF",
    [] ( const Record& self ) { return self.MF(); },
    "The MF number"
  )
  .def_property_readonly(

    "MT",
    [] ( const Record& self ) { return self.MT(); },
    "the MT number"
  )
  .def_property_readonly(

    "NC",
    [] ( const Record& self ) { return self.NC(); },
    "The number of lines NC that make up this section"
  )
  .def_property_readonly(

    "MOD",
    [] ( const Record& self ) { return self.MOD(); },
    "The modification number"
  )
  .def(

    "to_string",
    [] ( const Record& self, long mat ) { return print( self, mat, 1, 451 ); },
    "Return the string representation of the directory record\n\n"
    "Arguments:\n"
    "    self   the directory object\n"
    "    mat    the MAT number to be used"
  );
}
