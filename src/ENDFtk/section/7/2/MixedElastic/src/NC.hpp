/**
 *  @brief Return the number of lines in this MF7/MT2 component
 */
long NC() const {

  return this->coherent_.NC() + this->incoherent_.NC();
};
