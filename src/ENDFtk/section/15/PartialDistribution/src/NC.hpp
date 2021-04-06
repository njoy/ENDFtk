/**
 *  @brief Return the number of lines in this MF15 component
 */
long NC() const { return this->probability_.NC() + this->distribution_.NC(); };
