#ifndef NJOY_ENDFTK_FILE_32
#define NJOY_ENDFTK_FILE_32

// system includes

// other includes
#include "ENDFtk/section/32.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 32 > : protected Base< Type< 32 >, section::Type< 32, 151 > > {

    friend class Base< Type, section::Type< 32, 151 > >;

    /* auxiliary functions */

    static auto getSectionNumber( const section::Type< 32, 151 >& section ) {

      return section.MT();
    }

    template< typename OutputIterator >
    static void printSection( const section::Type< 32, 151 >& section,
                              OutputIterator& it, int MAT, int MF ) {

      section.print( it, MAT, MF );
    }

    template< typename Iterator >
    static auto
    readSection( StructureDivision& division,
                 Iterator& begin,
                 const Iterator& end,
                 long& lineNumber ) {

      switch ( division.tail.MT() ) {

        case 151 : return section::Type< 32, 151 >( asHead( division ), begin, end,
                                                    lineNumber, division.tail.MAT() );
        default : throw std::exception();
      }
    }

  public :

    /* ctor */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    Type() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] section   the MF32 MT151 section
     */
    Type( section::Type< 32, 151 >&& section ) :
      Base( { std::move( section ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] sections   the sections of the file
     */
    Type( std::vector< section::Type< 32, 151 > >&& sections ) :
      Base( std::move( sections ) ) {}

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
    Type( StructureDivision& division,
          Iterator& begin, const Iterator& end, long& lineNumber ) :
      Base( division, begin, end, lineNumber ) {}

    /* methods */

    /**
     *  @brief Return the file number
     */
    static constexpr int fileNumber() { return 32; }

    using Base::MF;
    using Base::sections;
    using Base::MTs;
    using Base::begin;
    using Base::end;
    using Base::hasMT;
    using Base::hasSection;
    using Base::section;
    using Base::MT;
    using Base::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
