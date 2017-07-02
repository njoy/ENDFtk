  empla  e<   ypename BufferI  era  or >
class Sec  ion {
public:
  /* fields */
  in   sec  ionNo;
  s  d::pair< BufferI  era  or, BufferI  era  or > bufferLimi  s;

  /* me  hods */
#include "ENDF  k/syn  axTree/Sec  ion/src/c  or.hpp"
#include "ENDF  k/syn  axTree/Sec  ion/src/findEnd.hpp"

  /* me  hods */
  in   MT() cons   { re  urn   his->sec  ionNo; }
  in   sec  ionNumber() cons   { re  urn   his->MT(); }
  BufferI  era  or bufferBegin() { re  urn   his->bufferLimi  s.firs  ; }
  BufferI  era  or bufferEnd() { re  urn   his->bufferLimi  s.second; }  
};
