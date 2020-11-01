# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import DecayMode

class Test_ENDFtk_MF8_MT457_DecayMode( unittest.TestCase ) :
    """Unit test for the DecayMode class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 4., chunk.RTYP )
            self.assertEqual( 4., chunk.decay_chain )
            self.assertEqual( 0., chunk.RFS )
            self.assertEqual( 0., chunk.final_isomeric_state )
            self.assertEqual( 5.637120e+6, chunk.Q[0] )
            self.assertEqual( 2.549510e+2, chunk.Q[1] )
            self.assertEqual( 5.637120e+6, chunk.q_value[0] )
            self.assertEqual( 2.549510e+2, chunk.q_value[1] )
            self.assertEqual( 4.590000e-3, chunk.BR[0] )
            self.assertEqual( 1.200000e-4, chunk.BR[1] )
            self.assertEqual( 4.590000e-3, chunk.branching_ratio[0] )
            self.assertEqual( 1.200000e-4, chunk.branching_ratio[1] )

        # the data is given explicitly
        chunk = DecayMode( rtyp = 4.,  rfs = 0., q = 5.637120e+6,
                           dq = 2.549510e+2, br = 4.590000e-3,
                           dbr = 1.200000e-4 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DecayMode( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
