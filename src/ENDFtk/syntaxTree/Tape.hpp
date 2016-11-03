template< typename BufferIterator >
class Tape {
public:
  /* convenience typedefs */
  using Material_t = Material< BufferIterator >;
  using Iterator = typename std::vector< Material_t >::iterator;
  using Multimap = std::unordered_multimap< int, Material_t& >;
  
  /* nested classes */
#include "ENDFtk/syntaxTree/Tape/src/MatchIterator.hpp"
#include "ENDFtk/syntaxTree/Tape/src/Range.hpp"
  
  /* fields */
  std::pair< BufferIterator, BufferIterator > bufferLimits;
  TapeIdentification tpid;
  std::vector< Material_t > materialVector;
  std::unordered_multimap< int, Material_t& > materialMap;

  /* ctor */
#include "ENDFtk/syntaxTree/Tape/src/createVector.hpp"
#include "ENDFtk/syntaxTree/Tape/src/createMap.hpp"
#include "ENDFtk/syntaxTree/Tape/src/ctor.hpp"

  /* methods */
#include "ENDFtk/syntaxTree/Tape/src/materialNumber.hpp"

  Range
  MAT( int materialNo ){ return this->materialNumber( materialNo ); }

  bool
  hasMAT( int materialNo ){ return this->materialMap.count( materialNo ); }

  bool
  hasMaterialNumber( int materialNo ){ return this->hasMAT( materialNo ); }
  
  Iterator begin(){ return materialVector.begin(); }
  
  Iterator end(){ return materialVector.end(); }
  
  std::size_t size() const { return materialVector.size(); }

  BufferIterator bufferBegin() { return this->bufferLimits.first; }

  BufferIterator bufferEnd() { return this->bufferLimits.second ; }

  const TapeIdentification& TPID() const { return this->tpid; }
};
