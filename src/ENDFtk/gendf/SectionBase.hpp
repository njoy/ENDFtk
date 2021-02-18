#ifndef NJOY_ENDFTK_GENDF_SECTION
#define NJOY_ENDFTK_GENDF_SECTION

// system includes

// other includes
#include "ENDFtk/section/Base.hpp"
#include "ENDFtk/gendf/DataRecord.hpp"
#include "range/v3/view.hpp"

namespace njoy {
namespace ENDFtk {
namespace gendf {

  class SectionBase : public section::Base {

    /* fields */
    int num_legendre_;
    int num_dilutions_;
    int breakup_;
    int num_groups_;
    std::map< unsigned int, DataRecord > records_;


  protected:

    /* constructor */
    #include "ENDFtk/gendf/SectionBase/src/readRecords.hpp"
    #include "ENDFtk/gendf/SectionBase/src/mapRecords.hpp"
    #include "ENDFtk/gendf/SectionBase/src/verifyRecords.hpp"
    #include "ENDFtk/gendf/SectionBase/src/ctor.hpp"

  public:

    /* get methods */

    /**
     *  @brief The number of Legendre moments
     */
    unsigned int NL() const { return this->num_legendre_; }

    /**
     *  @brief The number of Legendre moments
     */
    unsigned int numLegendre() const { return this->NL(); }

    /**
     *  @brief The Legendre order
     */
    unsigned int legendreOrder() const { return this->NL()-1; }

    /**
     *  @brief The number of dilutions
     */
    unsigned int NZ() const { return this->num_dilutions_; }

    /**
     *  @brief The number of dilutions
     */
    unsigned int numDilutions() const { return this->NZ(); }

    /**
     *  @brief The number of dilutions
     */
    unsigned int numSigmaZeros() const { return this->NZ(); }

    /**
     *  @brief The number of groups
     */
    unsigned int NGN() const { return this->num_groups_; }

    /**
     *  @brief The number of groups
     */
    unsigned int numGroups() const { return this->NGN(); }

    /**
     *  @brief The complex breakup flag
     */
    int LRFLAG() const { return this->breakup_; }

    /**
     *  @brief The complex breakup flag
     */
    int complexBreakUp() const { return this->LRFLAG(); }


    /* convenience functions for accessing data */

    /**
     *  @brief View of the record data.
     */
    auto records() const { return ranges::view::values( this->records_ ); }

    /**
     *  @brief Return a DataRecord by group
     *
     *  @param[in] group    the group index
     */
    auto record( unsigned int group ) const { return this->records_.at( group ); }

    /**
     *  @brief Check if group has a DataRecord
     *
     *  @param[in] group    the group index
     */
    bool hasRecord( unsigned int group ) const {
      return this->records_ .find( group ) != this->records_ .end();
    }


  };

} // gendf namespace
} // ENDFtk namespace
} // njoy namespace

#endif
