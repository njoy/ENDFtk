// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/12.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMultiplicities( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 12 >;
  using Component = Section::Multiplicities;
  using TotalMultiplicity = Section::TotalMultiplicity;
  using PartialMultiplicity = Section::PartialMultiplicity;
  using PartialMultiplicityRange = RandomAccessAnyView< PartialMultiplicity >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< PartialMultiplicity >(
      viewmodule,
      "any_view< PartialMultiplicity, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "Multiplicities",
    "MF12 section - the energy dependence of the photon production cross\n"
    "               section is given as multiplicities"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( PartialMultiplicity partial )
                     { return Component( std::move( partial ) ); } ),
    python::arg( "partial" ),
    "Initialise the component (only one partial given, no total required)\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    partial    the partial multiplicity"
  )
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( TotalMultiplicity total,
                       std::vector< PartialMultiplicity >&& partials )
                     { return Component( std::move( total ),
                                         std::move( partials ) ); } ),
    python::arg( "total" ), python::arg( "partials" ),
    "Initialise the component (one total and multiple partials)\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    total       the total multiplicity\n"
    "    partials    the partial multiplicities"
  )
  .def_property_readonly(

    "LO",
    [] ( const Component& self ) { return self.LO(); },
    "The photon production representation type"
  )
  .def_property_readonly(

    "representation",
    &Component::representation,
    "The photon production representation type"
  )
  .def_property_readonly(

    "NK",
    &Component::NK,
    "The the number of photons (discrete and continuum) with partial multiplicities"
  )
  .def_property_readonly(

    "number_photons",
    &Component::numberPhotons,
    "The the number of photons (discrete and continuum) with partial multiplicities"
  )
  .def_property_readonly(

    "total_multiplicity",
    &Component::totalMultiplicity,
    "The total multiplicity (optional)"
  )
  .def_property_readonly(

    "photon_partial_multiplicities",
    [] ( const Component& self ) -> PartialMultiplicityRange
       { return self.photonPartialMultiplicities(); },
    "The partial multiplicities"
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

  // no standard component definitions: read() required knowing NK
}
