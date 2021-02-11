/**
 *  @brief Return the number of lines in this MF2/MT151 component
 */
long NC() const {

  long NC = 0;
  for ( const auto& channel : this->backgroundRMatrices() ) {

    if ( channel ) {

      NC += std::visit( [] ( const auto& variant )
                           { return variant.NC(); },
                        channel.value() );
    }
  }
  return NC;
}
