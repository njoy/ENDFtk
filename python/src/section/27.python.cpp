// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/27.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_27( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 27 >;

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF27 section - atomic form factors or scattering functions"
  );

  // wrap the section
  section
  .def(

    python::init< int, int, double,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "x" ), python::arg( "h" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self           the section\n"
    "    mt             the MT number\n"
    "    zaid           the ZA  identifier\n"
    "    awr            the atomic mass ratio\n"
    "    boundaries     the interpolation range boundaries\n"
    "    interpolants   the interpolation types for each range\n"
    "    x              the x values\n"
    "    h              the form factor or scattering function values"
  )
  .def_property_readonly(

    "Z",
    &Section::Z,
    "The Z number of the atom"
  )
  .def_property_readonly(

    "atom_z",
    &Section::atomZ,
    "The Z number of the atom"
  )
  .def_property_readonly(

    "X",
    [] ( const Section& self ) -> DoubleRange
       { return self.X(); },
    "The x values"
  )
  .def_property_readonly(

    "H",
    [] ( const Section& self ) -> DoubleRange
       { return self.H(); },
    "The form factor or scattering function values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Section >( section );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
