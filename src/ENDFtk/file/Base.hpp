#ifndef NJOY_ENDFTK_FILE_BASE
#define NJOY_ENDFTK_FILE_BASE

// system includes

// other includes
#include "boost/hana.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/file/details.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template < typename Derived >
  class Base {

    Derived& derived() { return static_cast< Derived& >( *this ); }
    const Derived& derived() const {

      return static_cast< const Derived& >( *this );
    }

  protected:

    /* auxiliary functions */
    static constexpr auto sections() {

      return hana::sort(hana::concat( Derived::requiredSections(),
                                      Derived::optionalSections() ) );
    }

    #include "ENDFtk/file/Base/src/deduceMapType.hpp"
    #include "ENDFtk/file/Base/src/fill.hpp"
    #include "ENDFtk/file/Base/src/read.hpp"
    #include "ENDFtk/file/Base/src/verifyEND.hpp"

  public:

    /* get methods */

    /**
     *  @brief Return the MF number of the file
     */
    static constexpr int MF() {

      return Derived::fileNumber();
    }

    /**
     *  @brief Verify if a given section (defined by the MT number) is defined
     *
     *  @param mt   the MT number of the section to be verified
     */
    template< typename Index >
    constexpr bool hasMT( Index mt ) const {

      return this->derived().hasSection( mt );
    }

    /**
     *  @brief Retrieve a specific MT section
     *
     *  @param mt   the MT number of the section to be retrieved
     */
    template< typename Index >
    constexpr decltype( auto ) MT( Index mt ) const {

      return this->derived().section( mt );
    }

    /**
     *  @brief Retrieve a specific MT section
     *
     *  @param mt   the MT number of the section to be retrieved
     */
    template< typename Index > constexpr decltype( auto ) MT( Index mt ) {

      return this->derived().section( mt );
    }

    #include "ENDFtk/file/Base/src/section.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
