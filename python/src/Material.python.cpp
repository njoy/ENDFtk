// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

// local includes
#include "views.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/toMaterial.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMaterial( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Material = njoy::ENDFtk::Material;
  using FileVariant = Material::FileVariant;
  using FileVariantRange = BidirectionalAnyView< FileVariant >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< FileVariant >(
      viewmodule,
      "any_view< Material::FileVariant, bidirectional >" );

  // create the section
  python::class_< Material > material(

    module,
    "Material",
    "Material - nuclear data for a single material"
  );

  // wrap the section
  material
  .def_property_readonly(

    "MAT",
    &Material::MAT,
    "The material number"
  )
  .def_property_readonly(

    "material_number",
    &Material::materialNumber,
    "The material number"
  )
  .def(

    "has_MF",
    &Material::hasMF,
    python::arg( "mf" ),
    "Return whether or not the material has a file with the given MF number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mf      the MF number of the file"
  )
  .def(

    "has_file",
    &Material::hasFile,
    python::arg( "mf" ),
    "Return whether or not the material has a file with the given MF number\n\n"
    "Arguments:\n"
    "    self    the file\n"
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

    "MFs",
    [] ( const Material& self ) -> FileVariantRange
       { return self.MFs(); },
    "The files defined in the material"
  )
  .def_property_readonly(

    "files",
    [] ( const Material& self ) -> FileVariantRange
       { return self.files(); },
    "The files defined in the material"
  )
  .def(

    "MF",
    &Material::MF,
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "file",
    &Material::file,
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def_static(

    "from_string",
    [] ( const std::string& material ) -> Material {

      auto begin = material.begin();
      auto end = material.end();
      long lineNumber = 1;
      njoy::ENDFtk::StructureDivision division( begin, end, lineNumber);

      return njoy::ENDFtk::Material( division, begin, end, lineNumber );
    },
    python::arg( "material" ),
    "Read the material from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "material\n\n"
    "Arguments:\n"
    "    material    the string representing the material"
  )
  .def(

    "to_string",
    [] ( const Material& self ) -> std::string {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      self.print( output );
      return buffer;
    },
    "The string representation of the material\n\n"
    "Arguments:\n"
    "    self    the material"
  )
  .def(

    "to_tree",
    [] ( const Material& self ) -> njoy::ENDFtk::tree::Material
       { return njoy::ENDFtk::tree::toMaterial( self ); },
    "Return the ENDF tree representation of the material\n\n"
    "Arguments:\n"
    "    self    the file"
  );
}
