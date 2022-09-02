// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/31.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf31 {

void wrapReactionBlock( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 31 >;
  using Component = Section::ReactionBlock;
  using DerivedCovariance = Section::DerivedCovariance;
  using DerivedCovarianceRange = RandomAccessAnyView< DerivedCovariance >;
  using ExplicitCovariance = Section::ExplicitCovariance;
  using ExplicitCovarianceRange = RandomAccessAnyView< ExplicitCovariance >;


  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< DerivedCovariance >(
      viewmodule,
      "any_view< variant< MF31::DerivedRedundant, MF31::DerivedRatioToStandard >, "
                "random_access >" );
  wrapRandomAccessAnyViewOf< ExplicitCovariance >(
      viewmodule,
      "any_view< variant< MF31::CovariancePairs, MF31::SquareMatrix, "
                         "MF31::RectangularMatrix >, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "ReactionBlock",
    "MF31 section - a subsection of an MF31 section"
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

} // namespace mf31
