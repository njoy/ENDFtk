#ifndef NJOY_ENDFTK_GENDF_SECTION
#define NJOY_ENDFTK_GENDF_SECTION

// system includes

// other includes
#include "ENDFtk/section/Base.hpp"

namespace njoy {
namespace ENDFtk {
namespace gendf {

  class SectionBase : public section::Base {

    /* fields */
    int num_legendre_;
    int num_dilutions_;
    int breakup_;
    int num_groups_;

  protected:

    /* constructor */
    #include "ENDFtk/gendf/SectionBase/src/ctor.hpp"

  public:

    /* get methods */

    /**
     *  @brief The number of Legendre moments
     */
    int NL() const { return this->num_legendre_; }

    /**
     *  @brief The number of Legendre moments
     */
    int numLegendre() const { return this->NL(); }

    /**
     *  @brief The Legendre order
     */
    int legendreOrder() const { return this->NL()-1; }

    /**
     *  @brief The number of dilutions
     */
    int NZ() const { return this->num_dilutions_; }

    /**
     *  @brief The number of dilutions
     */
    int numDilutions() const { return this->NZ(); }

    /**
     *  @brief The number of dilutions
     */
    int numSigmaZeros() const { return this->NZ(); }

    /**
     *  @brief The number of groups
     */
    int NGN() const { return this->num_groups_; }

    /**
     *  @brief The number of groups
     */
    int numGroups() const { return this->NGN(); }

    /**
     *  @brief The complex breakup flag
     */
    int LRFLAG() const { return this->breakup_; }

    /**
     *  @brief The complex breakup flag
     */
    int complexBreakUp() const { return this->LRFLAG(); }


  };

} // gendf namespace
} // ENDFtk namespace
} // njoy namespace

#endif
