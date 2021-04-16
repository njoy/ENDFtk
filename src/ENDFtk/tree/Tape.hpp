#ifndef NJOY_ENDFTK_TREE_TAPE
#define NJOY_ENDFTK_TREE_TAPE

// system includes
#include <vector>
#include <map>
#include <optional>

// other includes
#include "range/v3/action/sort.hpp"
#include "range/v3/action/unique.hpp"
#include "range/v3/range/operations.hpp"
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/Tape.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace ENDFtk {

  // hana namespace declaration inside ENDFtk
  namespace hana = boost::hana;
  inline namespace literals { using namespace hana::literals; }

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
   *
   *  An ENDF tape starts with a tape identification (a label, which sometimes
   *  can contain a tape number).
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
    #include "ENDFtk/tree/Tape/src/parse.hpp"

    #include "ENDFtk/tree/Tape/src/material.hpp"

    /**
     *  @brief Return the materials with the requested MAT number
     *
     *  This function returns a range of materials since a tape can contain
     *  multiple instances of the same material (e.g. at different
     *  temperatures).
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto MAT( int mat ) { return this->material( mat ); }

    /**
     *  @brief Return the materials with the requested MAT number
     *
     *  This function returns a range of materials since a tape can contain
     *  multiple instances of the same material (e.g. at different
     *  temperatures).
     *
     *  @param[in]   mat   the MAT number of the material to be returned
     */
    auto MAT( int mat ) const { return this->material( mat ); }

    /**
     *  @brief Return the number of times a material with the given MAT
     *         number is present
     *
     *  @param[in]   mat   the MAT number of the material
     */
    int numberMAT( int mat ) const {

      return this->materials_.count( mat );
    }

    /**
     *  @brief Return the number of times a material with the given MAT
     *         number is present
     *
     *  @param[in]   mat   the MAT number of the material
     */
    int numberMaterial( int mat ) const { return this->numberMAT( mat ); }

    /**
     *  @brief Return whether or not the tape has a material with the given MAT
     *         number
     *
     *  @param[in]   mat   the MAT number of the material
     */
    bool hasMAT( int mat ) const {

      return this->materials_.count( mat );
    }

    /**
     *  @brief Return whether or not the tape has a material with the given MAT
     *         number
     *
     *  @param[in]   mat   the MAT number of the material
     */
    bool hasMaterial( int mat ) const { return this->hasMAT( mat ); }

    /**
     *  @brief Return all materials in the tape
     */
    auto materials() {

      return this->materials_ | ranges::cpp20::views::values;
    }

    /**
     *  @brief Return all materials in the tape
     */
    auto materials() const {

      return this->materials_ | ranges::cpp20::views::values;
    }

    /**
     *  @brief Return a begin iterator to all materials
     */
    auto begin() { return this->materials().begin(); }

    /**
     *  @brief Return an end iterator to all materials
     */
    auto end() { return this->materials().end(); }

    /**
     *  @brief Return a begin iterator to all materials
     */
    auto begin() const {

      return this->materials().begin();
    }

    /**
     *  @brief Return an end iterator to all materials
     */
    auto end() const { return this->materials().end(); }

    /**
     *  @brief Return the number of materials in the tape
     */
    std::size_t size() const { return this->materials_.size(); }

    /**
     *  @brief Return the tape's buffer
     */
    auto buffer() const { return this->buffer_ | ranges::cpp20::views::all; }

    /**
     *  @brief Return the tape identification (the first line in the file)
     */
    const TapeIdentification& TPID() const { return *( this->tpid ); }

    /**
     *  @brief Return all unique material numbers in the tape
     */
    std::vector< int > materialNumbers() const {

      return ranges::cpp20::views::keys( this->materials_ )
               | ranges::to_vector
               | ranges::actions::sort | ranges::actions::unique;
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
