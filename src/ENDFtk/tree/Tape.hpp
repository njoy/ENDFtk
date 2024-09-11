#ifndef NJOY_ENDFTK_TREE_TAPE
#define NJOY_ENDFTK_TREE_TAPE

// system includes
#include <vector>
#include <list>
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/Tape.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/toMaterial.hpp"

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
   *
   *  An ENDF tape starts with a tape identification (a label, which sometimes
   *  can contain a tape number).
   */
  class Tape {

    /* fields */
    std::optional< TapeIdentification > tpid_;
    std::list< Material > materials_;

    /* auxiliary function */
    #include "ENDFtk/tree/Tape/src/find.hpp"
    #include "ENDFtk/tree/Tape/src/fill.hpp"

  public:

    /* constructor */
    #include "ENDFtk/tree/Tape/src/ctor.hpp"

    /* methods */
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

      auto range = this->find( mat );
      return std::distance( range.first, range.second );
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

      auto range = this->find( mat );
      return range.first != range.second;
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

      using namespace njoy::tools;
      return std20::views::all( this->materials_ );
    }

    /**
     *  @brief Return all materials in the tape
     */
    auto materials() const {

      using namespace njoy::tools;
      return std20::views::all( this->materials_ );
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
    auto begin() const { return this->materials().begin(); }

    /**
     *  @brief Return an end iterator to all materials
     */
    auto end() const { return this->materials().end(); }

    /**
     *  @brief Return the number of materials in the tape
     */
    std::size_t size() const { return this->materials_.size(); }

    /**
     *  @brief Return the tape's content
     */
    auto content() const {

      std::string content;
      if ( this->tpid_.has_value() ) {

        auto output = std::back_inserter( content );
        this->tpid_->print( output, 0, 0, 0 );
      }

      for ( const auto& material : this->materials() ) {

        content += material.content();
      }

      if ( content.size() ) {

        auto output = std::back_inserter( content );
        TEND().print( output );
      }

      return content;
    }

    /**
     *  @brief Return the tape identification (the first line in the file)
     */
    const TapeIdentification& TPID() const { return *( this->tpid_ ); }

    /**
     *  @brief Return all unique material numbers in the tape
     */
    std::vector< int > materialNumbers() const {

      using namespace njoy::tools;
      auto keys = this->materials_ | std20::views::transform(
                                         [] ( auto&& material )
                                            { return material.materialNumber(); } );
      std::vector< int > materials( keys.begin(), keys.end() );
      std::sort( materials.begin(), materials.end() );
      materials.erase( std::unique( materials.begin(), materials.end() ), materials.end() );
      return materials;
    }

    #include "ENDFtk/tree/Tape/src/remove.hpp"
    #include "ENDFtk/tree/Tape/src/insert.hpp"
    #include "ENDFtk/tree/Tape/src/replace.hpp"

    #include "ENDFtk/tree/Tape/src/parse.hpp"

    #include "ENDFtk/tree/Tape/src/clean.hpp"
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
