# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import SammyBackgroundRMatrix

class Test_ENDFtk_MF2_MT151_SammyBackgroundRMatrix( unittest.TestCase ) :
    """Unit test for the SammyBackgroundRMatrix class."""

    chunk = ( ' 0.000000+0 0.000000+0          1          2          0          02625 2151     \n'
              ' 1.000000+0 2.000000+0          0          0          5          02625 2151     \n'
              ' 3.000000+0 4.000000+0 5.000000+0 6.000000+0 7.000000+0           2625 2151     \n' )

    invalid_lbk = ( ' 0.000000+0 0.000000+0          1          3          0          02625 2151     \n'
                    ' 1.000000+0 2.000000+0          0          0          5          02625 2151     \n'
                    ' 3.000000+0 4.000000+0 5.000000+0 6.000000+0 7.000000+0           2625 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LBK )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( 1, chunk.LCH )
            self.assertEqual( 1, chunk.channel_index )

            self.assertAlmostEqual( 1., chunk.ED )
            self.assertAlmostEqual( 2., chunk.EU )
            self.assertAlmostEqual( 3., chunk.R0 )
            self.assertAlmostEqual( 4., chunk.R1 )
            self.assertAlmostEqual( 5., chunk.R2 )
            self.assertAlmostEqual( 6., chunk.S0 )
            self.assertAlmostEqual( 7., chunk.S1 )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = SammyBackgroundRMatrix( index = 1, ed = 1., eu = 2.,
                                        r0 = 3., r1 = 4., r2 = 5.,
                                        s0 = 6., s1 = 7. )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = SammyBackgroundRMatrix.from_string( self.chunk, 2625, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = SammyBackgroundRMatrix( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid list
        with self.assertRaises( Exception ) :

            chunk = SammyBackgroundRMatrix.from_string( self.invalid_lbk, 2625, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
