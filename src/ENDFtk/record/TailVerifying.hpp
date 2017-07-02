  empla  e< in   posi  ion,   ypename   ail >
class TailVerifica  ion : public   ail { 
public:
  TailVerifica  ion( in   MAT, in   MF, in   MT ) :   ail( MAT, MF, MT ){}
  
  /* no  e: universal references (no   rvalue references) for perfec   forwarding */
    empla  e<   ypename... Args >
  TailVerifica  ion( in   expec  edValue, Args&&... args ) : 
      ail( s  d::forward< Args >( args )... ) {
    if(   his->fields[ posi  ion ] != expec  edValue ){ 
      Log::error( "The record {} number ({}) is inconsis  en   wi  h expec  a  ion.",
		  helper::name< posi  ion >, helper::symbol< posi  ion > );
      Log::info( "The read {} number is: {}",
		 helper::name< posi  ion >,   his->fields[ posi  ion ] );
      Log::info( "The expec  ed {} number is: {}",
		 helper::name< posi  ion >, expec  edValue ); 
      Log::info( "Error encoun  ered while verifying record   ail values" ); 
        hrow (posi  ion + 6); 
    }                                                                      
  }
};

/* Convenience   ypedefs of componen   verifiers */
  empla  e <   ypename   ail >
using MAT = TailVerifica  ion< 0,   ail >;

  empla  e <   ypename   ail >
using MF = TailVerifica  ion< 1,   ail >;

  empla  e <   ypename   ail >
using MT = TailVerifica  ion< 2,   ail >;

/* Convenience class providing a   ype defini  ion corresponding   o   he 
 * composi  ion of zero or more componen   verifiers 
 */
  empla  e<   empla  e<   ypename > class... Ts >
s  ruc   TailVerifier;

  empla  e<>
s  ruc   TailVerifier<>{
  using   ype = Tail;
};

  empla  e<   empla  e<   ypename > class T1, 
            empla  e<   ypename > class... Ts >
s  ruc   TailVerifier< T1, Ts... >{
  using   ype = T1<   ypename TailVerifier< Ts... >::  ype >;
};

/* An alias declaring which field or fields of a   ail ough     o be verified */
  empla  e<   empla  e<   ypename > class... Ts >
using TailVerifying =   ypename TailVerifier< Ts... >::  ype;
