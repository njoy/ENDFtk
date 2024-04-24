/**
 *  @brief Print the directory record
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 *  @param[in] MT            the MT number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  using namespace njoy::tools;
  using Format = disco::Record< disco::Integer< 33 >, disco::Integer< 11 >,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 4 >, disco::Integer< 2 >,
                                disco::Integer< 3 >, disco::Column<5> >;
  Format::write( it, this->MF(), this->MT(),
                 this->NC(), this->MOD(), MAT, MF, MT );
}
