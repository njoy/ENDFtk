#ifndef NJOY_ENDFTK_TABULATIONRECORD
#define NJOY_ENDFTK_TABULATIONRECORD

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/iota.hpp"
#include "range/v3/view/subrange.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/view/zip.hpp"
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

  protected:

    auto regions( size_t index ) const {
      const auto left = index ? this->boundaries()[ index - 1 ] - 1 : 0;
      const auto right = this->boundaries()[ index ];
      return
        std::make_pair( ranges::make_subrange
                        ( this->xValues.begin() + left,
                          this->xValues.begin() + right ),
                        ranges::make_subrange
                        ( this->yValues.begin() + left,
                          this->yValues.begin() + right ) );
    }

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

    using InterpolationBase::NR;
    using InterpolationBase::numberInterpolationRegions;

    /**
     *  @brief Return the x values in the table
     */
    auto x() const {

      return ranges::cpp20::views::all( this->xValues );
    }

    /**
     *  @brief Return the y values in the table
     */
    auto y() const {

      return ranges::cpp20::views::all( this->yValues );
    }

    /**
     *  @brief Return the x,y pairs in the table
     */
    auto pairs() const {

      return ranges::views::zip( this->xValues, this->yValues );
    }

    using InterpolationBase::INT;
    using InterpolationBase::NBT;
    using InterpolationBase::interpolants;
    using InterpolationBase::boundaries;

    /**
     *  @brief Return the interpolation ranges
     */
    auto regions() const {

      return
        ranges::views::iota( 0ul, this->boundaries().size() )
        | ranges::cpp20::views::transform(
            [this ]( int i ){ return this->regions(i); } );
    }

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
