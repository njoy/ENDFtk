// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/34.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf34 {

void wrapLegendreBlock( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 34 >;
  using Component = Section::LegendreBlock;
  using ExplicitCovariance = Section::ExplicitCovariance;
  using ExplicitCovarianceRange = RandomAccessAnyView< ExplicitCovariance >;


  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ExplicitCovariance >(
      viewmodule,
      "any_view< variant< MF34::CovariancePairs, MF34::SquareMatrix, "
                         "MF34::RectangularMatrix >, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "LegendreBlock",
    "MF34 section - a subsection of an MF34 section"
  );

  // wrap the section
  component
  .def(

    python::init< int, int, int,
                  std::vector< ExplicitCovariance >&& >(),
    python::arg( "order" ), python::arg( "order1" ),
    python::arg( "lct" ), python::arg( "data" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    order          the first Legendre order\n"
    "    order1         the second Legendre order\n"
    "    lct            the reference frame\n"
    "    data           the NI-type data blocks\n"
  )
  .def_property_readonly(

    "L",
    &Component::L,
    "the first Legendre order"
  )
  .def_property_readonly(

    "first_legendre_order",
    &Component::firstLegendreOrder,
    "the first Legendre order"
  )
  .def_property_readonly(

    "L1",
    &Component::L1,
    "the second Legendre order"
  )
  .def_property_readonly(

    "second_legendre_order",
    &Component::secondLegendreOrder,
    "the second Legendre order"
  )
  .def_property_readonly(

    "LCT",
    &Component::LCT,
    "the reference frame"
  )
  .def_property_readonly(

    "reference_frame",
    &Component::referenceFrame,
    "the reference frame"
  )
  .def_property_readonly(

    "NI",
    &Component::NI,
    "the number of NI-type data blocks"
  )
  .def_property_readonly(

    "number_data_blocks",
    &Component::numberDataBlocks,
    "the number of NI-type data blocks"
  )
  .def_property_readonly(

    "data",
    [] ( const Component& self ) -> ExplicitCovarianceRange
       { return self.data(); },
    "the NI-type subsubsections"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf34
