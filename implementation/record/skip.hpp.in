namespace ENDFtk {
namespace implementation {
namespace record {

template< typename Iterator >
Tail
skip( Iterator& begin, const Iterator& end, long& lineNumber ){
  try{
    Base< Character< 66 > >( begin, end );
    return Tail( begin, end, lineNumber );
  } catch( std::exception& e ){
    LOG(ERROR) << "Error while skipping a record.";
    throw e;
  }
}

}
}
}

