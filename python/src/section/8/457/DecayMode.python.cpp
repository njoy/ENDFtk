// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/457.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf8 {

void wrapDecayMode( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 8, 457 >::DecayMode;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "DecayMode",
    "MF8 MT457 section - a single ENDF decay mode"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, double, double, double, double >(),
    python::arg( "rtyp" ), python::arg( "rfs" ), python::arg( "q" ),
    python::arg( "dq" ), python::arg( "br" ), python::arg( "dbr" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    rtyp    the decay chain\n"
    "    rfs     the final isomeric state\n"
    "    q       the Q value\n"
    "    dq      the uncertainty on the Q value\n"
    "    br      the branching ratio value\n"
    "    dbr     the uncertainty on the branching ratio value"
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

    "RTYP",
    &Component::RTYP,
    "The decay chain"
  )
  .def_property_readonly(

    "decay_chain",
    &Component::decayChain,
    "The decay chain"
  )
  .def_property_readonly(

    "RFS",
    &Component::RFS,
    "The final isomeric state"
  )
  .def_property_readonly(

    "final_isomeric_state",
    &Component::finalIsomericState,
    "The final isomeric state"
  )
  .def_property_readonly(

    "Q",
    [] ( const Component& self ) -> DoubleRange
       { return self.Q(); },
    "The Q value and its uncertainty"
  )
  .def_property_readonly(

    "q_value",
    [] ( const Component& self ) -> DoubleRange
       { return self.qValue(); },
    "The Q value and its uncertainty"
  )
  .def_property_readonly(

    "BR",
    [] ( const Component& self ) -> DoubleRange
       { return self.BR(); },
    "The branching ratio and its uncertainty"
  )
  .def_property_readonly(

    "branching_ratio",
    [] ( const Component& self ) -> DoubleRange
       { return self.branchingRatio(); },
    "The branching ratio and its uncertainty"
  );
}

} // namespace mf8
