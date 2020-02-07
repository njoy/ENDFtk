template< typename Buffer>
class File {
public:
  /* convenience typedefs */
  using BufferIterator = ranges::iterator_t< Buffer >;
  using Section_t = Section< Buffer>;
  using iterator = typename std::vector< Section_t >::iterator;
  using const_iterator = 
    typename std::vector< Section_t >::const_iterator;

protected:
  /* fields */
  int fileNo;
  std::map< int, Section_t > sections_;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* ctor */
#include "ENDFtk/syntaxTree/File/src/createMap.hpp"

public:
#include "ENDFtk/syntaxTree/File/src/ctor.hpp"
#include "ENDFtk/syntaxTree/File/src/parse.hpp"

  /* methods */
#include "ENDFtk/syntaxTree/File/src/sectionNumber.hpp"

  const Section_t&
  MT( int sectionNo ) const { return this->sectionNumber( sectionNo ); }

  Section_t&
  MT( int sectionNo ){ return this->sectionNumber( sectionNo ); }

  bool
  hasMT( int sectionNo ) const { return this->sections_.count( sectionNo ); }
  
  bool
  hasSectionNumber( int sectionNo ) const {  return this->hasMT( sectionNo ); }
  
  auto begin(){ return ( this->sections_ | ranges::view::values ).begin(); }
  auto end(){ return ( this->sections_ | ranges::view::values ).end(); }

  auto begin() const { 
    return ( this->sections_ | ranges::view::values ).begin();
  }
  auto end() const { return ( this->sections_ | ranges::view::values ).end(); }
 
  std::size_t size() const { return this->sections_.size(); }

  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }
  
  int MF() const { return this->fileNo; }

  int fileNumber() const { return this->MF(); }
};
