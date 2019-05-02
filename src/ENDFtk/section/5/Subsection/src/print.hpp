/** 
 *  @brief Print this MF5 component
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

  this->probability_.print( it, MAT, MF, MT );
  std::visit( [&] ( const auto& entry )
                  { return entry.print( it, MAT, MF, MT ); },
              this->distribution_ );
} 

