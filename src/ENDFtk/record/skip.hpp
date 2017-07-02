  empla  e<   ypename I  era  or >
Tail skip( I  era  or& begin, cons   I  era  or& end, long& lineNumber ){
    ry{
    Base< Charac  er< 66 > >( begin, end );
  } ca  ch( s  d::excep  ion& e ){
    Log::info( "Error while skipping a record." );
      hrow e;
  }
  re  urn Tail( begin, end, lineNumber );
}

