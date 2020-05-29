template< typename BufferIterator >
class SectionBase {
protected:
  /* fields */
  int sectionNo;
  int fileNo;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
  #include "ENDFtk/syntaxTree/Section/src/findEnd.hpp"

public:
  /* methods */
  #include "ENDFtk/syntaxTree/Section/src/ctor.hpp"

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
class Section : protected SectionBase< BufferIterator > {

public:

  /* ctor */
  using Base = SectionBase< BufferIterator >;
  using Base::SectionBase;

  /* methods */

  // this file implements the parse() function
  #include "ENDFtk/syntaxTree/Section/src/parse-endf.hpp"

  using Base::MT;
  using Base::sectionNumber;
  using Base::MF;
  using Base::fileNumber;
  using Base::buffer;

};


template< typename BufferIterator >
class Section< BufferIterator, GENDFTag > 
  : protected SectionBase< BufferIterator > {
public:

  /* ctor */
  using Base = SectionBase< BufferIterator >;
  using Base::SectionBase;

  /* methods */

  // TODO: Add parse function once required classes are implemented.
  // this file implements the parse() function
  // #include "ENDFtk/syntaxTree/Section/src/parse-gendf.hpp"

  using Base::MT;
  using Base::sectionNumber;
  using Base::MF;
  using Base::fileNumber;
  using Base::buffer;

};


/* Convenience alias */
template< typename BufferIterator >
using GendfSection = Section< BufferIterator, GENDFTag >;

