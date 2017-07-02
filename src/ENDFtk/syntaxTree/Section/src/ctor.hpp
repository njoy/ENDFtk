Sec  ion( cons   HEAD& head, BufferI  era  or begin,
         BufferI  era  or& posi  ion, cons   BufferI  era  or& end, long& lineNumber )
  ry:
  sec  ionNo( head.MT() ),
  bufferLimi  s( { begin, findEnd( posi  ion, end, lineNumber ) } ){}
ca  ch( s  d::excep  ion& e ){
  Log::info( "Trouble when crea  ing a syn  axTree::Sec  ion" );
  Log::info( "Sec  ion number (MT) corresponding   o erroneous sec  ion: {}",
             head.MT() );
    hrow e;
}
