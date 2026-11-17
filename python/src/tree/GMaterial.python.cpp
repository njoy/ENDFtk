// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/GMaterial.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeGMaterial( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Material = njoy::ENDFtk::tree::GMaterial;
  using File = njoy::ENDFtk::tree::GFile;
  using FileRange = BidirectionalAnyView< File >;

  // wrap views created by this tree component
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< File >(
      viewmodule,
      "any_view< tree::GFile, bidirectional >" );

  // create the tree component
  python::class_< Material > tree(

    module,
    "GMaterial",
    "GENDF tree material"
  );

  // wrap the tree component
  tree
  .def(

    python::init< unsigned int >(),
    python::arg( "mat" ),
    "Initialise an empty material with its MAT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mat     the MAT number of the material\n"
  )
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
  .def(

    "has_MF_MT",
    &Material::hasMFMT,
    "Return whether or not the material has a section with the given MF and MT "
    "number\n\n"
    "Arguments:\n"
    "    self    the material\n"
    "    mf      the MF number of the section\n"
    "    mt      the MT number of the section"
  )
  .def(

    "has_section",
    &Material::hasSection,
    "Return whether or not the material has a file with the given MF number\n\n"
    "Arguments:\n"
    "    self    the material\n"
    "    mf      the MF number of the section\n"
    "    mt      the MT number of the section"
  )
  .def_property_readonly(

    "file_numbers",
    [] ( const Material& self ) -> IntList
       { return self.fileNumbers(); },
    "All file numbers in the material"
  )
  .def_property_readonly(

    "files",
    [] ( Material& self ) -> FileRange
       { return self.files(); },
    "All files in the material"
  )
  .def_property_readonly(

    "content",
    &Material::content,
    "The content of the material"
  )
  .def(

    "file",
    python::overload_cast< int >( &Material::file, python::const_ ),
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MF",
    python::overload_cast< int >( &Material::MF, python::const_ ),
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "section",
    python::overload_cast< int, int >( &Material::section, python::const_ ),
    python::arg( "mf" ), python::arg( "mt" ),
    "Return the section with the requested MF and MT number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the section to be returned\n",
    "    mt      the Mt number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MFMT",
    python::overload_cast< int, int >( &Material::MFMT, python::const_ ),
    python::arg( "mf" ), python::arg( "mt" ),
    "Return the section with the requested MF and MT number\n\n"
    "Arguments:\n"
    "    self    the ENDF tree material\n"
    "    mf      the MF number of the section to be returned\n",
    "    mt      the Mt number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "clean",
    &Material::clean,
    "Clean up the material\n\n"
    "This function removes the sequence numbers from the material."
  );
}
