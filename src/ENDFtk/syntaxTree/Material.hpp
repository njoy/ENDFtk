template< typename Buffer>
class Material {
public:
  /* convenience typedefs */
  using BufferIterator = ranges::iterator_t< Buffer >;
  using File_t = File< Buffer >;
  using iterator = typename std::vector< File_t >::iterator;
  using const_iterator = typename std::vector< File_t >::iterator;

protected:
  /* fields */
  int materialNo;         
  std::map< int, File_t > files_;
  std::pair< BufferIterator, BufferIterator > bufferLimits;

  /* ctor */
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
  hasMF( int fileNo ) const { return this->files_.count( fileNo ); }

  bool
  hasFileNumber( int fileNo ) const { return this->hasMF( fileNo ); }
  
  auto begin(){ return ( this->files_ | ranges::view::values ).begin(); }
  auto end(){ return ( this->files_ | ranges::view::values ).end(); }

  auto begin() const { return ( this->files_ | ranges::view::values ).begin(); }
  auto end() const { return ( this->files_ | ranges::view::values ).end(); }

  std::size_t size() const { return files_.size(); }
  
  int MAT() const { return this->materialNo; }

  int materialNumber() const { return this->MAT(); }

  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }
};
