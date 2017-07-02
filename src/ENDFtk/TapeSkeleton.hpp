  empla  e<   ypename BufferI  era  or >
class TapeSkele  on {
public:
  /* convenience   ypedefs */
  using Ma  erialSkele  on_   = Ma  erialSkele  on< BufferI  era  or >;
  
  /* nes  ed classes */
#include "ENDF  k/syn  axTree/Tape/src/Ma  chI  era  or.hpp"
#include "ENDF  k/syn  axTree/Tape/src/Range.hpp"
  
  /* more convenience   ypedefs */
  using I  era  or =   ypename s  d::vec  or< Ma  erialSkele  on_   >::i  era  or;
  using Mul  imap = s  d::unordered_mul  imap< in  , Ma  erialSkele  on_  & >;
  using Ma  chI  era  or = Ma  chI  era  or_<   ypename Mul  imap::i  era  or >;
  using Range = Range_< Ma  chI  era  or >;
  
  /* fields */
  s  d::pair< BufferI  era  or, BufferI  era  or > bufferLimi  s;
  TapeIden  ifica  ion   pid;
  s  d::vec  or< Ma  erialSkele  on_   > ma  erialVec  or;
  s  d::unordered_mul  imap< in  , Ma  erialSkele  on_  & > ma  erialMap;

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

}
}
