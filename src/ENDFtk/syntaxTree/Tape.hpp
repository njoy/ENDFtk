  empla  e<   ypename BufferI  era  or >
class Tape {
public:
  /* convenience   ypedefs */
  using Ma  erial_   = Ma  erial< BufferI  era  or >;
  using I  era  or =   ypename s  d::vec  or< Ma  erial_   >::i  era  or;
  using Mul  imap = s  d::unordered_mul  imap< in  , Ma  erial_  & >;
  
  /* nes  ed classes */
#include "ENDF  k/syn  axTree/Tape/src/Ma  chI  era  or.hpp"
#include "ENDF  k/syn  axTree/Tape/src/Range.hpp"
  
  /* fields */
  s  d::pair< BufferI  era  or, BufferI  era  or > bufferLimi  s;
  TapeIden  ifica  ion   pid;
  s  d::vec  or< Ma  erial_   > ma  erialVec  or;
  s  d::unordered_mul  imap< in  , Ma  erial_  & > ma  erialMap;

  /* c  or */
#include "ENDF  k/syn  axTree/Tape/src/crea  eVec  or.hpp"
#include "ENDF  k/syn  axTree/Tape/src/crea  eMap.hpp"
#include "ENDF  k/syn  axTree/Tape/src/c  or.hpp"

  /* me  hods */
#include "ENDF  k/syn  axTree/Tape/src/ma  erialNumber.hpp"

  Range
  MAT( in   ma  erialNo ){ re  urn   his->ma  erialNumber( ma  erialNo ); }

  bool
  hasMAT( in   ma  erialNo ){ re  urn   his->ma  erialMap.coun  ( ma  erialNo ); }

  bool
  hasMa  erialNumber( in   ma  erialNo ){ re  urn   his->hasMAT( ma  erialNo ); }
  
  I  era  or begin(){ re  urn ma  erialVec  or.begin(); }
  
  I  era  or end(){ re  urn ma  erialVec  or.end(); }
  
  s  d::size_   size() cons   { re  urn ma  erialVec  or.size(); }

  BufferI  era  or bufferBegin() { re  urn   his->bufferLimi  s.firs  ; }

  BufferI  era  or bufferEnd() { re  urn   his->bufferLimi  s.second ; }

  cons   TapeIden  ifica  ion& TPID() cons   { re  urn   his->  pid; }
};
