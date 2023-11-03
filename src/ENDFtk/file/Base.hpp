#ifndef NJOY_ENDFTK_FILE_BASE
#define NJOY_ENDFTK_FILE_BASE

// system includes
#include <map>

// other includes
#include "range/v3/view/map.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template < typename Derived, typename Section >
  class Base {

  protected:

    /* fields */
    std::map< int, Section > sections_;

    /* auxiliary functions */
    #include "ENDFtk/file/Base/src/read.hpp"
    #include "ENDFtk/file/Base/src/fill.hpp"
    #include "ENDFtk/file/Base/src/verifyFEND.hpp"

    /* ctor */
    #include "ENDFtk/file/Base/src/ctor.hpp"

  public:

    /* get methods */

    /**
     *  @brief Return the MF number of the file
     */
    static constexpr int MF() {

      return Derived::fileNumber();
    }

    /**
     *  @brief Return the sections stored in this file
     */
    auto MTs() {

      return this->sections_ | ranges::cpp20::views::values;
    }

    /**
     *  @brief Return the sections stored in this file
     */
    auto sections() {

      return this->MTs();
    }

    /**
     *  @brief Return the sections stored in this file
     */
    auto MTs() const {

      return this->sections_ | ranges::cpp20::views::values;
    }

    /**
     *  @brief Return the sections stored in this file
     */
    auto sections() const {

      return this->MTs();
    }

    /**
     *  @brief Return an iterator to the start of the sections
     */
    auto begin() { return this->sections().begin(); }

    /**
     *  @brief Return an iterator to the end of the sections
     */
    auto end() { return this->sections().end(); }

    /**
     *  @brief Return an iterator to the start of the sections
     */
    auto begin() const { return this->sections().begin(); }

    /**
     *  @brief Return an iterator to the end of the sections
     */
    auto end() const { return this->sections().end(); }

    /**
     *  @brief Verify if a given section (defined by the MT number) is defined
     *
     *  @param mt   the MT number of the section to be verified
     */
    bool hasMT( int mt ) const {

      return this->sections_.count( mt );
    }

    /**
     *  @brief Verify if a given section (defined by the MT number) is defined
     *
     *  @param mt   the MT number of the section to be verified
     */
    bool hasSection( int mt ) const {

      return this->hasMT( mt );
    }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in] mt   the MT number of the section to be returned
     */
    const Section& section( int mt ) const {

      try {

        return this->sections_.at( mt );
      }
      catch( std::out_of_range& o ) {

        Log::error( "Requested section number (MT) does not"
                    " correspond to a stored section" );
        Log::info( "Requested section number: {}", mt );
        Log::info( "File queried: ", this->MF() );
        throw o;
      }
    }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in] mt   the MT number of the section to be returned
     */
    const Section& MT( int mt ) const {

      return this->section( mt );
    }

    #include "ENDFtk/file/Base/src/print.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
