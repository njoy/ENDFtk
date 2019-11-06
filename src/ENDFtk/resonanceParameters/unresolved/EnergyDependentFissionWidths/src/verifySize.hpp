static void
verifySize( unsigned int NE, const std::vector< LValue >& lvalues ) {

  auto iter = ranges::find_if_not( lvalues, hana::equal.to( NE ),
                                   &LValue::NE );

  if ( iter != ranges::end( lvalues ) ) {

    Log::error( "All fission width functions must have the same size" );
    Log::info( "Expected NE={} for the l value with index={}", NE,
               ranges::distance( ranges::begin( lvalues ), iter ) );
    throw std::exception();
  }
}
