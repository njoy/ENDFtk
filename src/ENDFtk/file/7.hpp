#ifndef NJOY_ENDFTK_FILE_7
#define NJOY_ENDFTK_FILE_7

// system includes
#include <variant>

// other includes
#include "ENDFtk/section/7.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 7 > : protected Base< Type< 7 >,
                                    std::variant< section::Type< 7, 2 >,
                                                  section::Type< 7, 4 >,
                                                  section::Type< 7, 451 > > > {

    using SectionVariant = std::variant< section::Type< 7, 2 >,
                                         section::Type< 7, 4 >,
                                         section::Type< 7, 451 > >;
    friend class Base< Type, SectionVariant >;

    /* auxiliary functions blatantly copied from MF1 */

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

    /* auxiliary functions */

    template< typename Iterator >
    static SectionVariant
    readSection( StructureDivision& division,
                 Iterator& begin,
                 const Iterator& end,
                 long& lineNumber ) {

      switch ( division.tail.MT() ) {

        case   2 : return section::Type< 7, 2 >( asHead( division ), begin, end,
                                                 lineNumber, division.tail.MAT() );
        case   4 : return section::Type< 7, 4 >( asHead( division ), begin, end,
                                                 lineNumber, division.tail.MAT() );
        case 451 : return section::Type< 7, 451 >( asHead( division ), begin, end,
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
     *  @param[in] section   the MF7 MT2 section
     */
    Type( section::Type< 7, 2 >&& section ) :
      Base( { std::move( section ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] elastic       the MF7 MT2 section
     *  @param[in] information   the MF7 MT451 section
     */
    Type( section::Type< 7, 2 >&& elastic, section::Type< 7, 451 >&& information ) :
      Base( { std::move( elastic ), std::move( information ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] section   the MF7 MT4 section
     */
    Type( section::Type< 7, 4 >&& section ) :
      Base( { std::move( section ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] inelastic     the MF7 MT4 section
     *  @param[in] information   the MF7 MT451 section
     */
    Type( section::Type< 7, 4 >&& inelastic, section::Type< 7, 451 >&& information ) :
      Base( { std::move( inelastic ), std::move( information ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] elastic     the MF7 MT2 section
     *  @param[in] inelastic   the MF7 MT4 section
     */
    Type( section::Type< 7, 2 >&& elastic, section::Type< 7, 4 >&& inelastic ) :
      Base( { std::move( elastic ), std::move( inelastic ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] elastic     the MF7 MT2 section
     *  @param[in] inelastic   the MF7 MT4 section
     *  @param[in] information   the MF7 MT451 section
     */
    Type( section::Type< 7, 2 >&& elastic, section::Type< 7, 4 >&& inelastic,
          section::Type< 7, 451 >&& information ) :
      Base( { std::move( elastic ), std::move( inelastic ),
              std::move( information ) } ) {}

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
    static constexpr int fileNumber() { return 7; }

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
