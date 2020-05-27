/* Template specialization for GENDF Section */
template< typename BufferIterator >
class Section< BufferIterator, GENDFTag > {

protected:
  /* fields */
  int sectionNo_;
  int fileNo_;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
  #include "ENDFtk/syntaxTree/GendfSection/src/findEnd.hpp"

public:
  /* constructor */
  #include "ENDFtk/syntaxTree/GendfSection/src/ctor.hpp"

  /* methods */

  #include "ENDFtk/syntaxTree/GendfSection/src/parse.hpp"

  /*
   * @brief Getter for sectionNumber (MT)
   */
  int sectionNumber() const { return sectionNo_; }
  int MT() const { return sectionNumber(); }

  /*
   * @brief Getter for fileNumber (MF or MFD)
   */
  int fileNumber() const { return fileNo_; }
  int MF() const { return fileNumber(); }
  int MFD() const { return fileNumber(); }

  /*
   * @brief Create reference to buffer for Section.
   * TODO: update make_iterator_range to newer syntax
   */
  auto buffer() const {
    return ranges::make_iterator_range( bufferLimits.first,
                                        bufferLimits.second );
  }

};


/* convenience alias */
template< typename BufferIterator >
using GendfSection = Section< BufferIterator, GENDFTag >;
