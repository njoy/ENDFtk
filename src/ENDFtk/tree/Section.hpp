#ifndef NJOY_ENDFTK_TREE_SECTION
#define NJOY_ENDFTK_TREE_SECTION

// system includes

// other includes
#include "boost/hana.hpp"
#include "range/v3/all.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {

  namespace hana = boost::hana;
  
namespace tree {

  template< typename BufferIterator >
  class Section {
  public:
    /* fields */
    int sectionNo;
    int fileNo;
    std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* methods */
    #include "ENDFtk/tree/Section/src/ctor.hpp"
    #include "ENDFtk/tree/Section/src/findEnd.hpp"
    #include "ENDFtk/tree/Section/src/parse.hpp"

    /* methods */
    int MT() const { return this->sectionNo; }
    int sectionNumber() const { return this->MT(); }
    int MF() const { return this->fileNo; }
    int fileNumber() const { return this->MF(); }
    auto buffer() const {
      return ranges::make_iterator_range( this->bufferLimits.first,
                                          this->bufferLimits.second );
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
