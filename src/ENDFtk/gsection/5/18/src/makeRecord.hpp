static auto
makeRecord( double temp,
            const std::vector< double >& chi ) {

  // int nz is always one for this section
  int ig2lo = 1;
  unsigned int ngroups = chi.size();

  std::vector< double > list( ngroups );
  list = std::move( chi );

  return DataRecord( temp, ngroups, ig2lo, ngroups, std::move ( list ) );
}