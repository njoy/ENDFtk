template< typename BufferIterator >
class Material {
public:
  /* convenience typedefs */
  using File_t = File< BufferIterator >;
  using Iterator = typename std::vector< File_t >::iterator;
  
  /* fields */
  int materialNo;         
  std::vector< File_t > fileVector;
  std::unordered_map< int, File_t& > fileMap;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* ctor */
#include "ENDFtk/syntaxTree/Material/src/createVector.hpp"
#include "ENDFtk/syntaxTree/Material/src/createMap.hpp"
#include "ENDFtk/syntaxTree/Material/src/ctor.hpp"
 
  /* methods */
#include "ENDFtk/syntaxTree/Material/src/fileNumber.hpp"

  File_t&
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
