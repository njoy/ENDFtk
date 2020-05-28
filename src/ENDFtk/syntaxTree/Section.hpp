template< typename BufferIterator >
class SectionBase {
public:
  /* fields */
  int sectionNo;
  int fileNo;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
#include "ENDFtk/syntaxTree/Section/src/ctor.hpp"
#include "ENDFtk/syntaxTree/Section/src/findEnd.hpp"

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


template< typename BufferIterator, typename Tag = ENDFTag >
class Section : public SectionBase< BufferIterator > {

public:

  /* ctor */
  using SectionBase< BufferIterator >::SectionBase;

  /* methods */
  #include "ENDFtk/syntaxTree/Section/src/parse.hpp"  

};


template< typename BufferIterator >
class Section< BufferIterator, GENDFTag > : public SectionBase< BufferIterator > {
public:

  /* ctor */
  using SectionBase< BufferIterator >::SectionBase;

  /* methods */
  #include "ENDFtk/syntaxTree/Section/src/parse-gendf.hpp"

};


/* Convenience alias */
template< typename BufferIterator >
using GendfSection = Section< BufferIterator, GENDFTag >;

