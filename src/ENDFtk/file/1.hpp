#ifndef NJOY_ENDFTK_FILE_1
#define NJOY_ENDFTK_FILE_1

// system includes
#include <variant>

// other includes
#include "ENDFtk/section/1.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 1 > : protected Base< Type< 1 >,
                                    std::variant< section::Type< 1, 451 >,
                                                  section::Type< 1, 452 >,
                                                  section::Type< 1, 455 >,
                                                  section::Type< 1, 456 >,
                                                  section::Type< 1, 458 >,
                                                  section::Type< 1, 460 > > > {

    using SectionVariant = std::variant< section::Type< 1, 451 >,
                                         section::Type< 1, 452 >,
                                         section::Type< 1, 455 >,
                                         section::Type< 1, 456 >,
                                         section::Type< 1, 458 >,
                                         section::Type< 1, 460 > >;
    friend class Base< Type, SectionVariant >;

    /* auxiliary functions */

    static auto getSectionNumber( const SectionVariant& section ) {

      return std::visit( [] ( const auto& value )
                            { return value.MT(); },
                         section );
    }

    template< typename OutputIterator >
    static void printSection( const SectionVariant& section,
                              OutputIterator& it, int MAT, int MF ) {

      std::visit( [&] ( const auto& value )
                      { value.print( it, MAT, MF ); },
                  section );
    }

    template< typename Iterator >
    static SectionVariant
    readSection( StructureDivision& division,
                 Iterator& begin,
                 const Iterator& end,
                 long& lineNumber ) {

      switch ( division.tail.MT() ) {

        case 451 : return section::Type< 1, 451 >( asHead( division ), begin, end,
                                                   lineNumber, division.tail.MAT() );
        case 452 : return section::Type< 1, 452 >( asHead( division ), begin, end,
                                                   lineNumber, division.tail.MAT() );
        case 455 : return section::Type< 1, 455 >( asHead( division ), begin, end,
                                                   lineNumber, division.tail.MAT() );
        case 456 : return section::Type< 1, 456 >( asHead( division ), begin, end,
                                                   lineNumber, division.tail.MAT() );
        case 458 : return section::Type< 1, 458 >( asHead( division ), begin, end,
                                                   lineNumber, division.tail.MAT() );
        case 460 : return section::Type< 1, 460 >( asHead( division ), begin, end,
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
     *  @param[in] section   the MF1 MT451 section
     */
    Type( section::Type< 1, 451 >&& section ) :
      Base( { std::move( section ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] sections   the sections of the file
     */
    Type( std::vector< SectionVariant >&& sections ) :
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
    static constexpr int fileNumber() { return 1; }

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
