template< typename Buffer >
class Section {
public:
  using BufferIterator = ranges::iterator_t< Buffer >;
  /* fields */
  int sectionNo;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
#include "ENDFtk/syntaxTree/Section/src/ctor.hpp"
#include "ENDFtk/syntaxTree/Section/src/findEnd.hpp"
#include "ENDFtk/syntaxTree/Section/src/parse.hpp"  

  /* methods */
  int MT() const { return this->sectionNo; }
  int sectionNumber() const { return this->MT(); }
  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }
};
