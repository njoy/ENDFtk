static void
verifyBoundary( double left, double right ) {

  if ( left != right ) {

    Log::error( "The upper energy limit for the Legendre distributions "
    	          "does not line up with the lower boundary for the "
    	          "tabulated distributions" );
    Log::info( "Expected initial energy equal to {}", left );
    Log::info( "Found {}", right );
    throw std::exception();
  }
}
