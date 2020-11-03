#ifndef NJOY_ENDFTK_FILE_NOTIMPLEMENTEDYET
#define NJOY_ENDFTK_FILE_NOTIMPLEMENTEDYET

// system includes

// other includes
#include "ENDFtk/HeadRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template < typename Derived >
  class NotImplementedYet {

  public:

    /* get methods */

    /**
     *  @brief Return the MF number of the section
     */
    constexpr int MF() const {

        return static_cast< const Derived* >( this )->fileNumber();
    }

    /**
     *  @brief Placeholder for the print function - does nothing
     */
    template< typename OutputIterator >
    void print( OutputIterator&, int ) const { return; }

  protected:

    /* constructor */

    /**
     *  @brief Default constructor
     */
    NotImplementedYet() = default;

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
    template< typename BufferIterator >
    NotImplementedYet ( StructureDivision& division,
                        BufferIterator& begin, const BufferIterator& end,
                        long& lineNumber ) {

      int MF = Derived::fileNumber();
      if ( division.tail.MF() == MF ) {

        Log::info( "Found unsupported file MF{} - skipping file", MF );
        while ( division.tail.MF() == MF ) {

          division = StructureDivision( begin, end, lineNumber );
        }
      }
    }
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
