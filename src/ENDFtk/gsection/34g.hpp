#ifndef NJOY_ENDFTK_GSECTION_34
#define NJOY_ENDFTK_GSECTION_34

// system includes
#include <numeric>
#include <map>
#include <algorithm>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "tools/Log.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template < >
  class ENDFTK_PYTHON_EXPORT GType< 34 > : protected Base {

    /* fields */
    int l_;
    int l1_;
    int irelco_;
    std::vector< std::vector< double > > ang_covr_;

    /* auxiliary functions */
    #include "ENDFtk/gsection/34/src/readRecords.hpp"
    #include "ENDFtk/gsection/34/src/makeRecords.hpp"
    #include "ENDFtk/gsection/34/src/makeMatrices.hpp"

  public:

    /* constructor */
    #include "ENDFtk/gsection/34/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the primary legendre order
     */
    int L() const {

      return this->l_;
    }

    /**
     *  @brief Return the primary legendre order
     */
    int primaryLegendre() const {

      return this->L();
    }

    /**
     *  @brief Return the secondary legendre order
     */
    int L1() const {

      return this->l1_;
    }

    /**
     *  @brief Return the secondary legendre order
     */
    int secondaryLegendre() const {

      return this->L1();
    }

    /**
     *  @brief Return the covariance format (0/1 -> abs./rel.)
     */
    int IRELCO() const {

      return this->irelco_;
    }

    /**
     *  @brief
     */
    int covarianceFormat() const {

      return this->IRELCO();
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int NGN() const {

      return this->ang_covr_.size();
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int numberNeutronGroups() const {

      return this->NGN();
    }

    /**
     * @brief Return the secondary angular distribution covariance matrix.
     */
    const std::vector< std::vector< double > >& angularCovariance() const{

      return this->ang_covr_;
    }

    #include "ENDFtk/gsection/34/src/print.hpp"

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::AWR;
    using Base::atomicWeightRatio;
  };

} // section
} // ENDFtk
} // njoy

#endif // NJOY_ENDFTK_GSECTION_34
