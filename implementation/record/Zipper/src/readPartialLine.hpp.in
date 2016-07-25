template< typename Zip, typename Tuple,
          typename Iterator, std::size_t... indices >
static void
readPartialLine
( uint64_t nEntries, Tuple& iteratorTuple, Iterator& it, const Iterator& end,
  long& lineNumber, int MAT, int MF, int MT,
  std::index_sequence< indices... > ){

//auto increment = []( uint64_t offset, auto& iterator ){ iterator+= offset; };
  
  for ( uint64_t offset = 0; offset < nEntries; ++offset ){
    Zip::TupleFormat::read
      ( it, end, std::get< indices >( iteratorTuple )[offset]... );
  }
  
  auto remainingEntries = Zip::tuplesPerRecord - nEntries;    
  std::tuple< typename Zip:: template Type< indices >... > leftovers;

  while ( remainingEntries-- ){
    Zip::TupleFormat::read( it, end, std::get< indices >( leftovers )... );
    if ( leftovers != Zip::defaultTuple() ){
      LOG(ERROR) << "Encountered non-default value where none was expected";
      throw std::exception();
    }
  }
  
  using Gap = disco::Record
              < disco::ColumnPosition< Zip::nPad >, disco::RetainCarriage >;

  Gap::read( it, end );

  verifyTail( it, end, lineNumber, MAT, MF, MT );
}

