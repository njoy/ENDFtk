template< typename BufferIterator >
class Section {
public:
  /* fields */
  HEAD head;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
#include "ENDFtk/syntaxTree/Section/src/ctor.hpp"
#include "ENDFtk/syntaxTree/Section/src/findEnd.hpp"
#include "ENDFtk/syntaxTree/Section/src/parse.hpp"

  /* methods */
  int MT() const { return this->head.MT(); }
  int sectionNumber() const { return this->head.MT(); }
  BufferIterator bufferBegin() { return this->bufferLimits.first; }
  BufferIterator bufferEnd() { return this->bufferLimits.second; }  
};
