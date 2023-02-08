private:

/**
 *  @brief Private intermediate constructor
 */
CovarianceMatrix( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->NPAR() );
}

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CovarianceMatrix() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] values     the values of the upper diagonal covaraince matrix
 */
CovarianceMatrix( unsigned int mpar, std::vector< double >&& values ) :
  // no try ... catch: exceptions will be handled in the derived class
  CovarianceMatrix( ListRecord(
                      0., 0., mpar, 0,
                      [] ( unsigned int n ) {

                        return ( -1 + std::sqrt( 1 + 8 * n ) ) / 2;
                      }( values.size() ),
                      std::move( values ) ) ) {}

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
CovarianceMatrix(
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  CovarianceMatrix( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
