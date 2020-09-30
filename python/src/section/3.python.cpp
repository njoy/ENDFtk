// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/3.hpp"
#include "definitions.hpp"
#include "print.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_3( python::module& module ) {

  // type aliases
  using DirectoryRecord = njoy::ENDFtk::DirectoryRecord;
  using Section = njoy::ENDFtk::section::Type< 3 >;

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

    py::init< int, double, double, double, double, long,
              std::vector< long >&&, std::vector< long >&&,
              std::vector< double >&&, std::vector< double >&& >()
  )
  .def_property_readonly("MT", [](Section& type) { return type.MT(); })
  .def_property_readonly("ZA", [](Section& type) { return type.ZA(); })
  .def_property_readonly("AWR", [](Section& type) { return type.AWR(); })
  .def_property_readonly("QM", &Section::QM)
  .def_property_readonly("QI", &Section::QI)
  .def_property_readonly("LR", &Section::LR)
  .def_property_readonly("NR", &Section::NR)
  .def_property_readonly("NP", &Section::NP)
  .def_property_readonly("NC", &Section::NC)
  .def_property_readonly("interpolants",
                         [](Section& type) {
                           return type.interpolants() | ranges::to_vector;
                         })
  .def_property_readonly("boundaries",
                         [](Section& type) {
                           return type.boundaries() | ranges::to_vector;
                         })
  .def_property_readonly("energies",
                         [](Section& type) {
                           return type.energies() | ranges::to_vector;
                         })
  .def_property_readonly("crossSections",
                         [](Section& type) {
                           return type.crossSections() | ranges::to_vector;
                         })
  .def("to_string",
       [](Section& type, int MAT, int MF) {
         std::string buffer;
         auto output = std::back_inserter( buffer );
         type.print( output, MAT, MF );
         return buffer;
       });

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
