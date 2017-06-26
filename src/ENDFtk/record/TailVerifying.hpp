template< int position, typename tail >
class TailVerification : public tail { 
public:
  TailVerification( int MAT, int MF, int MT ) : tail( MAT, MF, MT ){}
  
  /* note: universal references (not rvalue references) for perfect forwarding */
  template< typename... Args >
  TailVerification( int expectedValue, Args&&... args ) : 
    tail( std::forward< Args >( args )... ) {
    if( this->fields[ position ] != expectedValue ){ 
      Log::error( "The record {} number ({}) is inconsistent with expectation.",
                  helper::name< position >, helper::symbol< position > );
      Log::info( "The read {} number is: {}", 
                 helper::name< position >, this->fields[ position ] );
      Log::info( "The expected {} number is: {}", 
                 helper::name< position >, expectedValue ); 
      Log::info( "Error encountered while verifying record tail values" ); 

      throw (position + 6); 
    }                                                                      
  }
};

/* Convenience typedefs of component verifiers */
template < typename tail >
using MAT = TailVerification< 0, tail >;

template < typename tail >
using MF = TailVerification< 1, tail >;

template < typename tail >
using MT = TailVerification< 2, tail >;

/* Convenience class providing a type definition corresponding to the 
 * composition of zero or more component verifiers 
 */
template< template< typename > class... Ts >
struct TailVerifier;

template<>
struct TailVerifier<>{
  using type = Tail;
};

template< template< typename > class T1, 
          template< typename > class... Ts >
struct TailVerifier< T1, Ts... >{
  using type = T1< typename TailVerifier< Ts... >::type >;
};

/* An alias declaring which field or fields of a tail ought to be verified */
template< template< typename > class... Ts >
using TailVerifying = typename TailVerifier< Ts... >::type;
