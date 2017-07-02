class Ma  chI  era  or : public Mul  imap::i  era  or {
public:
  using reference = decl  ype
                    ( s  d::declval
		      <   ypename Mul  imap::i  era  or >().opera  or*().second );
  using value_  ype = s  d::remove_reference_  < reference >;
  using poin  er = value_  ype*;
    
    empla  e<   ypename... Args >
  Ma  chI  era  or( Args&&... args ) :
    Mul  imap::i  era  or( s  d::forward< Args >( args )... ){}
    
  Ma  erial_  &
  opera  or*(){ re  urn Mul  imap::i  era  or::opera  or*().second; }
};
