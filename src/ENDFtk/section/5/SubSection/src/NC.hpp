/** 
 *  @brief Return the number of lines in this MF5 component
 */
long NC() const {
  return this->probability_.NC() + 
         std::visit( [] ( const auto& entry )
                        { return entry.NC(); },
                     this->distribution_ );
};
