#ifndef NJOY_ENDFTK_FILE_TYPE
#define NJOY_ENDFTK_FILE_TYPE

// system includes

// other includes
#include "ENDFtk/section.hpp"
#include "ENDFtk/file/Base.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  /**
   *  @class
   *  @brief Generic file class
   */
  template< int FileNumber >
  class Type : protected Base< Type< FileNumber >, section::Type< FileNumber > > {

    friend class Base< Type, section::Type< FileNumber > >;
    using Parent = Base< Type, section::Type< FileNumber > >;

    /* auxiliary functions */

    static auto getSectionNumber( const section::Type< FileNumber >& section ) {

      return section.MT();
    }

    template< typename OutputIterator >
    static void printSection( const section::Type< FileNumber >& section,
                              OutputIterator& it, int MAT, int MF ) {

      section.print( it, MAT, MF );
    }

    template< typename Iterator >
    static auto
    readSection( StructureDivision& division,
                 Iterator& begin,
                 const Iterator& end,
                 long& lineNumber ) {

      return section::Type< FileNumber >( asHead( division ), begin, end,
                                          lineNumber, division.tail.MAT() );
    }

  public :

    /* constructors */

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
     *  @param[in] sections   the sections of the file
     */
    Type( std::vector< section::Type< FileNumber > >&& sections ) :
      Parent( std::move( sections ) ) {}

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
      Parent( division, begin, end, lineNumber ) {}

    /* methods */

    /**
     *  @brief Return the file number
     */
    static int fileNumber() { return FileNumber; }

    using Parent::MF;
    using Parent::sections;
    using Parent::MTs;
    using Parent::begin;
    using Parent::end;
    using Parent::hasMT;
    using Parent::hasSection;
    using Parent::section;
    using Parent::MT;
    using Parent::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
