// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/3.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_3( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 3 >;
  using DoubleRange = RandomAccessAnyView< double >;
  using LongRange = RandomAccessAnyView< long >;

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section_3",
    "MF3 - reaction cross sections"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, double, double, long,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >()
  )
  .def_property_readonly(

    "QM",
    &Section::QM
  )
  .def_property_readonly(

    "QI",
    &Section::QI
  )
  .def_property_readonly(

    "LR",
    &Section::LR
  )
  .def_property_readonly(

    "NR",
    &Section::NR
  )
  .def_property_readonly(

    "NP",
    &Section::NP
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Section& self ) -> LongRange
       { return self.interpolants(); }
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Section& self ) -> LongRange
       { return self.boundaries(); }
  )
  .def_property_readonly(

    "energies",
    [] ( const Section& self ) -> DoubleRange
       { return self.energies(); }
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Section& self ) -> DoubleRange
       { return self.crossSections(); }
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
