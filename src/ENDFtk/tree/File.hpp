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

  template< typename BufferIterator >
  class File {
  public:
    /* convenience typedefs */
    using Section_t = Section< BufferIterator >;
    using iterator = typename std::vector< Section_t >::iterator;
    using const_iterator = typename std::vector< Section_t >::const_iterator;

  protected:
    /* fields */
    int fileNo;
    std::map< int, Section_t > sections_;
    std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* ctor */
    #include "ENDFtk/tree/File/src/createMap.hpp"

  public:

    #include "ENDFtk/tree/File/src/ctor.hpp"
    #include "ENDFtk/tree/File/src/parse.hpp"

    /* methods */
    #include "ENDFtk/tree/File/src/sectionNumber.hpp"

    const Section_t&
    MT( int sectionNo ) const { return this->sectionNumber( sectionNo ); }

    Section_t&
    MT( int sectionNo ){ return this->sectionNumber( sectionNo ); }

    bool
    hasMT( int sectionNo ) const { return this->sections_.count( sectionNo ); }

    bool
    hasSectionNumber( int sectionNo ) const {  return this->hasMT( sectionNo ); }

    auto begin(){ return ( this->sections_ | ranges::view::values ).begin(); }
    auto end(){ return ( this->sections_ | ranges::view::values ).end(); }

    auto begin() const {
      return ( this->sections_ | ranges::view::values ).begin();
    }
    auto end() const { return ( this->sections_ | ranges::view::values ).end(); }

    std::size_t size() const { return this->sections_.size(); }

    auto buffer() const {
      return ranges::make_iterator_range( this->bufferLimits.first,
                                          this->bufferLimits.second );
    }

    int MF() const { return this->fileNo; }

    int fileNumber() const { return this->MF(); }

    auto sectionNumbers() const { return ranges::view::keys( sections_ ); }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
