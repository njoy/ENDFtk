// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedBackgroundRMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::RMatrixLimited::TabulatedBackgroundRMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedBackgroundRMatrix",
    "MF2 MT151 section - tabulated complex function as a channel's background\n"
    "                    R-matrix"
  );

  // wrap the section
  component
  .def(

    python::init< int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&  >(),
    python::arg( "index" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "energies" ),
    python::arg( "real" ), python::arg( "imaginary" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    index           the channel index\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    real            the real values of the tabulated rmatrix\n"
    "    imaginary       the imaginary values of the tabulated rmatrix"
  )
  .def(

    python::init< int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&,
                  std::vector< std::complex< double > >&& >(),
    python::arg( "index" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "energies" ),
    python::arg( "rmatrix" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    index           the channel index\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    rmatrix         the complex tabulated rmatrix values"
  )
  .def_property_readonly(

    "LBK",
    [] ( const Component& self ) { return self.LBK(); },
    "The background R-matrix representation"
  )
  .def_property_readonly(

    "representation",
    [] ( const Component& self ) { return self.representation(); },
    "The background R-matrix representation"
  )
  .def_property_readonly(

    "LCH",
    [] ( const Component& self ) { return self.LCH(); },
    "The channel index"
  )
  .def_property_readonly(

    "channel_index",
    [] ( const Component& self ) { return self.channelIndex(); },
    "The channel index"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "RBR",
    [] ( const Component& self ) -> DoubleRange
       { return self.RBR(); },
    "The real component of the R-matrix values"
  )
  .def_property_readonly(

    "real",
    [] ( const Component& self ) -> DoubleRange
       { return self.real(); },
    "The real component of the R-matrix values"
  )
  .def_property_readonly(

    "RBI",
    [] ( const Component& self ) -> DoubleRange
       { return self.RBI(); },
    "The imaginary component of the R-matrix values"
  )
  .def_property_readonly(

    "imaginary",
    [] ( const Component& self ) -> DoubleRange
       { return self.imaginary(); },
    "The imaginary component of the R-matrix values"
  )
  .def_property_readonly(

    "RB",
    [] ( const Component& self ) -> ComplexRange
       { return self.RB(); },
    "The complex R-matrix values"
  )
  .def_property_readonly(

    "rmatrix",
    [] ( const Component& self ) -> ComplexRange
       { return self.rmatrix(); },
    "The complex R-matrix values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
