/**
 *  @brief Function to read an interpolation sequence using an ENDF component
 *
 *  @tparam Component        an ENDF component
 *  @tparam Iterator         an input iterator
 *
 *  This function requires the ENDF component to have a read style constructor.
 */
template< typename Component, typename Iterator >
InterpolationSequenceRecord< Component >
readInterpolationSequenceRecord( Iterator& begin,
                                 const Iterator& end,
                                 long& lineNumber,
                                 int MAT,
                                 int MF,
                                 int MT ) {

  InterpolationRecord interpolation( begin, end, lineNumber, MAT, MF, MT );
  return InterpolationSequenceRecord(
             std::move( interpolation ),
             readSequence< Component >( begin, end, lineNumber, MAT, MF, MT,
                                        interpolation.NZ() ) );
}
