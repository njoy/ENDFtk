namespace ENDFtk{
namespace implementation{

template< typename BufferIterator >
class MaterialSkeleton {
public:
  /* convenience typedefs */
  using FileSkeleton_t = FileSkeleton< BufferIterator >;
  using Iterator = typename std::vector< FileSkeleton_t >::iterator;
  
  /* fields */
  int materialNo;         
  std::vector< FileSkeleton_t > fileVector;
  std::unordered_map< int, FileSkeleton_t& > fileMap;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* ctor */
#include "ENDFtk/implementation/MaterialSkeleton/src/createVector.hpp"
#include "ENDFtk/implementation/MaterialSkeleton/src/createMap.hpp"
#include "ENDFtk/implementation/MaterialSkeleton/src/ctor.hpp"
 
  /* methods */
#include "ENDFtk/implementation/MaterialSkeleton/src/fileNumber.hpp"

  FileSkeleton_t&
  MF( int fileNo ) { return this->fileNumber( fileNo ); }

  bool
  hasMF( int fileNo ){ return this->fileMap.count( fileNo ); }

  bool
  hasFileNumber( int fileNo ){ return this->hasMF( fileNo ); }
  
  Iterator begin() { return this->fileVector.begin(); }

  Iterator end() { return this->fileVector.end(); }
  
  std::size_t size() const { return fileVector.size(); }
  
  int MAT() const { return this->materialNo; }

  int materialNumber() const { return this->MAT(); }
    
  BufferIterator bufferBegin() { return this->bufferLimits.first; }
  
  BufferIterator bufferEnd() { return this->bufferLimits.second; }

};

}
}
