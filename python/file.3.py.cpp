#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ENDFtk.hpp"

namespace py = pybind11;
using namespace njoy::ENDFtk;

void py_file_3(py::module &m) {

  using namespace file;
  using Section_3_t = section::Type< 3 >;
  using Type_3_t = file::Type< 3 >;

  py::class_< Type_3_t >(m, "File3")
    .def( py::init< std::vector< Section_3_t >&& >() )
    .def_property_readonly("sections", 
                           [](Type_3_t& type) {
                             return type.sections() | ranges::to_vector;
                           })
    .def("to_string",
         [](Type_3_t& type, int MAT) {
           std::string buffer;
           auto output = std::back_inserter( buffer );
           type.print( output, MAT );
           return buffer;
         });

}
