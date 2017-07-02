  empla  e<   ypename BufferI  era  or >
class Ma  erial {
public:
  /* convenience   ypedefs */
  using File_   = File< BufferI  era  or >;
  using I  era  or =   ypename s  d::vec  or< File_   >::i  era  or;
  
  /* fields */
  in   ma  erialNo;         
  s  d::vec  or< File_   > fileVec  or;
  s  d::unordered_map< in  , File_  & > fileMap;
  s  d::pair< BufferI  era  or, BufferI  era  or > bufferLimi  s;

  /* c  or */
#include "ENDF  k/syn  axTree/Ma  erial/src/crea  eVec  or.hpp"
#include "ENDF  k/syn  axTree/Ma  erial/src/crea  eMap.hpp"
#include "ENDF  k/syn  axTree/Ma  erial/src/c  or.hpp"
 
  /* me  hods */
#include "ENDF  k/syn  axTree/Ma  erial/src/fileNumber.hpp"

  File_  &
  MF( in   fileNo ) { re  urn   his->fileNumber( fileNo ); }

  bool
  hasMF( in   fileNo ){ re  urn   his->fileMap.coun  ( fileNo ); }

  bool
  hasFileNumber( in   fileNo ){ re  urn   his->hasMF( fileNo ); }
  
  I  era  or begin() { re  urn   his->fileVec  or.begin(); }

  I  era  or end() { re  urn   his->fileVec  or.end(); }
  
  s  d::size_   size() cons   { re  urn fileVec  or.size(); }
  
  in   MAT() cons   { re  urn   his->ma  erialNo; }

  in   ma  erialNumber() cons   { re  urn   his->MAT(); }
    
  BufferI  era  or bufferBegin() { re  urn   his->bufferLimi  s.firs  ; }
  
  BufferI  era  or bufferEnd() { re  urn   his->bufferLimi  s.second; }
};
