// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/35.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf35 {

  // declarations - components
  void wrapSquareMatrix( python::module&, python::module& );
}

void wrapSection_35( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 35 >;
  using SquareMatrix = Section::SquareMatrix;
  using SquareMatrixRange = RandomAccessAnyView< SquareMatrix >;

  // wrap components
  mf35::wrapSquareMatrix( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< SquareMatrix >(
      module,
      "any_view< MF35::SquareMatrix, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF35 section - covariances of energy distributions"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, std::vector< SquareMatrix >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "blocks" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number\n"
    "    zaid        the ZA  identifier\n"
    "    awr         the atomic mass ratio\n"
    "    blocks      the energy block subsections (at least 1)\n"
  )
  .def_property_readonly(

    "NK",
    &Section::NK,
    "the number of energy blocks (subsections)"
  )
  .def_property_readonly(

    "number_energy_blocks",
    &Section::numberEnergyBlocks,
    "the number of energy blocks (subsections)"
  )
  .def_property_readonly(

    "energy_blocks",
    [] ( const Section& self ) -> SquareMatrixRange
       { return self.energyBlocks(); },
    "the energy blocks (subsections) defined in this section"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
