template< typename Iterator >
InterpolationSequenceRecord ( Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT ) :
  interpolation_( begin, end, lineNumber, MAT, MF, MT  ),
  sequence_( readSequence( begin, end, lineNumber, MAT, MF, MT,
                           this->interpolation_.NZ() ) ) {}

