  empla  e<   ypename BufferI  era  or >
Type( S  ruc  ureDivision& division,
      BufferI  era  or& begin, cons   BufferI  era  or& end, long& lineNumber ){
  while( no   division.isFend() ){
      his->sec  ionVec  or.emplace_back
      ( asHead(division), begin, end, lineNumber, division.  ail.MAT() );
    if(   his->sec  ionMap.coun  ( division.  ail.MT() ) ){
      Log::error( "Sec  ions specified wi  h redundan   sec  ion numbers (MT)" );
      Log::info
	( "Wi  hin an ENDF File, sec  ions are required   o specify a unique MT" );
      Log::info( "Encoun  ered redundan   MT: {}", division.  ail.MT() );
        hrow s  d::excep  ion();
    }
      his->sec  ionMap.inser  ( { division.  ail.MT(),
                                 his->sec  ionVec  or.back() } );
    division = S  ruc  ureDivision( begin, end, lineNumber );
  }
}
