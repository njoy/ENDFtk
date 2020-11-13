#ifndef NJOY_ENDFTK_FILE_15
#define NJOY_ENDFTK_FILE_15

// system includes

// other includes
#include "ENDFtk/file/NotImplementedYet.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 15 > : public NotImplementedYet< Type< 15 > > {

    friend NotImplementedYet< Type< 15 > >;

  public:

    Type() : NotImplementedYet() {}
    template< typename BufferIterator >
    Type( StructureDivision& division,
          BufferIterator& begin, const BufferIterator& end,
          long& lineNumber ) :
      NotImplementedYet( division, begin, end,
                         lineNumber ) {}

    /**
     *  @brief Return the MF number of the section
     */
    static constexpr int fileNumber() { return 15; }

    using NotImplementedYet::MF;
    using NotImplementedYet::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
