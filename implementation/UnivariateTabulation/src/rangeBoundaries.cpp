#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

std::tuple< TAB1::constXIterator, TAB1::constXIterator >
TAB1::rangeBoundaries( std::size_t rangeIndex ) const {
  if ( std::size_t(this->nRanges()) <= rangeIndex ){
    LOG(ERROR) << "Out of range range index requested of TAB1 record";
    LOG(INFO) << "Requested index: " << index;
    LOG(INFO) << "Available index range: [ 0, "
              << this->boundaryIndices.size() << " )";
    throw std::out_of_range("");
  }
  const bool isFirstRange = ( rangeIndex == 0 );
  const std::size_t right = this->boundaryIndices[ rangeIndex-- ];
  const std::size_t
    left = ( isFirstRange ) ? 0 : this->boundaryIndices[ rangeIndex ] - 1;
  return std::make_tuple( this->xBegin() + left, this->xBegin() + right );
}
