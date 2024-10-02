#ifndef NJOY_ENDFTK_TAPE
#define NJOY_ENDFTK_TAPE

// system includes
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/Material.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief An ENDF tape - a collection of one or more materials
   */
  class Tape {

    /* fields */
    TapeIdentification id_;
    std::vector< Material > materials_;

    /* auxialiary functions */
    #include "ENDFtk/Tape/src/readMaterials.hpp"
    #include "ENDFtk/Tape/src/verifySize.hpp"

  public :

    /* constructors */
    #include "ENDFtk/Tape/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of materials
     */
    auto numberMaterials() const { return this->materials_.size(); }

    /**
     *  @brief Return the materials stored in this file
     */
    auto materials() {

      using namespace njoy::tools;
      return this->materials_ | std20::views::all;
    }

    /**
     *  @brief Return the materials stored in this file
     */
    auto materials() const {

      using namespace njoy::tools;
      return this->materials_ | std20::views::all;
    }

    /**
     *  @brief Return an iterator to the start of the materials
     */
    auto begin() { return this->materials().begin(); }

    /**
     *  @brief Return an iterator to the end of the materials
     */
    auto end() { return this->materials().end(); }

    /**
     *  @brief Return an iterator to the start of the materials
     */
    auto begin() const { return this->materials().begin(); }

    /**
     *  @brief Return an iterator to the end of the materials
     */
    auto end() const { return this->materials().end(); }

    /**
     *  @brief Return all materials with the given MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    auto MAT( int mat ) const {

      using namespace njoy::tools;
      return this->materials_
                 | std20::views::filter(
                      [mat] ( const auto& material )
                            { return material.MAT() == mat; } );
    }

    /**
     *  @brief Return all materials with the given MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    auto material( int mat ) const { return this->MAT( mat ); }

    /**
     *  @brief Return whether or not the tape contains a material with the given
     *         MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    bool hasMAT( int mat ) const {

      using namespace njoy::tools;
      return std20::distance( this->material( mat ) ) > 0;
    }

    /**
     *  @brief Return whether or not the tape contains a material with the given
     *         MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    bool hasMaterial( int mat ) const { return this->hasMAT( mat ); }

    #include "ENDFtk/Tape/src/print.hpp"
  };

} // ENDFtk namespace
} // njoy namespace

#endif
