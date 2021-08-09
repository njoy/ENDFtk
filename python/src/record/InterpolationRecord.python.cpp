// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/InterpolationRecord.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapInterpolationRecord( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::ENDFtk::InterpolationRecord;

  // wrap the record
  python::class_< Record > component(

    module,
    "InterpolationRecord",
    "ENDF TAB2 record\n\n"
    "The interpolation record is a multi-line ENDF record containing 2 doubles\n"
    "and 4 integers on the first line, followed by interpolation information\n"
    "on the following lines."
  );

  // wrap the record
  component
  .def(

    python::init< double, double, long, long,
                  std::vector< long >&&,
                  std::vector< long >&& >(),
    python::arg( "C1" ), python::arg( "C2" ),
    python::arg( "L1" ), python::arg( "L2" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self           the record\n"
    "    C1             the double in column 1\n"
    "    C2             the double in column 2\n"
    "    L1             the integer in column 3\n"
    "    L2             the integer in column 4\n"
    "    boundaries     the interpolation range boundaries\n"
    "    interpolants   the interpolation types for each range"
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

    "NZ",
    &Record::NZ,
    "The number of points"
  );

  // add standard tab2 definitions
  addStandardInterpolationTableDefinitions< Record >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Record >( component );
}
