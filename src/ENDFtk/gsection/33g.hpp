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
    std::map< std::size_t, std::vector< std::vector< double > > > covr_;

    /* auxiliary functions */
    #include "ENDFtk/gsection/33/src/makeMatrices.hpp"
    #include "ENDFtk/gsection/33/src/makeRecords.hpp"
    #include "ENDFtk/gsection/33/src/readRecords.hpp"
    #include "ENDFtk/gsection/33/src/verifySecondaryReaction.hpp"

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
    std::vector< std::size_t > secondaryReactions() const {

      std::vector< std::size_t > sec_rxns;
      sec_rxns.reserve( this->covr_.size() );
      for ( const auto& [sec_rxn, _ ] : this->covr_ ) {

          sec_rxns.push_back( sec_rxn );
      }
      return sec_rxns;
    }

    /**
     *  @brief Return the number of secondary reactions.
     */
    std::size_t NSMT() const {

      return this->covr_.size();
    }

    /**
     *  @brief Return the number of secondary reactions.
     */
    std::size_t numberSecondaryReactions() const {

      return this->NSMT();
    }

    /**
     *  @brief Return the covariance matrix for a given secondary reaction.
     *
     *  @param[in] secondary_rxn    the requested secondary reaction ( MT )
     */
    decltype(auto) covariance ( std::size_t secondary_rxn ) const {

      this->verifySecondaryReaction( secondary_rxn );
      if ( this->covr_.at( secondary_rxn).empty() ) {

        throw std::runtime_error( "Requested covariances when they are not present");
      }
      else{

        return this->covr_.at( secondary_rxn );
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