template < typename Range >
static bool compare( const Range& left, const Range& right ) {

  for ( unsigned int i = 0; i < left.size(); ++i ) {

    if ( left[i] != right[i] ) {

      return false;
    }
  }
  return true;
}

static void
verify( const TabulationRecord& real, const TabulationRecord& imaginary ) {

  if ( ( real.NP() != imaginary.NP() ) || ( real.NR() != imaginary.NR() ) ) {

    Log::error( "Encountered inconsistent size for real and imaginary values" );
    Log::info( "real.NR: {}", real.NR() );
    Log::info( "imaginary.NR: {}", imaginary.NR() );
    Log::info( "real.NP: {}", real.NP() );
    Log::info( "imaginary.NP: {}", imaginary.NP() );
    throw std::exception();
  }

  if ( !compare( real.boundaries(), imaginary.boundaries() ) ) {

    Log::error( "Encountered different interpolation ranges between the real "
                "and imaginary parts" );
  }

  if ( !compare( real.interpolants(), imaginary.interpolants() ) ) {

    Log::error( "Encountered different interpolation schemes between the real "
                "and imaginary parts" );
  }

  if ( !compare( real.x(), imaginary.x() ) ) {

    Log::error( "Encountered different energies between the real and "
                "imaginary parts" );
  }
}
