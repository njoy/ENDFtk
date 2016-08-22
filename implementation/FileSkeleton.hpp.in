namespace ENDFtk{
namespace implementation{

template< typename BufferIterator >
class FileSkeleton {
public:
  /* convenience typedefs */
  using SectionSkeleton_t = SectionSkeleton< BufferIterator >;
  using Iterator = typename std::vector< SectionSkeleton_t >::iterator;
  
  /* fields */
  int fileNo;
  std::vector< SectionSkeleton_t > sectionVector;
  std::unordered_map< int, SectionSkeleton_t& > sectionMap;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* ctor */
#include "ENDFtk/implementation/FileSkeleton/src/createVector.hpp"
#include "ENDFtk/implementation/FileSkeleton/src/createMap.hpp"
#include "ENDFtk/implementation/FileSkeleton/src/ctor.hpp"

  /* methods */
#include "ENDFtk/implementation/FileSkeleton/src/sectionNumber.hpp"

  SectionSkeleton_t&
  MT( int sectionNo ){ return this->sectionNumber( sectionNo ); }

  bool
  hasMT( int sectionNo ){ return this->sectionMap.count( sectionNo ); }
  
  bool
  hasSectionNumber( int sectionNo ){  return this->hasMT( sectionNo ); }
  
  Iterator begin() { return this->sectionVector.begin(); }

  Iterator end() { return this->sectionVector.end(); }
 
  std::size_t size() const { return this->sectionVector.size(); }

  BufferIterator bufferBegin() { return this->bufferLimits.first; }

  BufferIterator bufferEnd() { return this->bufferLimits.second; }
  
  int MF() const { return this->fileNo; }

  int fileNumber() const { return this->MF(); }

};

}
}
