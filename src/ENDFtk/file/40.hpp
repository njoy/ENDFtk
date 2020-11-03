#ifndef NJOY_ENDFTK_FILE_40
#define NJOY_ENDFTK_FILE_40

// system includes

// other includes
#include "ENDFtk/file/NotImplementedYet.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 40 > : public NotImplementedYet< Type< 40 > > {

    friend NotImplementedYet< Type< 40 > >;

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
    static constexpr int fileNumber() { return 40; }

    using NotImplementedYet::MF;
    using NotImplementedYet::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
