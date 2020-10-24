#ifndef NJOY_ENDFTK_PYTHON_READ
#define NJOY_ENDFTK_PYTHON_READ

// system includes
#include <string>

// other includes
#include "ENDFtk/StructureDivision.hpp"
#include "ENDFtk/HeadRecord.hpp"

/**
 *  @brief Read a component from a string
 *
 *  @param[in] component   the string to read from
 *  @param[in] mat         the material number
 *  @param[in] mf          the file number
 *  @param[in] mt          the section number
 */
template < typename Component >
Component readComponent( const std::string& component,
                         int mat, int mf, int mt ) {

  auto begin = component.begin();
  auto end = component.end();
  long lineNumber = 1;

  return Component( begin, end, lineNumber, mat, mf, mt );
}

/**
 *  @brief Read a section from a string
 *
 *  @param[in] section   the string to read from
 */
template < typename Section >
Section readSection( const std::string& section ) {

  auto begin = section.begin();
  auto end = section.end();
  long lineNumber = 1;
  njoy::ENDFtk::HeadRecord head( begin, end, lineNumber );

  return Section( head, begin, end, lineNumber, head.MAT() );
}

/**
 *  @brief Read a file from a string
 *
 *  @param[in] file   the string to read from
 */
template < typename File >
File readFile( const std::string& file ) {

  auto begin = file.begin();
  auto end = file.end();
  long lineNumber = 1;
  njoy::ENDFtk::StructureDivision division( begin, end, lineNumber);

  return File( division, begin, end, lineNumber );
}

#endif
