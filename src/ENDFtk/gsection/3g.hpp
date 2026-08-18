#ifndef NJOY_ENDFTK_GSECTION_3
#define NJOY_ENDFTK_GSECTION_3

// system includes
#include <numeric>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/section.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  //! @todo for now, errorr sections get printed as errorr sections. do we keep this?

  template <>
  class ENDFTK_PYTHON_EXPORT GType< 3 > : protected Base {

    /* fields */
    int lr_;
    double temp_;
    std::vector< unsigned int > groups_;

    // format flag: groupr (true), errorr (false)
    bool groupr_;

    // data is stored by moment and dilution
    std::vector< std::vector< std::vector< double > > > flux_;
    std::vector< std::vector< std::vector< double > > > sigma_;
    std::vector< std::vector< std::vector< double > > > ratio_;

    /* auxiliary functions */
    #include "ENDFtk/gsection/3/src/makeVectors.hpp"
    #include "ENDFtk/gsection/3/src/makeRecords.hpp"
    #include "ENDFtk/gsection/3/src/readRecords.hpp"
    #include "ENDFtk/gsection/3/src/verifySize.hpp"
    #include "ENDFtk/gsection/3/src/verifyIndex.hpp"

  public:

    /* constructor */
    #include "ENDFtk/gsection/3/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of legendre moments
     */
    int NL() const {

      return this->sigma_.size();
    }

    /**
     *  @brief Return the number of legendre moments
     */
    int numberMoments() const {

      return this->NL();
    }

    /**
     *  @brief Return the number of dilution values
     */
    int NZ() const {

      return this->sigma_.front().size();
    }

    /**
     *  @brief Return the number of dilution values
     */
    int numberDilutions() const {

      return this->NZ();
    }

    /**
     *  @brief Return the break up flag
     */
    int LR() const {

      return this->lr_;
    }

    /**
     *  @brief Return the break up identifier flag
     */
    int breakUp() const {

      return this->LR();
    }

    /**
     *  @brief Return whether or not this is a GROUPR formatted section
     */
    bool isGroupr() const {

      return this->groupr_;
    }

    /**
     *  @brief Return whether or not this is an ERRORR formatted section
     */
    bool isErrorr() const {

      return ! this->isGroupr();
    }

    /**
     *  @brief Return the number of neutron groups
     */
    int NGN() const {

      return this->sigma_.front().front().size();
    }

    /**
     *  @brief Return the number of neutron groups
     */
    int numberNeutronGroups() const {

      return this->NGN();
    }

    /**
     *  @brief Return the temperature
     */
    double temperature() const {

      return this->temp_;
    }

    /**
     *  @brief Return the multigroup cross section for a given moment and dilution
     *
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    const std::vector< double >& crossSection( std::size_t moment, std::size_t dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->sigma_[moment][dilution];
    }

    /**
     *  @brief Return the multigroup ratio data for a given moment and dilution
     *
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    const std::vector< double >& ratio( std::size_t moment, std::size_t dilution ) const {

      if (this->ratio_.size() != 0) {

        this->verifyIndex( moment, dilution );
        return this->ratio_[moment][dilution];
      }
      else {

        throw std::runtime_error( "Requested ratio when ratios are not present!" );
      }
    }

    /**
     *  @brief Return the group fluxes
     *
     *  @param[in] moment     the legendre moment requested
     *  @param[in] dilution   the dilution index requested
     */
    const std::vector< double >& flux( std::size_t moment, std::size_t dilution ) const {

      this->verifyIndex( moment, dilution );
      return this->flux_[moment][dilution];
    }

    #include "ENDFtk/gsection/3/src/print.hpp"

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

#endif