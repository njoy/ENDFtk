private:

/**
 *  @brief Intermediate private constructor
 */
Type( int zaid, double awr, bool lssf, int interpolation,
      ListRecord&& list ) :
  BaseWithoutMT( zaid, awr ), lssf_( lssf ), interpolation_( interpolation ),
  data_( std::move( list ) ) {

    verifySize( this->NREAC(), this->NSIGZ(), this->NUNR(), this->NW() );
  }

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief General constructor
 *
 *  @param[in] zaid            the material ZAID value
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] lssf            the lssf flag
 *  @param[in] interpolation   the interpolation scheme
 *  @param[in] temperature     the temperature
 *  @param[in] dilutions       the dilution values (nsigz values)
 *  @param[in] energies        the energy values (nunr values)
 *  @param[in] total           the total cross section values (nunr values of
 *                             nsigz values)
 *  @param[in] elastic         the elastic cross section values (nunr values of
 *                             nsigz values)
 *  @param[in] fission         the fission cross section values (nunr values of
 *                             nsigz values)
 *  @param[in] capture         the capture cross section values (nunr values of
 *                             nsigz values)
 *  @param[in] cwTotal         the current weighted total cross section values
 *                             (nunr values of nsigz values)
 */
Type( int zaid, double awr, bool lssf, int interpolation, double temperature,
      std::vector< double >&& dilutions, std::vector< double >&& energies,
      std::vector< std::vector< double > >&& total,
      std::vector< std::vector< double > >&& elastic,
      std::vector< std::vector< double > >&& fission,
      std::vector< std::vector< double > >&& capture,
      std::vector< std::vector< double > >&& cwTotal )
  try : Type( zaid, awr, lssf, interpolation,
              ListRecord( temperature, 0., 5, dilutions.size(), energies.size(),
                          generateList( std::move( dilutions ),
                                        std::move( energies ),
                                        std::move( total ),
                                        std::move( elastic ),
                                        std::move( fission ),
                                        std::move( capture ),
                                        std::move( cwTotal ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Trouble while constructing section 152 of File 2" );
    throw e;
  }

/**
 *  @brief Constructor for infinite dilution only
 *
 *  @param[in] zaid            the material ZAID value
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] lssf            the lssf flag
 *  @param[in] interpolation   the interpolation scheme
 *  @param[in] temperature     the temperature
 *  @param[in] energies        the energy values (nunr values)
 *  @param[in] total           the total cross section values (nunr values)
 *  @param[in] elastic         the elastic cross section values (nunr values)
 *  @param[in] fission         the fission cross section values (nunr values)
 *  @param[in] capture         the capture cross section values (nunr values)
 *  @param[in] cwTotal         the current weighted total cross section values
 *                             (nunr values)
 */
Type( int zaid, double awr, bool lssf, int interpolation, double temperature,
      std::vector< double >&& energies, std::vector< double >&& total,
      std::vector< double >&& elastic, std::vector< double >&& fission,
      std::vector< double >&& capture, std::vector< double >&& cwTotal )
  try : Type( zaid, awr, lssf, interpolation,
              ListRecord( temperature, 0., 5, 1, energies.size(),
                          generateList( std::move( energies ),
                                        std::move( total ),
                                        std::move( elastic ),
                                        std::move( fission ),
                                        std::move( capture ),
                                        std::move( cwTotal ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Trouble while constructing section 152 of File 2" );
    throw e;
  }

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try:
    Type( head.ZA(), head.AWR(), head.L1(), head.N2(),
          ListRecord( begin, end, lineNumber, head.MAT(), 2, 152 ) ) {

      readSEND( begin, end, lineNumber, MAT, 2 );
  } catch( std::exception& e ){
    Log::info( "Trouble while reading section 152 of File 2 of Material {}",
               MAT );
    throw e;
  }
