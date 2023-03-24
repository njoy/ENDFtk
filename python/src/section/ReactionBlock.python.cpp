// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/ReactionBlock.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReactionBlock( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Component = njoy::ENDFtk::section::ReactionBlock;
  using DerivedCovariance = njoy::ENDFtk::section::DerivedCovariance;
  using DerivedCovarianceRange = RandomAccessAnyView< DerivedCovariance >;
  using ExplicitCovariance = njoy::ENDFtk::section::ExplicitCovariance;
  using ExplicitCovarianceRange = RandomAccessAnyView< ExplicitCovariance >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Component >(
      viewmodule,
      "any_view< ReactionBlock, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "ReactionBlock",
    "Covariance component - a covariance subsection"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int, int,
                  std::vector< DerivedCovariance >&&,
                  std::vector< ExplicitCovariance >&& >(),
    python::arg( "xmf1" ), python::arg( "xlfs1" ),
    python::arg( "mat1" ), python::arg( "mt1" ),
    python::arg( "nc" ), python::arg( "ni" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    xmf1           the file number of the second cross section\n"
    "    xlfs1          the final excited state of the second cross section\n"
    "    mat1           the material number of the second cross section\n"
    "    mt1            the section number of the second cross section\n"
    "    nc             the NC-type (derived) subsubsections\n"
    "    ni             the NI-type (explicit) subsubsections\n"
  )
  .def(

    python::init< double, double, int, int,
                  std::vector< DerivedCovariance >&& >(),
    python::arg( "xmf1" ), python::arg( "xlfs1" ),
    python::arg( "mat1" ), python::arg( "mt1" ),
    python::arg( "nc" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    xmf1           the file number of the second cross section\n"
    "    xlfs1          the final excited state of the second cross section\n"
    "    mat1           the material number of the second cross section\n"
    "    mt1            the section number of the second cross section\n"
    "    nc             the NC-type (derived) subsubsections\n"
  )
  .def(

    python::init< double, double, int, int,
                  std::vector< ExplicitCovariance >&& >(),
    python::arg( "xmf1" ), python::arg( "xlfs1" ),
    python::arg( "mat1" ), python::arg( "mt1" ),
    python::arg( "ni" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    xmf1           the file number of the second cross section\n"
    "    xlfs1          the final excited state of the second cross section\n"
    "    mat1           the material number of the second cross section\n"
    "    mt1            the section number of the second cross section\n"
    "    ni             the NI-type (explicit) subsubsections\n"
  )
  .def_property_readonly(

    "XMF1",
    &Component::XMF1,
    "the file number for the second cross section"
  )
  .def_property_readonly(

    "second_file_number",
    &Component::secondFileNumber,
    "the file number for the second cross section"
  )
  .def_property_readonly(

    "XLFS1",
    &Component::XLFS1,
    "the final excited state for the second cross section"
  )
  .def_property_readonly(

    "second_final_excited_state",
    &Component::secondFinalExcitedState,
    "the final excited state for the second cross section"
  )
  .def_property_readonly(

    "MAT1",
    &Component::MAT1,
    "the material number for the second cross section"
  )
  .def_property_readonly(

    "second_material_number",
    &Component::secondMaterialNumber,
    "the material number for the second cross section"
  )
  .def_property_readonly(

    "MT1",
    &Component::MT1,
    "the section number for the second cross section"
  )
  .def_property_readonly(

    "second_section_number",
    &Component::secondSectionNumber,
    "the section number for the second cross section"
  )
  .def_property_readonly(

    "NK",
    &Component::NK,
    "the number of NC-type (derived) subsubsections"
  )
  .def_property_readonly(

    "number_derived",
    &Component::numberDerived,
    "the number of NC-type (derived) subsubsections"
  )
  .def_property_readonly(

    "NI",
    &Component::NI,
    "the number of NI-type (explicit) subsubsections"
  )
  .def_property_readonly(

    "number_explicit",
    &Component::numberExplicit,
    "the number of NI-type (explicit) subsubsections"
  )
  .def_property_readonly(

    "derived_covariances",
    [] ( const Component& self ) -> DerivedCovarianceRange
       { return self.derivedCovariances(); },
    "the NC-type (derived) subsubsections"
  )
  .def_property_readonly(

    "explicit_covariances",
    [] ( const Component& self ) -> ExplicitCovarianceRange
       { return self.explicitCovariances(); },
    "the NI-type (explicit) subsubsections"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
