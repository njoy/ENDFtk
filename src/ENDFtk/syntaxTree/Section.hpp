template< typename BufferIterator >
class Section {
public:
  /* fields */
  int sectionNo;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
#include "ENDFtk/syntaxTree/Section/src/ctor.hpp"
#include "ENDFtk/syntaxTree/Section/src/findEnd.hpp"

  /* methods */
  int MT() const { return this->sectionNo; }
  int sectionNumber() const { return this->MT(); }
  BufferIterator bufferBegin() { return this->bufferLimits.first; }
  BufferIterator bufferEnd() { return this->bufferLimits.second; }  
};
