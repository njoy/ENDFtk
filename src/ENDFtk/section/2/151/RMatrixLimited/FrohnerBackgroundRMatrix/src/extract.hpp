static std::array< double, 5 >
extract( ListRecord&& record ) {

  std::array< double, 5 > values;

  if ( record.NPL() != 3 ) {

    Log::info( "Expected NPL = 3 for the Frohner parametrisation" );
    Log::info( "Found NPL value: {}", record.NPL() );
    throw std::exception();
  }

  auto list = record.list();
  values[0] = record.C1();
  values[1] = record.C2();
  std::copy_n( ranges::begin( list ), 3, values.begin() + 2 );

  return values;
}
