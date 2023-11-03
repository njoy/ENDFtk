template< typename OutputIterator >
static void print( double dap, OutputIterator& it, int MAT, int MF, int MT ) {

  ControlRecord( 0., dap, 0, 0, 0, 0 ).print( it, MAT, MF, MT );
}

template< typename OutputIterator >
static void print( const ShortRangeBreitWignerBlock& block, OutputIterator& it,
                   int MAT, int MF, int MT ) {

  block.print( it, MAT, MF, MT );
}
