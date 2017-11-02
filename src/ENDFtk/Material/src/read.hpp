template< typename BufferIterator, typename Int >
static auto read( hana::true_,
		  Int fileNo,
		  StructureDivision& structureDivision,
		  BufferIterator& begin,
		  const BufferIterator& end,
		  long& lineNumber,
		  int MAT ){
  if ( structureDivision.tail.MF != fileNo ){
    Log::error("Required file missing from Material stream");
    Log::info("Line number: {}", lineNumber - 1 ); 
    Log::info("File number (MF): {}", fileNo.value );
    throw std::runtime_error( "file::Type<1>::read" );
  }
  
  auto p = hana::make_pair( fileNo,
			    file::Type< fileNo.value >
			    ( structureDivision, begin, end, lineNumber ) );

  try{
    structureDivision = StructureDivision( begin, end, lineNumber );
  } catch( std::exception& e ) {
    Log::info
      ( "Error while reading structure division following file number (MF) {}",
	fileNo.value );
    throw e;
  }

  return p;
}

template< typename BufferIterator, typename Int >
static auto read( hana::false_,
		  Int fileNo,
		  StructureDivision& structureDivision,
		  BufferIterator& begin,
		  const BufferIterator& end,
		  long& lineNumber,
		  int MAT ){
  auto p = 
    hana::make_pair( fileNo,
		     structureDivision.tail.MF == fileNo.value ?
		     std::make_optional
		     ( file::Type< fileNo.value >
		       ( structureDivision, begin, end, lineNumber ) ) :
		     std::nullopt );
	
  try{
    structureDivision = StructureDivision( begin, end, lineNumber );
  } catch( std::exception& e ) {
    Log::info
      ( "Error while reading structure division following file number (MF) {}",
	fileNo.value );
    throw e;
  }

  return p;
}

template< typename Pair, typename BxoufferIterator >
static auto read( Pair&& p,
		  StructureDivision& structureDivision,
		  BufferIterator& begin,xo
		  const BufferIterator& end,
		  long& lineNumber,
		  int MAT ){
  return read( hana::first(p),
	       hana::second(p),
	       structureDivision, begin, end, lineNumber, MAT );
}

template< typename BufferIterator >
static auto read( StructureDivision& structureDivision,
		  BufferIterator& begin,
		  const BufferIterator& end,
		  long& lineNumber,
		  int MAT ){
  return hana::unpack( files, [&]( auto&&... pairs ){
      return
	hana::make_map
	( read( pairs, structureDivision, begin, end, lineNumber, MAT )... );
    } );
}
