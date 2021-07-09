void verifyRecords() {

  // test if last record's index matches number of groups
  unsigned int ig = records_.rbegin()->first;
  if ( ig != this->num_groups_ ) {
    Log::error( "Final DataRecord in GENDF section {} has IG {} which "
                "does not match NGN {}.",
                this->MT(), ig, this->NGN() );
    throw;
  }
}
