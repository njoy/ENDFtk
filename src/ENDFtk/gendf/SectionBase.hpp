#ifndef NJOY_ENDFTK_GENDF_SECTIONBASE
#define NJOY_ENDFTK_GENDF_SECTIONBASE

// system includes

// other includes
#include "ENDFtk/section/Base.hpp"
#include "ENDFtk/gendf/DataRecord.hpp"
#include "range/v3/view.hpp"

namespace njoy {
namespace ENDFtk {
namespace gendf {

  class SectionBase : protected section::Base {

  protected:

    /* fields */
    int num_legendre_;
    int num_dilutions_;
    int breakup_;
    int num_groups_;
    std::map< unsigned int, DataRecord > records_;

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
    unsigned int numberLegendreMoments() const { return this->NL(); }

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
    unsigned int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief The number of dilutions
     */
    unsigned int numberSigmaZeros() const { return this->NZ(); }

    /**
     *  @brief The number of groups
     */
    unsigned int NGN() const { return this->num_groups_; }

    /**
     *  @brief The number of groups
     */
    unsigned int numberGroups() const { return this->NGN(); }

    /**
     *  @brief The complex breakup flag
     */
    int LR() const { return this->breakup_; }

    /**
     *  @brief The complex breakup flag
     */
    int complexBreakUp() const { return this->LR(); }


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
    const auto& record( unsigned int group ) const {
      return this->records_.at( group );
    }

    /**
     *  @brief Check if group has a DataRecord
     *
     *  @param[in] group    the group index
     */
    bool hasRecord( unsigned int group ) const {
      return this->records_.find( group ) != this->records_ .end();
    }

    #include "ENDFtk/gendf/SectionBase/src/checkBounds.hpp"

    /**
     *  @brief Convenience function for extracting a value from
     *         a block of a DataRecord
     *
     *  @param[in] block    the block index
     *  @param[in] group    the group index
     *  @param[in] order    the Legendre order
     *  @param[in] dilution the dilution index
     */
    double getValue( unsigned int block, unsigned int group,
                     unsigned int order, unsigned int dilution ) const {

      // default value
      if ( !this->hasRecord(group) ) {
        return 0.0;
      }

      // from list
      const auto& values = this->record( group ).data( block );
      return values[ this->num_legendre_ * dilution + order ];
    }

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::AWR;
    using Base::atomicWeightRatio;

  };

} // gendf namespace
} // ENDFtk namespace
} // njoy namespace

#endif
