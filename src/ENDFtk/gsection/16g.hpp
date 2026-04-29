#ifndef NJOY_ENDFTK_GSECTION_16
#define NJOY_ENDFTK_GSECTION_16

// system includes
#include <numeric>
#include <algorithm>

// other includes
#include "ENDFtk/macros.hpp"
#include "tools/std20/views.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "tools/Log.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template < >
  class ENDFTK_PYTHON_EXPORT GType< 16 > : protected Base {

    /* fields */
    int lr_;
    int ngn_;
    double temp_;
    std::vector< std::vector< std::vector< double > > > flux_;
    std::vector< std::vector< std::vector< std::vector< double > > > > matrix_;

    /* auxiliary functions */
    #include "ENDFtk/gsection/16/src/verifySize.hpp"
    #include "ENDFtk/gsection/16/src/makeMatrices.hpp"
    #include "ENDFtk/gsection/16/src/makeRecords.hpp"
    #include "ENDFtk/gsection/16/src/readRecords.hpp"
    #include "ENDFtk/gsection/6/src/verifyIndex.hpp" // taken from MF6

  public:

    /* constructor */
    #include "ENDFtk/gsection/16/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of legendre moments.
     */
    int NL() const { return this->flux_.size(); }

    /**
     *  @brief Return the number of legendre moments.
     */
    int numberMoments() const { return this->NL(); }

    /**
     *  @brief Return the number of dilution values.
     */
    int NZ() const { return this->flux_.front().size(); }

    /**
     *  @brief Return the number of dilution values
     */
    int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief Return the break up identifier flag.
     */
    int LRFLAG() const { return this->lr_; }

    /**
     *  @brief Return the break up identifier flag.
     */
    int breakUpID() const { return this->LRFLAG(); }

    /**
     *  @brief Return the number of neutron energy bins
     */
    int NGN() const { return this->ngn_; }

    /**
     *  @brief Return the number of neutron energy bins
     */
    int numberNeutronGroups() const { return this->NGN(); }

    /**
     *  @brief Return the temperature
     */
    double TEMP() const { return this->temp_; }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMP(); }

    /**
     *  @brief Return the matrix for a given moment and dilution
     *
     *  @param[in] moment   the legendre moment requested
     *  @param[in] diltuion the dilution index requested
     */
    decltype(auto) matrix( int moment, int dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->matrix_[ moment ][ dilution ];
    }

    /**
     *  @brief Return the flux
     *
     *  @param[in] moment   the legendre moment requested
     *  @param[in] dilution the dilution index requested
     */
    decltype(auto) flux( int moment, int dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->flux_[ moment ][ dilution ];
    }

    #include "ENDFtk/gsection/16/src/print.hpp"

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

#endif // NJOY_ENDFTK_GSECTION_16