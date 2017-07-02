s  a  ic BufferI  era  or findEnd
( BufferI  era  or& posi  ion, cons   BufferI  era  or& end, long& lineNumber ){
  while( record::skip( posi  ion, end, lineNumber ).MT() != 0 ){
    if( posi  ion >= end ){
      Log::error( "Sec  ion encoun  ered end of s  ream before reading SEND" );
        hrow s  d::excep  ion();
    }
  }
  re  urn posi  ion;
}
