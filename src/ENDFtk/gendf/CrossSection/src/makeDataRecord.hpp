static DataRecord makeDataRecord(
      double temperature, unsigned int group,
      const std::vector< double >& fluxes,
      const std::vector< double >& cross_sections ) {

  std::vector< double > list;
  list.insert( list.end(), fluxes.begin(), fluxes.end() );
  list.insert( list.end(), cross_sections.begin(), cross_sections.end() );

  return { temperature, 2, 1, group, std::move( list ) };
}
