protected:
Type( Map&& map ) : sectionMap( std::move(map) ){}

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

template< int sectionNo, typename... Args >
Type( section::Type< 7, sectionNo >&& section_, Args&&... args ) :
  Type( fill( std::move( section_ ), std::forward< Args >( args )... ) ) {}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber )
  try: Type( this->read( sections(),
                         structureDivision, begin, end, lineNumber,
                         structureDivision.tail.MAT() ) ) {

    this->verifyEND( structureDivision, lineNumber );
  }
  catch ( std::exception& e ) {

    Log::info("Error while reading File 7");
    throw e;
  }
