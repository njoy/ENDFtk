static std::vector< double >
generateList( std::vector< double >&& rowEnergies,
              std::vector< double >&& columnEnergies,
              std::vector< double >&& values ) {

  std::vector< double > list;

  int NER = rowEnergies.size();
  int NEC = columnEnergies.size();
  int NV = values.size();

  if ( (NER-1)*(NEC-1) != NV ) {
    Log::error( "Inconsistent number of values in rectangular matrix" );
    Log::info( "NER: {}", NER );
    Log::info( "NEC: {}", NEC );
    Log::info( "Expected: {}", (NER-1)*(NEC-1) );
    Log::info( "Observed: {}", NV );
    throw std::exception();
  }

  list.insert( list.end(), rowEnergies.begin(), rowEnergies.end() );
  list.insert( list.end(), columnEnergies.begin(), columnEnergies.end() );
  list.insert( list.end(), values.begin(), values.end() );
  return list;
}
