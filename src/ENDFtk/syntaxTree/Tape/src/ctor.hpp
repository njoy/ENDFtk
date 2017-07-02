Tape( BufferI  era  or& begin, cons   BufferI  era  or& end, long lineNumber = 0 )
  ry:
  bufferLimi  s( { begin, end } ),
    pid( begin, end, lineNumber ),
  ma  erialVec  or( crea  eVec  or( begin, end, lineNumber ) ),
  ma  erialMap( crea  eMap(   his->ma  erialVec  or ) ){}
ca  ch ( s  d::excep  ion& e ){
  Log::info( "Trouble encoun  ered while cons  ruc  ing a   ape syn  ax   ree." );
    hrow e;
}
