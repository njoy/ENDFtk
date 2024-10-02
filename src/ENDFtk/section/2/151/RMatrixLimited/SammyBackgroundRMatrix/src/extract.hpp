static std::array< double, 7 >
extract( ListRecord&& record ) {

  using namespace njoy::tools;

  std::array< double, 7 > values;

  if ( record.NPL() != 5 ) {

    Log::info( "Expected NPL = 5 for the SAMMY parametrisation" );
    Log::info( "Found NPL value: {}", record.NPL() );
    throw std::exception();
  }

  auto list = record.list();
  values[0] = record.C1();
  values[1] = record.C2();
  std::copy_n( std20::begin( list ), 5, values.begin() + 2 );

  return values;
}
