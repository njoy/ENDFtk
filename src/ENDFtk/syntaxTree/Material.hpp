template< typename BufferIterator >
class Material {
public:
  /* convenience typedefs */
  using File_t = File< BufferIterator >;
  using iterator = typename std::vector< File_t >::iterator;
  using const_iterator = typename std::vector< File_t >::iterator;

protected:
  /* fields */
  int materialNo;         
  std::vector< File_t > fileVector;
  tsl::hopscotch_map< int, const File_t* > fileMap;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* ctor */
#include "ENDFtk/syntaxTree/Material/src/createVector.hpp"
#include "ENDFtk/syntaxTree/Material/src/createMap.hpp"

public:
#include "ENDFtk/syntaxTree/Material/src/ctor.hpp"
 
  /* methods */
#include "ENDFtk/syntaxTree/Material/src/fileNumber.hpp"

  const File_t&
  MF( int fileNo ) const { return this->fileNumber( fileNo ); }
  
  File_t&
  MF( int fileNo ) { return this->fileNumber( fileNo ); }

  bool
  hasMF( int fileNo ) const { return this->fileMap.count( fileNo ); }

  bool
  hasFileNumber( int fileNo ) const { return this->hasMF( fileNo ); }
  
  iterator begin() { return this->fileVector.begin(); }
  iterator end() { return this->fileVector.end(); }

  const_iterator begin() const {
    return const_cast< Material& >( *this ).begin();
  }
  
  const_iterator end() const {
    return const_cast< Material& >( *this ).end();
  }
  
  std::size_t size() const { return fileVector.size(); }
  
  int MAT() const { return this->materialNo; }

  int materialNumber() const { return this->MAT(); }

  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }
};
