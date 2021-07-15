/**
 *  @brief Insert or replace the material in the tape
 *
 *  This function inserts the material in the ENDF tape tree. If one or more
 *  materials are already present, the old materials are removed before inserting
 *  the new material.
 *
 *  @param[in]   material   the material to be inserted
 */
void replace( Material&& material ) {

  this->remove( material.MAT() );
  this->materials_.emplace( material.MAT(), std::move( material ) );
}

/**
 *  @brief Insert or replace the material in the tape
 *
 *  This function inserts the material in the ENDF tape tree. If one or more
 *  materials are already present, the old materials are removed before inserting
 *  the new material.
 *
 *  @param[in]   material   the material to be inserted
 */
void replace( const njoy::ENDFtk::Material& material ) {

  this->replace( toMaterial( material ) );
}
