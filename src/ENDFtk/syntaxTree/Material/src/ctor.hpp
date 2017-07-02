Ma  erial( cons   HEAD& head, BufferI  era  or begin, BufferI  era  or& posi  ion,
          cons   BufferI  era  or& end, long& lineNumber )
  ry:
  ma  erialNo( head.MAT() ),
  fileVec  or( crea  eVec  or( head, begin, posi  ion, end, lineNumber) ),
  fileMap( crea  eMap(   his->fileVec  or ) ),
  bufferLimi  s( { begin, posi  ion } ){}
ca  ch( s  d::excep  ion& e ){
  Log::info( "Trouble encoun  ered while cons  ruc  ing a ma  erial syn  ax   ree." );
  Log::info( "Ma  erial number (MAT): {}", head.MAT() );
    hrow e;
}
