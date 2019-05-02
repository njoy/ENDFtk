template< typename Iterator >
static std::optional< ContinuousSpectrum >
readContinuous( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT,
                int lcon ) {
  if ( lcon == 0 ) return std::nullopt;
  return std::make_optional( ContinuousSpectrum( begin, end, lineNumber,
                                                 MAT, MF, MT ) );
}
