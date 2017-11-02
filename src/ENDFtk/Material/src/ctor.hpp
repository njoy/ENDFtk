public:
template< typename Args... >
Material( int MAT, Args&&... args ) :
  fileMap( fill( std::forward< Args >( args )... ) ),
  MAT_( MAT ){}

template< typename BufferIterator >
Material( StructureDivision& structureDivision,
	  BufferIterator& begin,
	  const BufferIterator& end,
	  long& lineNumber,
	  int MAT )
try:
  fileMap( read( structureDivision, begin, end, lineNumber, MAT ) ),
  MAT_( MAT ){
} catch ( std::exception& e ) {
  Log::info("Error while reading Material {}", MAT );
  throw e;
}
