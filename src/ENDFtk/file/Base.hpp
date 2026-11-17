#ifndef NJOY_ENDFTK_FILE_BASE
#define NJOY_ENDFTK_FILE_BASE

// system includes
#include <list>

// other includes
#include "tools/std20/views.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template < typename Derived, typename Section >
  class Base {

  protected:

    /* fields */

    std::list< Section > sections_;

    /* auxiliary functions */

    /**
     *  @brief Return iterator to the section with the given mt number
     *
     *  @param[in] mt    the mt number
     */
    auto find( int mt ) {

      auto iter = std::lower_bound( this->sections_.begin(), this->sections_.end(), mt,
                                    [] ( auto&& left, auto&& right )
                                       { return Derived::getSectionNumber( left ) < right; } );

      if ( iter != this->sections_.end() ) {

        if ( Derived::getSectionNumber( *iter ) == mt ) {

          return iter;
        }
      }
      return this->sections_.end();
    }

    /**
     *  @brief Return iterator to the section with the given mt number
     *
     *  @param[in] mt    the mt number
     */
    auto find( int mt ) const {

      auto iter = std::lower_bound( this->sections_.begin(), this->sections_.end(), mt,
                                    [] ( auto&& left, auto&& right )
                                       { return Derived::getSectionNumber( left ) < right; } );

      if ( iter != this->sections_.end() ) {

        if ( Derived::getSectionNumber( *iter ) == mt ) {

          return iter;
        }
      }
      return this->sections_.end();
    }

    template< typename Iterator >
    static auto
    read( StructureDivision& division,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber ) {

      std::vector< Section > sections;
      while ( not division.isFend() ) {

        sections.emplace_back( Derived::readSection( division, begin, end, lineNumber ) );
        division = StructureDivision( begin, end, lineNumber );
      }
      verifyFEND( division, lineNumber );
      return fill( std::move( sections ) );
    }

    static auto
    fill( std::vector< Section >&& sections ) {

      std::list< Section > list;
      for ( auto&& section : sections ) {

        int MT = Derived::getSectionNumber( section );
        auto iter = std::lower_bound( list.begin(), list.end(), MT,
                                      [] ( auto&& left, auto&& right )
                                         { return Derived::getSectionNumber( left ) < right; } );
        if ( iter != list.end() ) {

          if ( Derived::getSectionNumber( *iter ) == MT ) {

            Log::error( "Section with duplicate section number found" );
            Log::info( "Sections are required to specify a unique MT or section number" );
            Log::info( "Encountered duplicate MT: {}", MT );
            throw std::exception();
          }
        }
        list.insert( iter, std::move( section ) );
      }
      return list;
    }

    static void
    verifyFEND( const StructureDivision& structureDivision,
                long lineNumber ) {

      if ( not structureDivision.isFend() ) {

        int MF = Base::MF();
        if ( structureDivision.isSend() ) {

          Log::error( "Encountered duplicate SEND record in File {}", MF );
          Log::info("Line number: {}", lineNumber );
          throw std::exception{};
        }
        else if ( structureDivision.isHead() ) {

          Log::error( "Inappropriate section encountered in File {}", MF );
          Log::info( "Section number: {}", asHead( structureDivision ).section() );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception{};
        }
        else if ( structureDivision.isMend() ) {

          Log::error( "Encountered MEND record before FEND record in File {}", MF );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception{};
        }
        else if ( structureDivision.isTend() ) {

          Log::error( "Encountered TEND record before FEND record in File {}", MF );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception{};
        }
      }
    }

    /* ctor */

    //! @todo pybind11 variant needs default constructor workaround
    //#ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    Base() = default;
    //#endif

    /**
     *  @brief Constructor
     *
     *  @param[in] sections   the sections of the file
     */
    Base( std::vector< Section >&& sections ) :
      sections_( fill( std::move( sections ) ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] division     the first HEAD record of the section
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     */
    template< typename Iterator >
    Base( StructureDivision& division,
          Iterator& begin, const Iterator& end, long& lineNumber )
      try: sections_( read( division, begin, end, lineNumber ) ) {}
      catch ( std::exception& e ) {

        Log::info("Encountered error while reading file::Type<{}>", MF() );
        Log::info( "Line number: {}", lineNumber );
        throw e;
      }

  public:

    /* get methods */

    /**
     *  @brief Return the MF number of the file
     */
    static constexpr int MF() { return Derived::fileNumber(); }

    /**
     *  @brief Return the sections stored in this file
     */
    auto MTs() {

      using namespace njoy::tools;
      return std20::views::all( this->sections_ );
    }

    /**
     *  @brief Return the sections stored in this file
     */
    auto sections() { return this->MTs(); }

    /**
     *  @brief Return the sections stored in this file
     */
    auto MTs() const {

      using namespace njoy::tools;
      return std20::views::all( this->sections_ );
    }

    /**
     *  @brief Return the sections stored in this file
     */
    auto sections() const { return this->MTs(); }

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
    bool hasMT( int mt ) const { return this->find( mt ) != this->sections_.end(); }

    /**
     *  @brief Verify if a given section (defined by the MT number) is defined
     *
     *  @param mt   the MT number of the section to be verified
     */
    bool hasSection( int mt ) const { return this->hasMT( mt ); }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in] mt   the MT number of the section to be returned
     */
    const Section& section( int mt ) const {

      auto iter = this->find( mt );
      if ( iter != this->sections_.end() ) {

        return *iter;
      }

      Log::error( "Requested section number (MT) does not"
                  " correspond to a stored section" );
      Log::info( "Requested section number: {}", mt );
      Log::info( "File queried: ", this->MF() );
      throw std::exception();
    }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in] mt   the MT number of the section to be returned
     */
    const Section& MT( int mt ) const {

      return this->section( mt );
    }

    /**
     *  @brief Print the file (includes FEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT ) const {

      int MF = this->MF();
      for ( const auto& entry : this->sections_ ) {

        Derived::printSection( entry, it, MAT, MF );
      }
      FEND( MAT ).print( it );
    }
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
