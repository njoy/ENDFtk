#ifndef NJOY_ENDFTK_SECTION_2_153
#define NJOY_ENDFTK_SECTION_2_153

// system includes

// other includes
#include "range/v3/view/subrange.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF2 MT153 - internal NJOY section
   *
   *  See the NJOY manual, PURR for more information.
   */
  template<>
  class Type< 2, 153 > : protected BaseWithoutMT< Type< 2, 153 > > {

  public:

    #include "ENDFtk/section/2/153/Table.hpp"

  private:

    friend BaseWithoutMT< Type< 2, 153 > >;

    /* fields */
    unsigned int inelastic_comp_;
    unsigned int absorption_comp_;
    unsigned int nbin_;
    ListRecord data_;

    /* auxiliary functions */
    //#include "ENDFtk/section/2/152/src/generateList.hpp"
    //#include "ENDFtk/section/2/152/src/reaction.hpp"
    //#include "ENDFtk/section/2/152/src/verifySize.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/2/153/src/ctor.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 153; }

    /**
     *  @brief Return the inelastic competition
     */
    unsigned int IINEL() const { return this->inelastic_comp_; }

    /**
     *  @brief Return the inelastic competition
     */
    unsigned int inelasticCompetition() const { return this->IINEL(); }

    /**
     *  @brief Return the absorption competition
     */
    unsigned int IABSO() const { return this->inelastic_comp_; }

    /**
     *  @brief Return the absorption competition
     */
    unsigned int absorptionCompetition() const { return this->IABSO(); }

    /**
     *  @brief Return the number of bins in the probability tables
     */
    unsigned int NBIN() const { return this->inelastic_comp_; }

    /**
     *  @brief Return the number of bins in the probability tables
     */
    unsigned int numberBins() const { return this->NBIN(); }

    /**
     *  @brief Return the self-shielding only flag
     */
    bool LSSF() const { return this->data_.L1(); }

    /**
     *  @brief Return the self-shielding only flag
     */
    bool selfShieldingOnly() const { return this->LSSF(); }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;

    #include "ENDFtk/section/2/153/src/print.hpp"
    //#include "ENDFtk/section/2/153/src/NC.hpp"
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
