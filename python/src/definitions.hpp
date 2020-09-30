#ifndef NJOY_ENDFTK_PYTHON_DEFINITIONS
#define NJOY_ENDFTK_PYTHON_DEFINITIONS

// system includes

// other includes
#include "print.hpp"

/**
 *  @brief Add standard section definitions
 *
 *  This adds the following standard properties:
 *    ZA, AWR, atomic_weight_ratio, MT, section_number, NC
 *
 *  @param[in] section   the section to which the definitions have to be added
 */
template < typename Section, typename PythonClass >
void addStandardSectionDefinitions( PythonClass& section ) {

  section
  .def_property_readonly(

    "ZA",
    [] ( const Section& self ) { return self.ZA(); },
    "The ZA identifier for the section"
  )
  .def_property_readonly(

    "AWR",
    [] ( const Section& self ) { return self.AWR(); },
    "The atomic weight ratio for the section"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    [] ( const Section& self ) { return self.atomicWeightRatio(); },
    "The atomic weight ratio for the section"
  )
  .def_property_readonly(

    "MT",
    [] ( const Section& self ) { return self.MT(); },
    "The MT number of the section"
  )
  .def_property_readonly(

    "section_number",
    [] ( const Section& self ) { return self.sectionNumber(); },
    "The MT number of the section"
  )
  .def_property_readonly(

    "NC",
    [] ( const Section& self ) { return self.NC(); },
    "Return the number of lines in this section"
  )
  .def(

  "to_string",
  [] ( const Section& self, int mat, int mf )
     { return print( self, mat, mf ); },
  "Return the string representation of the section\n\n"
  "Arguments:\n"
  "    self    the section\n"
  "    mat     the MAT number to be used\n"
  "    mf      the MF number to be used"
  );
}

#endif
