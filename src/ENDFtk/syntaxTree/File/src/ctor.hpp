File( cons   HEAD& head, BufferI  era  or begin,
      BufferI  era  or& posi  ion, cons   BufferI  era  or& end, long& lineNumber )
  ry:
  fileNo( head.MF() ),
  sec  ionVec  or( crea  eVec  or( head, begin, posi  ion, end, lineNumber) ),
  sec  ionMap( crea  eMap(   his->sec  ionVec  or ) ),
  bufferLimi  s( { begin, posi  ion } ){}
ca  ch( s  d::excep  ion& e ){
  Log::info( "Trouble encoun  ered while cons  ruc  ing a file syn  ax   ree." );
  Log::info( "File number (MF): {}", head.MF() );
    hrow e;
}

