// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/section/1.hpp"
#include "ENDFtk/section/2.hpp"
#include "ENDFtk/section/3.hpp"
#include "range/v3/utility/iterator.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeSection( python::module& module ) {

  // type aliases
  using Tape = njoy::ENDFtk::tree::Tape< std::string >;
  using Material = Tape::Material_t;
  using File = Material::File_t;
  using Section = File::Section_t;
  using MF1MT451 = njoy::ENDFtk::section::Type< 1, 451 >;
  using MF2MT151 = njoy::ENDFtk::section::Type< 2, 151 >;
  using MF2MT152 = njoy::ENDFtk::section::Type< 2, 152 >;
  using MF3MTxxx = njoy::ENDFtk::section::Type< 3 >;

  // wrap views created by this component

  // create the tree component
  python::class_< Section > tree(

    module,
    "Section",
    "ENDF tree section"
  );

  // wrap the tree component
  // no __init__ since we do not want to create this object in python
  tree
  .def_property_readonly(

    "MAT",
    &Section::MAT,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "material_number",
    &Section::materialNumber,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "MF",
    &Section::MF,
    "The MF number of the section"
  )
  .def_property_readonly(

    "file_number",
    &Section::fileNumber,
    "The MF number of the section"
  )
  .def_property_readonly(

    "MT",
    &Section::MT,
    "The MT number of the section"
  )
  .def_property_readonly(

    "section_number",
    &Section::sectionNumber,
    "The MT number of the section"
  )
  .def(

    "parse",
    [] ( const Section& self ) -> std::variant< MF1MT451, MF2MT151, MF2MT152,
                                                MF3MTxxx > {

      switch ( self.fileNumber() ) {

        case 1 : {

          switch ( self.sectionNumber() ) {

            case 451 : return self.parse< 1, 451 >();
          }
        }
        case 2 : {

          switch ( self.sectionNumber() ) {

            case 151 : return self.parse< 2, 151 >();
            case 152 : return self.parse< 2, 152 >();
          }
        }
        case 3 : return self.parse< 3 >();
      }
      throw std::runtime_error( "Section cannot be parsed yet" );
    },
    "Parse the section"
  )
  .def_property_readonly(

    "content",
    [] ( const Section& self ) -> std::string
       { return self.buffer(); },
    "The content of the section"
  );
}
