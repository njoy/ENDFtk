#ifndef NJOY_ENDFTK_TREE_MATERIAL
#define NJOY_ENDFTK_TREE_MATERIAL

// system includes
#include <vector>
#include <map>

// other includes
#include "header-utilities/echoErroneousLine.hpp"
#include "ENDFtk/tree/File.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  template< typename BufferIterator >
  class Material {
  public:
    /* convenience typedefs */
    using File_t = File< BufferIterator >;
    using iterator = typename std::vector< File_t >::iterator;
    using const_iterator = typename std::vector< File_t >::iterator;

  protected:
    /* fields */
    int materialNo;
    std::map< int, File_t > files_;
    std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* ctor */
  #include "ENDFtk/tree/Material/src/createMap.hpp"

  public:
  #include "ENDFtk/tree/Material/src/ctor.hpp"

    /* methods */
  #include "ENDFtk/tree/Material/src/fileNumber.hpp"

    const File_t&
    MF( int fileNo ) const { return this->fileNumber( fileNo ); }

    File_t&
    MF( int fileNo ) { return this->fileNumber( fileNo ); }

    bool
    hasMF( int fileNo ) const { return this->files_.count( fileNo ); }

    bool
    hasFile( int fileNo ) const { return this->hasMF( fileNo ); }

    auto begin(){ return ( this->files_ | ranges::view::values ).begin(); }
    auto end(){ return ( this->files_ | ranges::view::values ).end(); }

    auto begin() const { return ( this->files_ | ranges::view::values ).begin(); }
    auto end() const { return ( this->files_ | ranges::view::values ).end(); }

    std::size_t size() const { return files_.size(); }

    int MAT() const { return this->materialNo; }

    int materialNumber() const { return this->MAT(); }

    auto buffer() const {
      return ranges::make_iterator_range( this->bufferLimits.first,
                                          this->bufferLimits.second );
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
