template< typename BufferIterator >
class File {
public:
  /* convenience typedefs */
  using Section_t = Section< BufferIterator >;
  using Iterator = typename std::vector< Section_t >::iterator;

  /* fields */
  int fileNo;
  std::vector< Section_t > sectionVector;
  std::unordered_map< int, Section_t& > sectionMap;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

    /* ctor */
#include "ENDFtk/syntaxTree/File/src/createVector.hpp"
#include "ENDFtk/syntaxTree/File/src/createMap.hpp"
#include "ENDFtk/syntaxTree/File/src/ctor.hpp"

  /* methods */
#include "ENDFtk/syntaxTree/File/src/sectionNumber.hpp"

  Section_t&
  MT( int sectionNo ){ return this->sectionNumber( sectionNo ); }

  bool
  hasMT( int sectionNo ){ return this->sectionMap.count( sectionNo ); }
  
  bool
  hasSectionNumber( int sectionNo ){  return this->hasMT( sectionNo ); }
  
  Iterator begin() { return this->sectionVector.begin(); }

  Iterator end() { return this->sectionVector.end(); }
 
  std::size_t size() const { return this->sectionVector.size(); }

  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }
  
  int MF() const { return this->fileNo; }

  int fileNumber() const { return this->MF(); }
};
