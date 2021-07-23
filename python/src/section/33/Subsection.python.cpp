// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/33.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf33 {

void wrapSubsection( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 33 >;
  using Component = Section::Subsection;
  using NCType = Section::NCType;
  using NCTypeRange = RandomAccessAnyView< NCType >;
  using NIType = Section::NIType;
  using NITypeRange = RandomAccessAnyView< NIType >;


  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< NCType >(
      viewmodule,
      "any_view< variant< DerivedRedundant, DerivedRatioToStandard >, "
                "random_access >" );
  wrapRandomAccessAnyViewOf< NIType >(
      viewmodule,
      "any_view< variant< CovariancePairs, SquareMatrix,"
                         "RectangularMatrix >, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "Subsection",
    "MF33 section - a subsection of an MF33 section"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int, int,
                  std::vector< NCType >&&, std::vector< NIType >&& >(),
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
    "    nc             the NC-type subsubsections\n"
    "    ni             the NI-type subsubsections\n"
  )
  .def(

    python::init< double, double, int, int,
                  std::vector< NCType >&& >(),
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
    "    nc             the NC-type subsubsections\n"
  )
  .def(

    python::init< double, double, int, int,
                  std::vector< NIType >&& >(),
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
    "    ni             the NI-type subsubsections\n"
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
    "the number of NC-type subsubsections"
  )
  .def_property_readonly(

    "number_nc_type",
    &Component::numberNCType,
    "the number of NC-type subsubsections"
  )
  .def_property_readonly(

    "NI",
    &Component::NI,
    "the number of NI-type subsubsections"
  )
  .def_property_readonly(

    "number_ni_type",
    &Component::numberNIType,
    "the number of NI-type subsubsections"
  )
  .def_property_readonly(

    "components_nc",
    [] ( const Component& self ) -> NCTypeRange
       { return self.componentsNC(); },
    "the NC-type subsubsections"
  )
  .def_property_readonly(

    "components_ni",
    [] ( const Component& self ) -> NITypeRange
       { return self.componentsNI(); },
    "the NI-type subsubsections"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf33
