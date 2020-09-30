#ifndef NJOY_ENDFTK_PYTHON_READ
#define NJOY_ENDFTK_PYTHON_READ

// system includes
#include <string>

// other includes
#include "ENDFtk/HeadRecord.hpp"

/**
 *  @brief Read a section from a string
 *
 *  @param[in] section   the string to read from
 */
template < typename Section >
Section read( const std::string& section ) {

  auto begin = section.begin();
  auto end = section.end();
  long lineNumber = 1;
  njoy::ENDFtk::HeadRecord head( begin, end, lineNumber );

  return Section( head, begin, end, lineNumber, head.MAT() );
}

#endif
