// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section/1/451.hpp"
#include "views.hpp"
#include "print.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_1_451( python::module& module ) {

  // type aliases
  using DirectoryRecord = njoy::ENDFtk::DirectoryRecord;
  using Section = njoy::ENDFtk::section::Type< 1, 451 >;

  // wrap some basic views
  wrapAnyViewOf< DirectoryRecord >( module, "any_view< DirectoryRecord, random_access >" );

  // wrap the section
  python::class_< Section >(

    module,
    "Section_1_451",
    "MF1 MT451 - descriptive data and directory"
  )
  .def(

    python::init< double, double, int, int, int, int,
                  double, double, int, int, int,
                  double, double, int, int, int,
                  double, int,
                  const std::string&,
                  std::vector< DirectoryRecord >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lrp" ),
    python::arg( "lfi" ), python::arg( "nlib" ), python::arg( "nmod" ),
    python::arg( "elis" ), python::arg( "sta" ), python::arg( "lis" ),
    python::arg( "liso" ), python::arg( "nfor" ), python::arg( "awi" ),
    python::arg( "emax" ), python::arg( "lrel" ), python::arg( "nsub" ),
    python::arg( "nver" ), python::arg( "temp" ), python::arg( "ldrv" ),
    python::arg( "description" ), python::arg( "index" ),
    "Initialise the MF1 MT451 section\n\n"
    "Arguments:\n"
    "    string    the string representation of a level number (case \n"
    "              insensitive)"
  )
  .def_property_readonly(

    "LRP",
    &Section::LRP,
    "The resonance parameter flag"
  )
  .def_property_readonly(

    "MT",
    [] ( const Section& section ) { return section.MT(); },
    "The MT number of the section"
  )
  .def_property_readonly(

    "sectionNumber",
    [] ( const Section& section ) { return section.sectionNumber(); },
    "The MT number of the section"
  )
  .def_property_readonly(

    "AWR",
    [] ( const Section& section ) { return section.AWR(); },
    "The atomic weight ratio for the section"
  )
  .def_property_readonly(

    "atomicWeightRatio",
    [] ( const Section& section ) { return section.atomicWeightRatio(); },
    "The atomic weight ratio for the section"
  )
  .def_property_readonly(

    "ZA",
    [] ( const Section& section ) { return section.ZA(); },
    "The ZA identifier for the section"
  )
  .def(

    "to_string",
    [] ( const Section& self, long mat )
       { return print( self, mat, 1 ); },
    "Return the string representation of the section\n\n"
    "Arguments:\n"
    "    self   the directory object\n"
    "    mat    the MAT number to be used"
  );
}
