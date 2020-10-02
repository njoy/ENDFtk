#ifndef NJOY_ENDFTK_TREE_FILE
#define NJOY_ENDFTK_TREE_FILE

// system includes
#include <vector>
#include <map>

// other includes
#include "range/v3/iterator_range.hpp"
#include "range/v3/view/map.hpp"
#include "header-utilities/echoErroneousLine.hpp"
#include "ENDFtk/file/Type.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree file to index and access ENDF section data
   *
   *  This class represents a single file in an ENDF tape and contains the
   *  indexed ENDF sections from that file. It is created by the ENDF tree
   *  Material class and should not be directly constructed by a user.
   */
  template< typename BufferIterator >
  class File {

  public:

    /* type aliases */
    using Section_t = Section< BufferIterator >;
    using iterator = typename std::vector< Section_t >::iterator;
    using const_iterator = typename std::vector< Section_t >::const_iterator;

  private:

    /* fields */
    int materialNo;
    int fileNo;
    std::map< int, Section_t > sections_;
    std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* auxiliary functions */
    #include "ENDFtk/tree/File/src/createMap.hpp"

  public:

    /* constructor */
    #include "ENDFtk/tree/File/src/ctor.hpp"

    /* methods */
    #include "ENDFtk/tree/File/src/parse.hpp"
    #include "ENDFtk/tree/File/src/section.hpp"

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section_t& MT( int mt ) const { return this->section( mt ); }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section_t& MT( int mt ){ return this->section( mt ); }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasMT( int mt ) const {

      return this->sections_.count( mt );
    }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasSection( int mt ) const {  return this->hasMT( mt ); }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin(){ return ( this->sections_ | ranges::view::values ).begin(); }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end(){ return ( this->sections_ | ranges::view::values ).end(); }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin() const {

      return ( this->sections_ | ranges::view::values ).begin();
    }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end() const { return ( this->sections_ | ranges::view::values ).end(); }

    /**
     *  @brief Return the number of files in the materials
     */
    std::size_t size() const { return this->sections_.size(); }

    /**
     *  @brief Return the file's buffer
     */
    auto buffer() const {
      
      return ranges::make_iterator_range( this->bufferLimits.first,
                                          this->bufferLimits.second );
    }

    /**
     *  @brief Return MAT number of the file
     */
    int MAT() const { return this->materialNo; }

    /**
     *  @brief Return MAT number of the file
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return MF number of the file
     */
    int MF() const { return this->fileNo; }

    /**
     *  @brief Return MF number of the file
     */
    int fileNumber() const { return this->MF(); }

    /**
     *  @brief Return all section numbers in the file
     */
    auto sectionNumbers() const {

      return ranges::view::keys( this->sections_ );
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
