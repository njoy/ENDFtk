# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import SammyBackgroundRMatrix
from ENDFtk.MF2.MT151 import BackgroundChannels

class Test_ENDFtk_MF2_MT151_BackgroundChannels( unittest.TestCase ) :
    """Unit test for the BackgroundChannels class."""

    chunk = ( ' 0.000000+0 0.000000+0          2          2          0          02625 2151     \n'
              ' 1.000000+0 2.000000+0          0          0          5          02625 2151     \n'
              ' 3.000000+0 4.000000+0 5.000000+0 6.000000+0 7.000000+0           2625 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.NCH )
            self.assertEqual( 3, chunk.number_channels )
            self.assertEqual( 1, chunk.KBK )
            self.assertEqual( 1, chunk.number_background_channels )

            self.assertEqual( 3, len( chunk.background_rmatrices ) )
            self.assertEqual( True, None == chunk.background_rmatrices[0] )
            self.assertEqual( False, None == chunk.background_rmatrices[1] )
            self.assertEqual( True, None == chunk.background_rmatrices[2] )

            self.assertEqual( True, isinstance( chunk.background_rmatrices[1],
                                                SammyBackgroundRMatrix ) )

            self.assertEqual( 2, chunk.background_rmatrices[1].LBK )
            self.assertEqual( 2, chunk.background_rmatrices[1].representation )
            self.assertEqual( 2, chunk.background_rmatrices[1].LCH )
            self.assertEqual( 2, chunk.background_rmatrices[1].channel_index )

            self.assertAlmostEqual( 1., chunk.background_rmatrices[1].ED )
            self.assertAlmostEqual( 2., chunk.background_rmatrices[1].EU )
            self.assertAlmostEqual( 3., chunk.background_rmatrices[1].R0 )
            self.assertAlmostEqual( 4., chunk.background_rmatrices[1].R1 )
            self.assertAlmostEqual( 5., chunk.background_rmatrices[1].R2 )
            self.assertAlmostEqual( 6., chunk.background_rmatrices[1].S0 )
            self.assertAlmostEqual( 7., chunk.background_rmatrices[1].S1 )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = BackgroundChannels(
                    nch = 3,
                    channels = [ SammyBackgroundRMatrix( 2, 1., 2., 3., 4., 5., 6., 7. ) ] )

        verify_chunk( self, chunk )

        # the data is copied
        copy = BackgroundChannels( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
