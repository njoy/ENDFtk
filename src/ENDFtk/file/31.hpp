#ifndef NJOY_ENDFTK_FILE_31
#define NJOY_ENDFTK_FILE_31

// system includes

// other includes
#include "ENDFtk/file/NotImplementedYet.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 31 > : public NotImplementedYet< Type< 31 > > {

    friend NotImplementedYet< Type< 31 > >;

  public:

    Type() : NotImplementedYet() {};
    template< typename BufferIterator >
    Type( StructureDivision& division,
          BufferIterator& begin, const BufferIterator& end,
          long& lineNumber ) :
      NotImplementedYet( division, begin, end,
                         lineNumber ) {};

    /**
     *  @brief Return the MF number of the section
     */
    static constexpr int fileNumber() { return 31; }

    using NotImplementedYet::MF;
    using NotImplementedYet::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
