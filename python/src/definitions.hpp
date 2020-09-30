#ifndef NJOY_ENDFTK_PYTHON_DEFINITIONS
#define NJOY_ENDFTK_PYTHON_DEFINITIONS

// system includes

// other includes

/**
 *  @brief Add standard section definitions
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
  );
}

#endif
