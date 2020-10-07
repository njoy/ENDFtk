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
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self   the record\n"
    "    mf     the MF number\n"
    "    mt     the MT number\n"
    "    nc     the number of lines that make up this section\n"
    "    mod    the modification number"
  )
  .def(

    python::init< const Record& >(),
    python::arg( "record" ),
    "Initialise the record with another record\n\n"
    "Arguments:\n"
    "    self      the record\n"
    "    record    the record to be copied"
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
    "The number of lines NC that make up this record"
  )
  .def_property_readonly(

    "MOD",
    [] ( const Record& self ) { return self.MOD(); },
    "The modification number"
  )
  .def(

    "to_string",
    [] ( const Record& self, long mat ) { return print( self, mat, 1, 451 ); },
    "Return the string representation of the record\n\n"
    "Arguments:\n"
    "    self   the record\n"
    "    mat    the MAT number to be used"
  )
  .def(

    "__eq__",
    [] ( const Record& self, const Record& right )
       { return ( self.MF() == right.MF() ) and\
                ( self.MT() == right.MT() ) and
                ( self.NC() == right.NC() ) and
                ( self.MOD() == right.MOD() ); },
    "Compare two records\n\n"
    "Arguments:\n"
    "    self     the record\n"
    "    right    the record on the right"
  );
}
