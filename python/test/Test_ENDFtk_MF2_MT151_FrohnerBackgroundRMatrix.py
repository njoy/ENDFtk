# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import FrohnerBackgroundRMatrix

class Test_ENDFtk_MF2_MT151_FrohnerBackgroundRMatrix( unittest.TestCase ) :
    """Unit test for the FrohnerBackgroundRMatrix class."""

    chunk = ( ' 0.000000+0 0.000000+0          1          3          0          02625 2151     \n'
              ' 1.000000+0 2.000000+0          0          0          3          02625 2151     \n'
              ' 3.000000+0 4.000000+0 5.000000+0                                 2625 2151     \n' )

    invalid_lbk = ( ' 0.000000+0 0.000000+0          1          4          0          02625 2151     \n'
                    ' 1.000000+0 2.000000+0          0          0          3          02625 2151     \n'
                    ' 3.000000+0 4.000000+0 5.000000+0                                 2625 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.LBK )
            self.assertEqual( 3, chunk.representation )
            self.assertEqual( 1, chunk.LCH )
            self.assertEqual( 1, chunk.channel_index )

            self.assertAlmostEqual( 1., chunk.ED )
            self.assertAlmostEqual( 2., chunk.EU )
            self.assertAlmostEqual( 3., chunk.R0 )
            self.assertAlmostEqual( 4., chunk.S0 )
            self.assertAlmostEqual( 5., chunk.GA )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = FrohnerBackgroundRMatrix( index = 1, ed = 1., eu = 2.,
                                          r0 = 3., s0 = 4., ga = 5. )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = FrohnerBackgroundRMatrix.from_string( self.chunk, 2625, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = FrohnerBackgroundRMatrix( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid list
        with self.assertRaises( Exception ) :

            chunk = FrohnerBackgroundRMatrix.from_string( self.invalid_lbk, 2625, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
