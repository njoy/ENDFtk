#ifndef NJOY_ENDFTK_TREE_SECTION
#define NJOY_ENDFTK_TREE_SECTION

// system includes

// other includes
#include "boost/hana.hpp"
#include "range/v3/view/subrange.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/section.hpp"
#include "boost/hana.hpp"

namespace njoy {
namespace ENDFtk {

  // hana namespace declaration inside ENDFtk
  namespace hana = boost::hana;
  inline namespace literals { using namespace hana::literals; }

namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree section
   *
   *  This class represents a single section in an ENDF tape, it is the smallest
   *  piece available in the ENDF tree prior to parsing it.
   */
  template< typename BufferIterator >
  class Section {

    /* fields */
    int materialNo;
    int fileNo;
    int sectionNo;
    std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* auxiliary function */
    #include "ENDFtk/tree/Section/src/findEnd.hpp"

  public:

    /* constructor */
    #include "ENDFtk/tree/Section/src/ctor.hpp"

    /* methods */
    #include "ENDFtk/tree/Section/src/parse.hpp"

    /**
     *  @brief Return MAT number of the section
     */
    int MAT() const { return this->materialNo; }

    /**
     *  @brief Return MAT number of the section
     */
    int materialNumber() const { return this->MAT(); }
    /**
     *  @brief Return MF number of the section
     */
    int MF() const { return this->fileNo; }

    /**
     *  @brief Return MF number of the section
     */
    int fileNumber() const { return this->MF(); }

    /**
     *  @brief Return MT number of the section
     */
    int MT() const { return this->sectionNo; }

    /**
     *  @brief Return MT number of the section
     */
    int sectionNumber() const { return this->MT(); }

    /**
     *  @brief Return the section's buffer
     */
    auto buffer() const {
      return ranges::make_subrange( this->bufferLimits.first,
                                    this->bufferLimits.second );
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
