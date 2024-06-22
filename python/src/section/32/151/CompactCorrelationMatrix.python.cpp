// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapCompactCorrelationMatrix( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::CompactCorrelationMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CompactCorrelationMatrix",
    "MF32 MT151 section - compact correlation matrix (LCOMP = 2)"
  );

  // wrap the section
  component
  .def(

    python::init< unsigned int, std::vector< unsigned int >&&,
                  std::vector< unsigned int >&&, std::vector< double >&&,
                  unsigned int >(),
    python::arg( "order" ), python::arg( "i" ), python::arg( "j" ),
    python::arg( "correlations" ), python::arg( "ndigit" ) = 6,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self           the component\n"
    "    order          the order of the (square) correlation matrix\n"
    "    i              the i coordinates\n"
    "    j              the j coordinates\n"
    "    correlations   the correlation values\n"
    "    ndigit         the number of digits for compacting (default = 6)"
  )
  .def_property_readonly(

    "NDIGIT",
    &Component::NDIGIT,
    "The number of digits used for compacting"
  )
  .def_property_readonly(

    "number_digits",
    &Component::numberDigits,
    "The number of digits used for compacting"
  )
  .def_property_readonly(

    "NNN",
    &Component::NNN,
    "The order of the correlation matrix"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The order of the correlation matrix"
  )
  .def_property_readonly(

    "I",
    [] ( const Component& self ) -> IntRange
       { return self.I(); },
    "The i coordinates for which correlation values are available"
  )
  .def_property_readonly(

    "J",
    [] ( const Component& self ) -> IntRange
       { return self.J(); },
    "The j coordinates for which correlation values are available"
  )
  .def_property_readonly(

    "correlations",
    [] ( const Component& self ) -> DoubleRange
       { return self.correlations(); },
    "The correlation values"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
