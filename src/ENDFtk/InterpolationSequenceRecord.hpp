template < typename Record >
void validateSequence( const std::vector< Record >& ) { return; }

template < typename Record >
class InterpolationSequenceRecord {

  /* fields */
  InterpolationRecord interpolation_;
  std::vector< Record > sequence_;

  /* auxiliary functions */
#include "ENDFtk/InterpolationSequenceRecord/src/readSequence.hpp"

public:
  /* constructor */
#include "ENDFtk/InterpolationSequenceRecord/src/ctor.hpp"

  /* get methods */
  const InterpolationRecord& tab2() const { return this->interpolation_; }

  auto records() const {
    return ranges::make_iterator_range( this->sequence_.begin(),
                                        this->sequence_.end() );
  }

#include "ENDFtk/InterpolationSequenceRecord/src/NC.hpp"

#include "ENDFtk/InterpolationSequenceRecord/src/print.hpp"

};

