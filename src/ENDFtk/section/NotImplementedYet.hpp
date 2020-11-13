#ifndef NJOY_ENDFTK_SECTION_NOTIMPLEMENTEDYET
#define NJOY_ENDFTK_SECTION_NOTIMPLEMENTEDYET

// system includes

// other includes
#include "ENDFtk/HeadRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template < typename Derived >
  class NotImplementedYet {

    using Text = record::Base< record::Character< 66 > >;
    using Tail = record::Tail;

  public:

    /* get methods */

    /**
     *  @brief Return the MF number of the section
     */
    constexpr int MF() const {

        return static_cast< const Derived* >( this )->fileNumber();
    }

    /**
     *  @brief Return the MT number of the section
     */
    constexpr int MT() const {

        return static_cast< const Derived* >( this )->sectionNumber();
    }

    /**
     *  @brief Placeholder for the print function - does nothing
     */
    template< typename OutputIterator >
    void print( OutputIterator&, int, int ) const { return; }

  protected:

    /* constructor */

    /**
     *  @brief Default constructor
     */
    NotImplementedYet() = default;

    /**
     *  @brief Constructor (from a buffer) - skips section
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    NotImplementedYet ( HEAD& head, Iterator& begin, const Iterator& end,
                        long& lineNumber, int ) {

      int MF = Derived::fileNumber();
      int MT = Derived::sectionNumber();
      if ( ( head.MF() == MF ) && ( head.MT() == MT ) ) {

        Log::info( "Found unsupported section MF{} MT{} - skipping section",
                   MF, MT );
        Tail tail( head.MAT(), head.MF(), head.MT() );
        while ( tail.MT() == MT ) {

          Text( begin, end );
          tail = Tail( begin, end, lineNumber );
        }
      }
    }
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
