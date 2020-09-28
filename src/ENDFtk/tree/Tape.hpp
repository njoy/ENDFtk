#ifndef NJOY_ENDFTK_TREE_TAPE
#define NJOY_ENDFTK_TREE_TAPE

// system includes
#include <vector>
#include <map>
#include <optional>

// other includes
#include "range/v3/iterator_range.hpp"
#include "range/v3/utility/iterator.hpp"
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  template< typename Buffer >
  class Tape {
    using BufferIterator = ranges::iterator_t< const Buffer >;
  public:
    /* convenience typedefs */
    using Material_t = Material< BufferIterator >;

  protected:
    /* fields */
    Buffer buffer_;
    std::optional< TapeIdentification > tpid;
    std::multimap< int, Material_t > materials_;

    /* ctor */
    #include "ENDFtk/tree/Tape/src/createMap.hpp"

  public:

    #include "ENDFtk/tree/Tape/src/ctor.hpp"

    /* methods */
    #include "ENDFtk/tree/Tape/src/materialNumber.hpp"

    auto MAT( int materialNo ){ return this->materialNumber( materialNo ); }
    auto MAT( int materialNo ) const {
      return this->materialNumber( materialNo ); }

    bool hasMAT( int materialNo ) const {
      return this->materials_.count( materialNo );
    }

    bool hasMaterialNumber( int materialNo ) const {
      return this->hasMAT( materialNo );
    }

    auto begin(){ return ( this->materials_ | ranges::view::values ).begin(); }
    auto end(){ return ( this->materials_ | ranges::view::values ).end(); }

    auto begin() const {
      return ( this->materials_ | ranges::view::values ).begin();
    }
    auto end() const { return ( this->materials_ | ranges::view::values ).end(); }

    std::size_t size() const { return this->materials_.size(); }

    auto buffer() const { return this->buffer_ | ranges::view::all; }

    const TapeIdentification& TPID() const { return *( this->tpid ); }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
