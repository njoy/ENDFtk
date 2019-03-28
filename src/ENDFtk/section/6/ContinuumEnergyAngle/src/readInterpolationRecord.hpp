template< typename Iterator >
static InterpolationRecord
readInterpolationRecord( Iterator& begin,
                         const Iterator& end,
                         long& lineNumber,
                         int MAT,
                         int MF,
                         int MT ) {

  InterpolationRecord interpolation( begin, end, lineNumber, MAT, MF, MT );

  try {

    checkLANG( interpolation.L1() );
  }
  catch ( ... ) {

    Log::info( "Line number: {}", lineNumber - interpolation.NC() );
    throw;
  }

  return interpolation;
}

