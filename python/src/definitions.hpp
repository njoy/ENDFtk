#ifndef NJOY_ENDFTK_PYTHON_DEFINITIONS
#define NJOY_ENDFTK_PYTHON_DEFINITIONS

// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes
#include "print.hpp"
#include "read.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

/**
 *  @brief Add standard TAB2 definitions
 *
 *  This adds the following standard properties:
 *    NR, interpolants, boundaries
 *
 *  @param[in] component   the section to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardInterpolationTableDefinitions( PythonClass& component ) {

  component
  .def_property_readonly(

    "NR",
    [] ( const Component& self ) { return self.NR(); },
    "The number of interpolation ranges"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Component& self ) -> LongRange
       { return self.interpolants(); },
    "The interpolation type for each range"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Component& self ) -> LongRange
       { return self.boundaries(); },
    "The interpolation boundaries"
  );
}

/**
 *  @brief Add standard TAB1 definitions
 *
 *  This adds the following standard properties:
 *    NR, NP, interpolants, boundaries
 *
 *  @param[in] component   the section to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardTableDefinitions( PythonClass& component ) {

  component
  .def_property_readonly(

    "NP",
    [] ( const Component& self ) { return self.NP(); },
    "The number of points"
  );

  // add standard tab2 definitions
  addStandardInterpolationTableDefinitions< Component >( component );
}

/**
 *  @brief Add standard component definitions
 *
 *  This adds the following standard properties:
 *    NC, from_string, to_string
 *
 *  @param[in] component   the section to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardComponentDefinitions( PythonClass& component ) {

  component
  .def(

    python::init< const Component& >(),
    python::arg( "component" ),
    "Copy the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    component    the component to be copied"
  )
  .def_property_readonly(

    "NC",
    [] ( const Component& self ) { return self.NC(); },
    "The number of lines in this component"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, int mat, int mf, int mt ) -> Component
       { return readComponent< Component >( string, mat, mf, mt ); },
    python::arg( "string" ), python::arg( "mat" ),
    python::arg( "mf" ), python::arg( "mt" ),
    "Read the component from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "component\n\n"
    "Arguments:\n"
    "    string    the string representing the component\n"
    "    mat       the MAT number of the section\n"
    "    mf        the MF number of the section\n"
    "    mt        the MT number of the section"
  )
  .def(

    "to_string",
    [] ( const Component& self, int mat, int mf, int mt ) -> std::string
       { return print( self, mat, mf, mt ); },
    python::arg( "mat" ), python::arg( "mf" ), python::arg( "mt" ),
    "Return the string representation of the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    mat     the MAT number to be used\n"
    "    mf      the MF number to be used\n"
    "    mt      the MT number to be used"
  );
}

/**
 *  @brief Add standard section definitions
 *
 *  This adds the following standard properties:
 *    ZA, AWR, atomic_weight_ratio, MT, section_number, NC, from_string,
 *    to_string
 *
 *  @param[in] section   the section to which the definitions have to be added
 */
template < typename Section, typename PythonClass >
void addStandardSectionDefinitions( PythonClass& section ) {

  section
  .def(

    python::init< const Section& >(),
    python::arg( "section" ),
    "Initialise the section with another section\n\n"
    "Arguments:\n"
    "    self       the section\n"
    "    section    the section to be copied"
  )
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
    "The number of lines in this section"
  )
  .def_static(

    "from_string",
    [] ( const std::string& section ) -> Section
       { return readSection< Section >( section ); },
    "Read the section from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "section\n\n"
    "Arguments:\n"
    "    section    the string representing the section"
  )
  .def(

    "to_string",
    [] ( const Section& self, int mat, int mf ) -> std::string
       { return print( self, mat, mf ); },
    python::arg( "mat" ), python::arg( "mf" ),
    "Return the string representation of the section\n\n"
    "Arguments:\n"
    "    self    the section\n"
    "    mat     the MAT number to be used\n"
    "    mf      the MF number to be used"
  );
}

/**
 *  @brief Add standard file definitions
 *
 *  This adds the following standard properties:
 *    init (copy), MF, file_number, has_MT, has_section, from_string, to_string
 *
 *  @param[in] file   the file to which the definitions have to be added
 */
template < typename File, typename PythonClass >
void addStandardFileDefinitions( PythonClass& file ) {

  file
  .def(

    python::init< const File& >(),
    python::arg( "file" ),
    "Initialise the file with another file\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    file    the file to be copied"
  )
  .def_property_readonly(

    "MF",
    [] ( const File& self ) { return self.MF(); },
    "The MF number of the file"
  )
  .def_property_readonly(

    "file_number",
    [] ( const File& self ) { return self.fileNumber(); },
    "The MF number of the file"
  )
  .def(

    "has_MT",
    [] ( const File& self, int mt ) { return self.hasSection( mt ); },
    "Return whether or not the file has a section with the given MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section"
  )
  .def(

    "has_section",
    [] ( const File& self, int mt ) { return self.hasSection( mt ); },
    "Return whether or not the file has a section with the given MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section"
  )
  .def_static(

    "from_string",
    [] ( const std::string& file ) -> File
       { return readFile< File >( file ); },
    "Read the file from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "file\n\n"
    "Arguments:\n"
    "    file    the string representing the file"
  )
  .def(

    "to_string",
    [] ( const File& self, int mat ) -> std::string
       { return print( self, mat ); },
    python::arg( "mat" ),
    "The string representation of the section\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mat     the MAT number to be used"
  );
}

/**
 *  @brief Add file definitions for an unenumerated file (e.g. MF3)
 *
 *  This adds the following standard properties:
 *    init (list of sections), MT, section, sections
 *
 *  @param[in] file   the file to which the definitions have to be added
 */
template < typename File, typename Section, typename SectionRange,
           typename PythonClass >
void addStandardUnenumeratedFileDefinitions( PythonClass& file ) {

  file
  .def(

    python::init< std::vector< Section >&& >(),
    python::arg( "sections" ),
    "Initialise the file\n\n"
    "Arguments:\n"
    "    self       the file\n"
    "    sections   the sections to be put into the file"
  )
  .def(

    "section",
    ( Section& ( File::* )( int ) ) &File::section,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MT",
    ( Section& ( File::* )( int ) ) &File::MT,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "sections",
    [] ( const File& self ) -> SectionRange
       { return self.sections(); },
    "The sections defined in the file"
  );
}

#endif
