// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

// local includes
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/toMaterial.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMaterial( python::module& module, python::module& ) {

  // type aliases
  using Material = njoy::ENDFtk::Material;
  using MF1 = njoy::ENDFtk::file::Type< 1 >;
  using MF2 = njoy::ENDFtk::file::Type< 2 >;
  using MF3 = njoy::ENDFtk::file::Type< 3 >;
  using MF4 = njoy::ENDFtk::file::Type< 4 >;
  using MF5 = njoy::ENDFtk::file::Type< 5 >;
  using MF6 = njoy::ENDFtk::file::Type< 6 >;
  using MF7 = njoy::ENDFtk::file::Type< 7 >;
  using MF8 = njoy::ENDFtk::file::Type< 8 >;
  using MF9 = njoy::ENDFtk::file::Type< 9 >;
  using MF10 = njoy::ENDFtk::file::Type< 10 >;
  using MF12 = njoy::ENDFtk::file::Type< 12 >;
  using MF13 = njoy::ENDFtk::file::Type< 13 >;
  using MF14 = njoy::ENDFtk::file::Type< 14 >;
  using MF15 = njoy::ENDFtk::file::Type< 15 >;
  using MF23 = njoy::ENDFtk::file::Type< 23 >;
  using MF26 = njoy::ENDFtk::file::Type< 26 >;
  using MF27 = njoy::ENDFtk::file::Type< 27 >;
  using MF28 = njoy::ENDFtk::file::Type< 28 >;
  using MF32 = njoy::ENDFtk::file::Type< 32 >;
  using MF33 = njoy::ENDFtk::file::Type< 33 >;
  using MF34 = njoy::ENDFtk::file::Type< 34 >;

  // wrap views created by this section

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

    "MF",
    [] ( const Material& self, int mf ) ->decltype(auto)
       { return self.MF( mf ); },
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "file",
    [] ( const Material& self, int mf ) ->decltype(auto)
       { return self.file( mf ); },
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
