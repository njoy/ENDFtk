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

  /**
   *  @class
   *  @brief The ENDF tree tape to index and access ENDF data
   *
   *  This class is used to load an ENDF tape and index its content into
   *  the different ENDF tree components: materials, sections and files. This
   *  indexing operation performed at construction does not parse the underlying
   *  ENDF data. Once the tape is indexed, a user can request materials, files
   *  and sections to be parsed individually.
   */
  template< typename Buffer >
  class Tape {

    /* type aliases */
    using BufferIterator = ranges::iterator_t< const Buffer >;

  public:

    /* type aliases */
    using Material_t = Material< BufferIterator >;

  private:

    /* fields */
    Buffer buffer_;
    std::optional< TapeIdentification > tpid;
    std::multimap< int, Material_t > materials_;

    /* auxiliary function */
    #include "ENDFtk/tree/Tape/src/createMap.hpp"

  public:

    /* constructor */
    #include "ENDFtk/tree/Tape/src/ctor.hpp"

    /* methods */
    #include "ENDFtk/tree/Tape/src/material.hpp"

    /**
     *  @brief Return the material with the requested MAT number
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto MAT( int mat ) { return this->material( mat ); }

    /**
     *  @brief Return the material with the requested MAT number
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto MAT( int mat ) const { return this->material( mat ); }

    bool hasMAT( int mat ) const {
      return this->materials_.count( mat );
    }

    bool hasMaterial( int mat ) const {
      return this->hasMAT( mat );
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
