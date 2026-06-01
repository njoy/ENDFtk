template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

    int MT = this->MT();
    ControlRecord( this->ZA(), this->AWR(), 0, this->IRELCO(),
                   this->L() , this->L1() ).print( it, MAT, MF, MT ); 

    ControlRecord( 0.0, 0.0, MT, this->L(), this->L1(),
                   this->NGN() ).print(it, MAT, MF, MT);

    auto records = makeRecords( this->ang_covr_ );

    for ( const auto& record : records ) {
        record.print( it, MAT, MF, MT );
    } // record

    SEND( MAT, MF ).print( it );
}