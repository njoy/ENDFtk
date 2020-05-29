/* Template specialization for GendfMaterial */
template< typename BufferIterator >
class Material< BufferIterator, GENDFTag > {

public:
  /* convenience typedefs */
  using Section_t = GendfSection< BufferIterator >;
  using MFMT = std::pair< int, int >;

protected:
  /* fields */
  int materialNo;
  std::map< MFMT, Section_t > sections_;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* methods */
  #include "ENDFtk/syntaxTree/GendfMaterial/src/createMap.hpp"

public:
  /* constructor */
  #include "ENDFtk/syntaxTree/GendfMaterial/src/ctor.hpp"

  /* methods */

  #include "ENDFtk/syntaxTree/GendfMaterial/src/section.hpp"

  bool hasSection( int MF, int MT ) const {
    return sections_.count( MFMT(MF, MT) );
  }

  /*
   * @brief Define begin, end to make object iterable.
   */
  auto begin() { return (sections_ | ranges::view::values).begin(); }
  auto end() { return (sections_ | ranges::view::values).end(); }
  
  auto begin() const { return (sections_ | ranges::view::values).begin(); }
  auto end() const { return (sections_ | ranges::view::values).end(); }


  /*
   * @brief Return the number of Sections contained in the Material.
   */
  std::size_t size() const { return sections_.size(); }

  /*
   * @brief Return the MAT number.
   */
  int MAT() const { return materialNo; }
  int materialNumber() const { return MAT(); }

  /*
   * @brief Create a reference to the buffer.
   * TODO: Update make_iterator_range to newer syntax
   */
  auto buffer() const {
    return ranges::make_iterator_range( bufferLimits.first,
                                        bufferLimits.second );
  }

};


/* convenience alias */
template< typename BufferIterator >
using GendfMaterial = Material< BufferIterator, GENDFTag >;
