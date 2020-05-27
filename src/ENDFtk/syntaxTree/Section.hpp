template< typename BufferIterator, typename Tag = ENDFTag >
class Section {
public:
  /* fields */
  int sectionNo;
  int fileNo;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
#include "ENDFtk/syntaxTree/Section/src/ctor.hpp"
#include "ENDFtk/syntaxTree/Section/src/findEnd.hpp"
#include "ENDFtk/syntaxTree/Section/src/parse.hpp"  

  /* methods */
  int MT() const { return this->sectionNo; }
  int sectionNumber() const { return this->MT(); }
  int MF() const { return this->fileNo; }
  int fileNumber() const { return this->MF(); }
  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }
};

/* Convenience alias */
template< typename BufferIterator >
using GendfSection = Section< BufferIterator, GENDFTag >

/* Template specialization */
#include "ENDFtk/syntaxTree/Section/src/parse-gendf.hpp"
