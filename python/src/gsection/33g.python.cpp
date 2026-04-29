// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/gsection/33g.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGSection_33( python::module& module, python::module& ) {

  // type aliases
  using GSection = njoy::ENDFtk::section::GType< 33 >;

  // create the section
  python::class_< GSection > gsection(

      module,
      "GSection",
      "MF33 gsection - group cross section covariance matrices"
  );

  // wrap section
  gsection
  .def(

      python::init< int, int, double, int, int, std::map< size_t,
                    std::vector< std::vector< double > > >&& >(),
      python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
      python::arg( "lr" ) = 0, python::arg( "ngn" ), python::arg( "covr" ),
      "Initialise the section\n\n"
      "Arguments:\n"
      "   self        the section\n"
      "   mt          the MT number\n"
      "   zaid        the ZA identifier\n"
      "   awr         the atomic mass ratio\n"
      "   lr          the complex breakup flag (default 0)\n"
      "   ngn         the number of neutron groups\n"
      "   covr        map of the secondary reaction and its associated covariance matrix (ngn, ngn)\n"
  )
  .def_property_readonly(

    "LRFLAG",
    &GSection::LRFLAG,
    "The break up identifier flag"
  )
  .def_property_readonly(

    "break_up",
    &GSection::breakUp,
    "The break up identifier flag"
  )
  .def_property_readonly(

    "NGN",
    &GSection::NGN,
    "The number of neutron energy bins"
  )
  .def_property_readonly(

    "number_groups",
    &GSection::numberNeutronGroups,
    "The number of neutron groups"
  )
  .def_property_readonly(

    "secondary_reactions",
    [] ( const GSection& self ) -> IntRange
       { return self.secondaryReactions(); },
    "The present secondary reactions"
  )
  .def_property_readonly(

    "NSMT",
    &GSection::NSMT,
    "The number of secondary reactions"
  )
  .def_property_readonly(

    "number_secondary_reactions",
    &GSection::numberSecondaryReactions,
    "The number of secondary reactions"
  )
  .def(

    "covariance",
    &GSection::covariance,
    python::arg( "mt" ),
    "The covaraince matrix for a given secondary reaction"
  );

  addStandardGSectionDefinitions< GSection >( gsection );
}