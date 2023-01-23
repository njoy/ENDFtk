template< typename OutputIterator >
static void print( double dap, OutputIterator& it, int MAT, int MF, int MT ) {

  ControlRecord( dap, 0., 0, 0, 0, 0 ).print( it, MAT, MF, MT );
}
