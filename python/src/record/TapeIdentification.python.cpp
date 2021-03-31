// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/TapeIdentification.hpp"
#include "print.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTapeIdentification( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::ENDFtk::TapeIdentification;

  // wrap the record
  python::class_< Record >(

    module,
    "TapeIdentification",
    "Tape identification"
  )
  .def(

    python::init< std::string&& >(),
    python::arg( "text" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self   the tape identifier\n"
    "    text   the tape identification"
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

    "text",
    ( std::string& ( Record::* )() ) &Record::text,
    "The tape indentification"
  )
  .def(

    "to_string",
    [] ( const Record& self ) { return print( self, 1, 0, 0 ); },
    "Return the string representation of the tape identification\n\n"
    "Arguments:\n"
    "    self   the record"
  );
}
