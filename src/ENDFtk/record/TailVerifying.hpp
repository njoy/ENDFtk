#ifndef NJOY_ENDFTK_RECORD_TAILVERIFICATION
#define NJOY_ENDFTK_RECORD_TAILVERIFICATION

// system includes

// other includes
#include "Log.hpp"
#include "disco.hpp"
#include "ENDFtk/record/helper.hpp"
#include "ENDFtk/record/Integer.hpp"
#include "ENDFtk/record/Real.hpp"
#include "ENDFtk/record/Tail.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  template< int position, typename Tail >
  class TailVerification : public Tail {
  public:
    TailVerification( int MAT, int MF, int MT ) : Tail( MAT, MF, MT ){}

    /* note: universal references (not rvalue references) for perfect forwarding */
    template< typename... Args >
    TailVerification( int expectedValue, Args&&... args ) :
      Tail( std::forward< Args >( args )... ) {
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
  template < typename Tail >
  using MAT = TailVerification< 0, Tail >;

  template < typename Tail >
  using MF = TailVerification< 1, Tail >;

  template < typename Tail >
  using MT = TailVerification< 2, Tail >;

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

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
