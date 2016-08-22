namespace ENDFtk{
namespace implementation{

template< typename BufferIterator >
class SectionSkeleton {
public:
  /* fields */
  int sectionNo;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* ctor */
#include "ENDFtk/implementation/SectionSkeleton/src/findEnd.hpp"
#include "ENDFtk/implementation/SectionSkeleton/src/ctor.hpp"

  /* methods */
  int MT() const { return this->sectionNo; }
  int sectionNumber() const { return this->MT(); }
  BufferIterator bufferBegin() { return this->bufferLimits.first; }
  BufferIterator bufferEnd() { return this->bufferLimits.second; }  
};

}
}

