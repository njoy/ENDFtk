// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Tape.hpp"
#include "range/v3/utility/iterator.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeMaterial( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Tape = njoy::ENDFtk::tree::Tape< std::string >;
  using Material = Tape::Material_t;
  using ParsedMaterial = njoy::ENDFtk::Material;
  using File = Material::File_t;
  using FileRange = BidirectionalAnyView< File >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< File >(
      viewmodule,
      "any_view< tree::File, bidirectional >" );

  // create the tree component
  python::class_< Material > tree(

    module,
    "Material",
    "ENDF tree material"
  );

  // wrap the tree component
  // only copy is allowed since we do not want to create this object in python
  tree
  .def(

    python::init< const Material& >(),
    python::arg( "material" ),
    "Initialise the material with another material\n\n"
    "Arguments:\n"
    "    self        the material\n"
    "    material    the material to be copied"
  )
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
  .def_property_readonly(

    "file_numbers",
    [] ( const Material& self ) -> std::vector< int >
       { return self.fileNumbers(); },
    "All file numbers in the material"
  )
  .def_property_readonly(

    "files",
    [] ( const Material& self ) -> FileRange
       { return self.files(); },
    "All files in the material"
  )
  .def_property_readonly(

    "content",
    [] ( const Material& self ) -> std::string
       { return self.buffer(); },
    "The content of the material"
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
  )
  .def(

    "parse",
    [] ( const Material& self ) -> ParsedMaterial {

      return self.parse();
    },
    "Parse the material"
  );
}
