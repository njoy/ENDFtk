#ifndef NJOY_ENDFTK_TREE_SECTION
#define NJOY_ENDFTK_TREE_SECTION

// system includes

// other includes
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/TextRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree section
   *
   *  This class represents a single section in an ENDF tape, it is the smallest
   *  piece available in the ENDF tree prior to parsing it.
   */
  class Section {

    /* fields */
    int mat_;
    int mf_;
    int mt_;
    std::string content_;

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
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return MAT number of the section
     */
    int materialNumber() const { return this->MAT(); }
    /**
     *  @brief Return MF number of the section
     */
    int MF() const { return this->mf_; }

    /**
     *  @brief Return MF number of the section
     */
    int fileNumber() const { return this->MF(); }

    /**
     *  @brief Return MT number of the section
     */
    int MT() const { return this->mt_; }

    /**
     *  @brief Return MT number of the section
     */
    int sectionNumber() const { return this->MT(); }

    /**
     *  @brief Return the section's content
     */
    const std::string& content() const { return this->content_; }

    /**
     *  @brief Return the number lines in the section
     */
    unsigned int NC() const {

      // count all newline characters, subtract 1 for the SEND record
      return std::count( this->content_.begin(), this->content_.end(), '\n' ) - 1;
    }

    #include "ENDFtk/tree/Section/src/clean.hpp"
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
