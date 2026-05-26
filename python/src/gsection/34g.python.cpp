// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/gsection/34g.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGSection_34( python::module& module, python::module& ) {

  // type aliases
  using GSection = njoy::ENDFtk::section::GType< 34 >;

  // create the section
  python::class_< GSection > gsection(

      module,
      "GSection",
      "MF34 gsection - secondary angular distribution covariance matrices"
  );

  // wrap section
  gsection
  .def(
        python::init< int, int, double, int, int, int, int,
                      std::vector< std::vector< double > >&& >(),
        python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
        python::arg( "irelco" ), python::arg( "l" ), python::arg( "l1" ),
        python::arg( "ngn" ), python::arg( "ang_covr" ),
        "Initialise the section\n\n"
        "Arguments:\n"
        "   self        the section\n"
        "   mt          the MT number\n"
        "   zaid        the ZA identifier\n"
        "   awr         the atomic mass ratio\n"
        "   irelco      the covariance format ( 0/1 = abs./rel. )\n"
        "   l           the primary legendre order\n"
        "   l1          the secondary legendre order\n"
        "   ngn         the number of neutron groups\n"
        "   ang_covr    the secondary angular distribution covariance matrix\n"
  )
  .def_property_readonly(

    "L",
    &GSection::L,
    "The primary legendre order"
  )
  .def_property_readonly(

    "primary_legendre",
    &GSection::primaryLegendre,
    "The primary legendre order"
  )
  .def_property_readonly(

    "L1",
    &GSection::L1,
    "The secondary legendre order"
  )
  .def_property_readonly(

    "secondary_legendre",
    &GSection::secondaryLegendre,
    "The secondary legendre order"
  )
  .def_property_readonly(

    "IRELCO",
    &GSection::IRELCO,
    "The covariance format (0/1 = abs./rel.)"
  )
  .def_property_readonly(

    "covariance_format",
    &GSection::covarianceFormat,
    "The covariance format (0/1 = abs./rel.)"
  )
  .def_property_readonly(

    "NGN",
    &GSection::NGN,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "number_groups",
    &GSection::numberNeutronGroups,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "angular_covariance",
    &GSection::angularCovariance,
    "The secondary angular distribution covariance matrix"
  );

  addStandardGSectionDefinitions< GSection >( gsection );
}
