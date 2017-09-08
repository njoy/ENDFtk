class InterpolationRecord : protected record::InterpolationBase {

public:
#include "ENDFtk/InterpolationRecord/src/ctor.hpp"

  using InterpolationBase::C1;
  using InterpolationBase::C2;
  using InterpolationBase::L1;
  using InterpolationBase::L2;
  using InterpolationBase::NR;

  long NZ() const { return InterpolationBase::N2(); }

  using InterpolationBase::interpolants;
  using InterpolationBase::boundaries;

  bool operator==( const InterpolationRecord& rhs ) const {
    return ( InterpolationBase::operator==( static_cast<const InterpolationBase&>( rhs ) ) );
  }
    
  bool operator!=( const InterpolationRecord& rhs ) const {
    return not ( *this == rhs );
  }
};
