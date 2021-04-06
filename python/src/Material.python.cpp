// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

// local includes
#include "ENDFtk/Material.hpp"
#include "boost/hana.hpp"

// namespace aliases
namespace python = pybind11;

namespace hana = boost::hana;
inline namespace literals { using namespace hana::literals; }

void wrapMaterial( python::module& module, python::module& ) {

  // type aliases
  using Material = njoy::ENDFtk::Material;
  using MF1 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 1 > >;
  using MF2 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 2 > >;
  using MF3 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 3 > >;
  using MF4 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 4 > >;
  using MF5 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 5 > >;
  using MF6 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 6 > >;
  using MF7 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 7 > >;
  using MF8 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 8 > >;
  using MF9 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 9 > >;
  using MF10 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 10 > >;
  using MF12 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 12 > >;
  using MF13 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 13 > >;
  using MF14 = std::reference_wrapper< const njoy::ENDFtk::file::Type< 14 > >;

  // wrap views created by this section

  // create the section
  python::class_< Material > material(

    module,
    "Material",
    "Material - nuclear data for a single material"
  );

  // predefined lambda
  auto getFile = [] ( const Material& self, int mf )
  -> std::variant< MF1, MF2, MF3, MF4, MF5, MF6, MF7, MF8, MF9, MF10,
                   MF12, MF13 > {

    switch ( mf ) {

      case 1 : return self.file( 1_c );
      case 2 : return self.file( 2_c );
      case 3 : return self.file( 3_c );
      case 4 : return self.file( 4_c );
      case 5 : return self.file( 5_c );
      case 6 : return self.file( 6_c );
      case 7 : return self.file( 7_c );
      case 8 : return self.file( 8_c );
      case 9 : return self.file( 9_c );
      case 10 : return self.file( 10_c );
      case 12 : return self.file( 12_c );
      case 13 : return self.file( 13_c );
      case 14 : return self.file( 14_c );
      default: throw std::runtime_error(
                    "Requested file number (" + std::to_string( mf ) +
                    ") does not correspond to a stored file" );
    }
  };

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
    getFile,
    python::arg( "mf" ),
    "Return the file with the requested MF number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mf      the MF number of the file to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "file",
    getFile,
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
  );
}
