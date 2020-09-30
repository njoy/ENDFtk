#ifndef NJOY_ENDFTK_PYTHON_PRINT
#define NJOY_ENDFTK_PYTHON_PRINT

// system includes
#include <string>

// other includes

/**
 *  @brief Print a component
 *
 *  @param[in] component   the ENDF component
 *  @param[in] mat         the material number
 *  @param[in] mf          the file number
 *  @param[in] mt          the section number
 */
template < typename Component >
std::string print( const Component& component, int mat, int mf, int mt ) {

  std::string buffer;
  auto output = std::back_inserter( buffer );
  component.print( output, mat, mf, mt );
  return buffer;
}

/**
 *  @brief Print a section
 *
 *  @param[in] section   the ENDF section
 *  @param[in] mat       the material number
 *  @param[in] mf        the file number
 */
template < typename Section >
std::string print( const Section& section, int mat, int mf ) {

  std::string buffer;
  auto output = std::back_inserter( buffer );
  section.print( output, mat, mf );
  return buffer;
}

/**
 *  @brief Print a file
 *
 *  @param[in] file   the ENDF section
 *  @param[in] mat    the material number
 *  @param[in] mf        the file number
 *  @param[in] mt        the section number
 */
template < typename File >
std::string print( const File& file, int mat ) {

  std::string buffer;
  auto output = std::back_inserter( buffer );
  file.print( output, mat );
  return buffer;
}

#endif
