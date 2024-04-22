#ifndef NJOY_ENDFTK_INTERPOLATIONRECORD
#define NJOY_ENDFTK_INTERPOLATIONRECORD

// system includes

// other includes
#include "tools/Log.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief ENDF TAB2 record
   *
   *  The interpolation record is a multi-line ENDF record containing 2 doubles
   *  and 4 integers on the first line, followed by interpolation information
   *  on the following lines.
   *
   *  See ENDF102, section 1.1 for more information.
   */
  class InterpolationRecord : protected record::InterpolationBase {

  public:

    /* constructor */
    #include "ENDFtk/InterpolationRecord/src/ctor.hpp"

    /* methods */
    using InterpolationBase::C1;
    using InterpolationBase::C2;
    using InterpolationBase::L1;
    using InterpolationBase::L2;
    using InterpolationBase::NR;
    using InterpolationBase::numberInterpolationRegions;

    /**
     *  @brief Return the number of points
     */
    long NZ() const { return InterpolationBase::N2(); }

    using InterpolationBase::NBT;
    using InterpolationBase::INT;
    using InterpolationBase::interpolants;
    using InterpolationBase::boundaries;

    /**
     *  @brief Equality operator
     *
     *  @param[in] rhs   the interpolation record on the right
     */
    bool operator==( const InterpolationRecord& rhs ) const {

      return InterpolationBase::operator==( static_cast<const InterpolationBase&>( rhs ) );
    }

    /**
     *  @brief Not equal operator
     *
     *  @param[in] rhs   the interpolation record on the right
     */
    bool operator!=( const InterpolationRecord& rhs ) const {

      return not ( *this == rhs );
    }

    using record::InterpolationBase::NC;
    using record::InterpolationBase::print;
  };

  using TAB2 = InterpolationRecord;

} // ENDFtk namespace
} // njoy namespace

#endif
