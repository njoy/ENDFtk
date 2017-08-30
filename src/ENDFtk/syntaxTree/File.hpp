template< typename BufferIterator >
class File {
public:
  /* convenience typedefs */
  using Section_t = Section< BufferIterator >;
  using iterator = typename std::vector< Section_t >::iterator;
  using const_iterator = typename std::vector< Section_t >::const_iterator;

protected:
  /* fields */
  int fileNo;
  std::vector< Section_t > sectionVector;
  tsl::hopscotch_map< int, const Section_t* > sectionMap;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* ctor */
#include "ENDFtk/syntaxTree/File/src/createVector.hpp"
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
  hasMT( int sectionNo ) const { return this->sectionMap.count( sectionNo ); }
  
  bool
  hasSectionNumber( int sectionNo ) const {  return this->hasMT( sectionNo ); }
  
  iterator begin() { return this->sectionVector.begin(); }
  iterator end() { return this->sectionVector.end(); }

  const_iterator begin() const { return const_cast< File& >( *this ).begin(); }
  const_iterator end() const { return const_cast< File& >( *this ).end(); }
 
  std::size_t size() const { return this->sectionVector.size(); }

  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }
  
  int MF() const { return this->fileNo; }

  int fileNumber() const { return this->MF(); }
};
