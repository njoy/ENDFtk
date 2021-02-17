/**
 *  @brief Constructor
 *
 *  @param[in] qm               the mass difference Q value
 *  @param[in] qi               the reaction Q value
 *  @param[in] izap             the za identifier of the product
 *  @param[in] lfs              the excited level number
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] energies         the energy values
 *  @param[in] multiplicities   the multiplicity values
 */
Multiplicity( double qm, double qi, long izap, long lfs,
              std::vector< long >&& boundaries,
              std::vector< long >&& interpolants,
              std::vector< double >&& energies,
              std::vector< double >&& multiplicities )
  try : TabulationRecord( qm, qi, izap, lfs,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( multiplicities ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a radioactive nuclide "
               "production multiplicity" );
    throw;
  }

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 *  @param[in] MF           the expected MF number
 *  @param[in] MT           the expected MT number
 */
template< typename Iterator >
Multiplicity( Iterator& begin, const Iterator& end,
              long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a radioactive nuclide "
               "production multiplicity" );
    throw;
  }
