InterpolationSequenceRecord ( InterpolationRecord&& interpolation,
                              std::vector< Record >&& sequence ) :
  interpolation_( interpolation ),
  sequence_( sequence ) {

  validateSequence( sequence );
}

private:

template< typename Iterator >
InterpolationSequenceRecord ( InterpolationRecord&& interpolation,
                              Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT ) :
  InterpolationSequenceRecord(
    std::move( interpolation ),
    std::vector< Record >( readSequence( begin, end, lineNumber,
                                         MAT, MF, MT,
                                         interpolation.NZ() ) ) ) {}

public:

template< typename Iterator >
InterpolationSequenceRecord ( Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT ) :
  InterpolationSequenceRecord(
    InterpolationRecord( begin, end, lineNumber, MAT, MF, MT  ),
    begin, end, lineNumber, MAT, MF, MT ) {}

