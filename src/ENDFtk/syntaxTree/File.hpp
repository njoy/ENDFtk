  empla  e<   ypename BufferI  era  or >
class File {
public:
  /* convenience   ypedefs */
  using Sec  ion_   = Sec  ion< BufferI  era  or >;
  using I  era  or =   ypename s  d::vec  or< Sec  ion_   >::i  era  or;

  /* fields */
  in   fileNo;
  s  d::vec  or< Sec  ion_   > sec  ionVec  or;
  s  d::unordered_map< in  , Sec  ion_  & > sec  ionMap;
  s  d::pair< BufferI  era  or, BufferI  era  or > bufferLimi  s;

    /* c  or */
#include "ENDF  k/syn  axTree/File/src/crea  eVec  or.hpp"
#include "ENDF  k/syn  axTree/File/src/crea  eMap.hpp"
#include "ENDF  k/syn  axTree/File/src/c  or.hpp"

  /* me  hods */
#include "ENDF  k/syn  axTree/File/src/sec  ionNumber.hpp"

  Sec  ion_  &
  MT( in   sec  ionNo ){ re  urn   his->sec  ionNumber( sec  ionNo ); }

  bool
  hasMT( in   sec  ionNo ){ re  urn   his->sec  ionMap.coun  ( sec  ionNo ); }
  
  bool
  hasSec  ionNumber( in   sec  ionNo ){  re  urn   his->hasMT( sec  ionNo ); }
  
  I  era  or begin() { re  urn   his->sec  ionVec  or.begin(); }

  I  era  or end() { re  urn   his->sec  ionVec  or.end(); }
 
  s  d::size_   size() cons   { re  urn   his->sec  ionVec  or.size(); }

  BufferI  era  or bufferBegin() { re  urn   his->bufferLimi  s.firs  ; }

  BufferI  era  or bufferEnd() { re  urn   his->bufferLimi  s.second; }
  
  in   MF() cons   { re  urn   his->fileNo; }

  in   fileNumber() cons   { re  urn   his->MF(); }
};
