// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapBackgroundChannels( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::RMatrixLimited::BackgroundChannels;
  using BackgroundRMatrix = Section::RMatrixLimited::BackgroundRMatrix;
  using BackgroundRMatrixRange = RandomAccessAnyView< std::optional< BackgroundRMatrix > >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< std::optional< BackgroundRMatrix > >(
      viewmodule,
      "any_view< std::optional< BackgroundRMatrix >, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "BackgroundChannels",
    "MF2 MT151 section - background R-matrix values for each channel in the\n"
    "                    spin group"
  );

  // wrap the section
  component
  .def(

    python::init< unsigned int,
                  std::vector< BackgroundRMatrix >&& >(),
    python::arg( "nch" ), python::arg( "channels" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    nch         the total number of channels in the spin group\n"
    "    channels    the background R-matrix values for each channel"
  )
  .def_property_readonly(

    "NCH",
    &Component::NCH,
    "The number of channels"
  )
  .def_property_readonly(

    "number_channels",
    &Component::numberChannels,
    "The number of channels"
  )
  .def_property_readonly(

    "KBK",
    &Component::KBK,
    "The number of channels with background R-matrix values"
  )
  .def_property_readonly(

    "number_background_channels",
    &Component::numberBackgroundChannels,
    "The number of channels with background R-matrix values"
  )
  .def_property_readonly(

    "background_rmatrices",
    [] ( const Component& self ) -> BackgroundRMatrixRange
       { return self.backgroundRMatrices(); },
    "The complex R-matrix values"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "component" ),
    "Copy the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    component    the component to be copied"
  )
  .def_property_readonly(

    "NC",
    [] ( const Component& self ) { return self.NC(); },
    "The number of lines in this component"
  )
  .def(

    "to_string",
    [] ( const Component& self, int mat, int mf, int mt ) -> std::string
       { return print( self, mat, mf, mt ); },
    python::arg( "mat" ), python::arg( "mf" ), python::arg( "mt" ),
    "Return the string representation of the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    mat     the MAT number to be used\n"
    "    mf      the MF number to be used\n"
    "    mt      the MT number to be used"
  );

  // no standard definitions - read constructor needs number of channels and
  // number of background matrices
}
