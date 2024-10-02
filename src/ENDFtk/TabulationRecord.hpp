#ifndef NJOY_ENDFTK_TABULATIONRECORD
#define NJOY_ENDFTK_TABULATIONRECORD

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief ENDF TAB1 record
   *
   *  The tabulation record is a multi-line ENDF record containing 2 doubles
   *  and 4 integers on the first line, followed by a interpolation data and a
   *  list of x,y values on the following lines.
   *
   *  See ENDF102, section 1.1 for more information.
   */
  class TabulationRecord : protected record::InterpolationBase {

    /* fields */
    std::vector< double > xValues;
    std::vector< double > yValues;

    /* helper methods */
    #include "ENDFtk/TabulationRecord/src/verifyVectorSizes.hpp"
    #include "ENDFtk/TabulationRecord/src/verifyXValuesAreSorted.hpp"
    #include "ENDFtk/TabulationRecord/src/verifyNP.hpp"
    #include "ENDFtk/TabulationRecord/src/readPairs.hpp"

  public:

    /* constructor */
    #include "ENDFtk/TabulationRecord/src/ctor.hpp"

    /* methods */
    using InterpolationBase::C1;
    using InterpolationBase::C2;
    using InterpolationBase::L1;
    using InterpolationBase::L2;

    /**
     *  @brief Return the number of points in the table
     */
    long NP() const { return this->xValues.size(); }

    /**
     *  @brief Return the number of points in the table
     */
    long numberPoints() const { return this->NP(); }

    using InterpolationBase::NR;
    using InterpolationBase::numberInterpolationRegions;

    /**
     *  @brief Return the x values in the table
     */
    auto x() const {

      using namespace njoy::tools;
      return std20::views::all( this->xValues );
    }

    /**
     *  @brief Return the y values in the table
     */
    auto y() const {

      using namespace njoy::tools;
      return std20::views::all( this->yValues );
    }

    using InterpolationBase::INT;
    using InterpolationBase::NBT;
    using InterpolationBase::interpolants;
    using InterpolationBase::boundaries;

    /**
     *  @brief Equality operator
     *
     *  @param[in] rhs   the tabulation record on the right
     */
    bool operator==( const TabulationRecord& rhs ) const {

        return ( InterpolationBase::operator==( static_cast<const InterpolationBase&>( rhs ) ) )
        and ( this->xValues == rhs.xValues )
        and ( this->yValues == rhs.yValues );
    }

    /**
     *  @brief Not equal operator
     *
     *  @param[in] rhs   the list record on the right
     */
    bool operator!=( const TabulationRecord& rhs ) const {

      return not ( *this == rhs );
    }

    /**
     *  @brief Return the number of lines in this record
     */
    long NC() const {

      return record::InterpolationBase::NC() + ( this->NP() + 2 ) / 3;
    }

    #include "ENDFtk/TabulationRecord/src/print.hpp"
  };

  using TAB1 = TabulationRecord;

} // ENDFtk namespace
} // njoy namespace

#endif
