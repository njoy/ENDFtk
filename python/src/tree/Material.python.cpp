// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Material.hpp"
#include "range/v3/utility/iterator.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeMaterial( python::module& module ) {

  // type aliases
  using BufferIterator = ranges::iterator_t< const std::string >;
  using Material = njoy::ENDFtk::tree::Material< BufferIterator >;
  using File = njoy::ENDFtk::tree::File< BufferIterator >;

  // wrap views created by this tree component

  // create the tree component
  python::class_< Material > tree(

    module,
    "Material",
    "ENDF tree material"
  );

  // wrap the tree component
  // no __init__ since we do not want to create this object in python
  tree
  .def_property_readonly(

    "MAT",
    &Material::MAT,
    "The MAT number of the material"
  )
  .def_property_readonly(

    "material_number",
    &Material::materialNumber,
    "The MAT number of the material"
  )
  .def(

    "has_MF",
    &Material::hasMF,
    "Return whether or not the material has a file with the given MF number\n\n"
    "Arguments:\n"
    "    self    the material\n"
    "    mf      the MF number of the file"
  )
  .def(

    "has_file",
    &Material::hasFile,
    "Return whether or not the material has a file with the given MF number\n\n"
    "Arguments:\n"
    "    self    the material\n"
    "    mf      the MF number of the file"
  )
  .def(

    "file",
    ( File& ( Material::* )( int ) ) &Material::file,
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MF",
    ( File& ( Material::* )( int ) ) &Material::MF,
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  );

//    .def("size", &Material_t::size)
//    .def("MF", (File_t& (Material_t::*)(int))
//               &Material_t::MF)
//    .def_property_readonly("files",
//                           [](Material_t& matl) {
//                             return matl | ranges::to_vector;
//                           });

}
