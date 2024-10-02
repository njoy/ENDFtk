void generateArrays() {

  this->interpolants_.clear();
  this->boundaries_.clear();
  this->energies_.clear();
  this->distributions_.clear();

  // interpolants
  this->interpolants_.insert( this->interpolants_.end(),
                              this->legendre().INT().begin(), this->legendre().INT().end() );
  this->interpolants_.insert( this->interpolants_.end(),
                              this->tabulated().INT().begin(), this->tabulated().INT().end() );

  // boundaries
  auto offset = this->legendre().NBT().back();
  this->boundaries_.insert( this->boundaries_.end(),
                            this->legendre().NBT().begin(), this->legendre().NBT().end() );
  std::transform( this->tabulated().NBT().begin(), this->tabulated().NBT().end(),
                  std::back_inserter( this->boundaries_ ),
                  [offset] ( auto&& value ) { return offset + value; } );

  // energies
  this->energies_.insert( this->energies_.end(),
                          this->legendre().incidentEnergies().begin(),
                          this->legendre().incidentEnergies().end() );
  this->energies_.insert( this->energies_.end(),
                          this->tabulated().incidentEnergies().begin(),
                          this->tabulated().incidentEnergies().end() );

  // distributions
  std::transform( this->legendre().angularDistributions().begin(),
                  this->legendre().angularDistributions().end(),
                  std::back_inserter( this->distributions_ ),
                  [] ( auto&& element ) -> Variant { return std::cref( element ); } );
  std::transform( this->tabulated().angularDistributions().begin(),
                  this->tabulated().angularDistributions().end(),
                  std::back_inserter( this->distributions_ ),
                  [] ( auto&& element ) -> Variant { return std::cref( element ); } );
}
