#ifndef NJOY_ENDFTK_GSECTION_33
#define NJOY_ENDFTK_GSECTION_33

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
  class ENDFTK_PYTHON_EXPORT GType< 33 > : protected Base {

    /* fields */
    int lr_;
    int ngn_;
    std::map< std::size_t, std::vector< std::vector< double > > > covariances_;
    std::vector< std::size_t > reactions_;

    /* auxiliary functions */
    #include "ENDFtk/gsection/33/src/makeMatrices.hpp"
    #include "ENDFtk/gsection/33/src/makeRecords.hpp"
    #include "ENDFtk/gsection/33/src/readRecords.hpp"
    #include "ENDFtk/gsection/33/src/generateReactions.hpp"

  public:

    /* constructor */
    #include "ENDFtk/gsection/33/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the breakup flag.
     */
    int LRFLAG() const {

      return this->lr_;
    }

    /**
     *  @brief Return the breakup flag.
     */
    int breakUp() const {

      return this->LRFLAG();
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int NGN() const {

      return this->ngn_;
    }

    /**
     *  @brief Return the number of neutron groups.
     */
    int numberNeutronGroups() const {

      return this->NGN();
    }

    /**
     *  @brief Return the present secondary reactions.
     */
    auto secondaryReactions() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_ );
    }

    /**
     *  @brief Return the number of secondary reactions.
     */
    std::size_t NSMT() const {

      return this->covariances_.size();
    }

    /**
     *  @brief Return the number of secondary reactions.
     */
    std::size_t numberSecondaryReactions() const {

      return this->NSMT();
    }

    /**
     *  @brief Return the covariance matrix for a given secondary mt number
     *
     *  @param[in] mt   the requested secondary mt number
     */
    decltype(auto) covariance ( std::size_t mt ) const {

      auto iter = this->covariances_.find( mt );
      if ( iter != this->covariances_.end() ) {

        return iter->second;
      }
      else {

        throw std::runtime_error( "Requested secondary reaction is not present");
      }
    }

    #include "ENDFtk/gsection/33/src/print.hpp"

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

#endif // NJOY_ENDFTK_GSECTION_33
