/**
 *  @brief Insert the material in the tape
 *
 *  This function inserts the material in the ENDF tape tree. If one or more
 *  materials are already present, the new material is inserted after the
 *  materials that are already there.
 *
 *  @param[in]   material   the material to be inserted
 */
void insert( Material&& material ) {

  this->materials_.emplace( material.MAT(), std::move( material ) );
}

/**
 *  @brief Insert the material in the tape
 *
 *  This function inserts the material in the ENDF tape tree. If one or more
 *  materials are already present, the new material is inserted after the
 *  materials that are already there.
 *
 *  @param[in]   material   the material to be inserted
 */
void insert( const njoy::ENDFtk::Material& material ) {

  this->insert( toMaterial( material ) );
}
