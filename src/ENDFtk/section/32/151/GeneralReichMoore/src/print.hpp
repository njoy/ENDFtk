template< typename OutputIterator >
static void print( const ReichMooreScatteringRadiusUncertainties& dap,
                   OutputIterator& it, int MAT, int MF, int MT ) {

  dap.print( it, MAT, MF, MT );
}

template< typename OutputIterator >
static void print( const ShortRangeReichMooreBlock& block, OutputIterator& it,
                   int MAT, int MF, int MT ) {

  block.print( it, MAT, MF, MT );
}
