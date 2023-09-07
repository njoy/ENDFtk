// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/ControlRecord.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapControlRecord( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::ENDFtk::ControlRecord;

  // wrap the record
  python::class_< Record > component(

    module,
    "ControlRecord",
    "ENDF CONT record\n\n"
    "The control record is a single line record consisting of 2 doubles and\n"
    "4 integer values."
  );

  // wrap the record
  component
  .def(

    python::init< double, double, long, long, long, long >(),
    python::arg( "C1" ), python::arg( "C2" ),
    python::arg( "L1" ), python::arg( "L2" ),
    python::arg( "N1" ), python::arg( "N2" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self   the record\n"
    "    C1     the double in column 1\n"
    "    C2     the double in column 2\n"
    "    L1     the integer in column 3\n"
    "    L2     the integer in column 4\n"
    "    N1     the integer in column 5\n"
    "    N2     the integer in column 6"
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

    "C1",
    [] ( const Record& self ) { return self.C1(); },
    "The double in column 1"
  )
  .def_property_readonly(

    "C2",
    [] ( const Record& self ) { return self.C2(); },
    "The double in column 2"
  )
  .def_property_readonly(

    "L1",
    [] ( const Record& self ) { return self.L1(); },
    "The integer in column 3"
  )
  .def_property_readonly(

    "L2",
    [] ( const Record& self ) { return self.L2(); },
    "The integer in column 4"
  )
  .def_property_readonly(

    "N1",
    [] ( const Record& self ) { return self.N1(); },
    "The integer in column 5"
  )
  .def_property_readonly(

    "N2",
    [] ( const Record& self ) { return self.N2(); },
    "The integer in column 6"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Record >( component );
}
