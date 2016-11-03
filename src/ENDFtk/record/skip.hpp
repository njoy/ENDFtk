template< typename Iterator >
Tail skip( Iterator& begin, const Iterator& end, long& lineNumber ){
  try{
    Base< Character< 66 > >( begin, end );
    return Tail( begin, end, lineNumber );
  } catch( std::exception& e ){
    Log::info( "Error while skipping a record." );
    throw e;
  }
}

