# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8 import FissionYieldData

class Test_ENDFtk_MF8_FissionYieldData( unittest.TestCase ) :
    """Unit test for the FissionYieldData class."""

    chunk = ( ' 2.530000-2 0.000000+0          2          0         12          39228 8454     \n'
              ' 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8454     \n'
              ' 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8454     \n' )

    invalid = ( ' 2.530000-2 0.000000+0          2          0         16          39228 8454     \n'
                ' 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8454     \n'
                ' 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8454     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.I )
            self.assertEqual( 2, chunk.interpolation_type )
            self.assertEqual( False, chunk.LE )
            self.assertEqual( False, chunk.is_energy_independent )
            self.assertEqual( 3, chunk.NFP )
            self.assertEqual( 3, chunk.number_fission_products )
            self.assertEqual( 0.0253, chunk.E )
            self.assertEqual( 0.0253, chunk.incident_energy )

            self.assertEqual( 3, len( chunk.ZAFP ) )
            self.assertEqual( 3, len( chunk.fission_product_identifiers ) )
            self.assertEqual( 3, len( chunk.FPS ) )
            self.assertEqual( 3, len( chunk.isomeric_states ) )
            self.assertEqual( 3, len( chunk.Y ) )
            self.assertEqual( 3, len( chunk.fission_yields ) )
            self.assertEqual( 3, len( chunk.DY ) )
            self.assertEqual( 3, len( chunk.fission_yield_uncertainties ) )
            self.assertEqual( 23066, chunk.ZAFP[0] )
            self.assertEqual( 54135, chunk.ZAFP[1] )
            self.assertEqual( 72171, chunk.ZAFP[2] )
            self.assertEqual( 23066, chunk.fission_product_identifiers[0] )
            self.assertEqual( 54135, chunk.fission_product_identifiers[1] )
            self.assertEqual( 72171, chunk.fission_product_identifiers[2] )
            self.assertEqual( 0, chunk.FPS[0] )
            self.assertEqual( 0, chunk.FPS[1] )
            self.assertEqual( 0, chunk.FPS[2] )
            self.assertEqual( 0, chunk.isomeric_states[0] )
            self.assertEqual( 0, chunk.isomeric_states[1] )
            self.assertEqual( 0, chunk.isomeric_states[2] )
            self.assertAlmostEqual( 2.05032e-19, chunk.Y[0] )
            self.assertAlmostEqual( 7.851250e-4, chunk.Y[1] )
            self.assertAlmostEqual( 0, chunk.Y[2] )
            self.assertAlmostEqual( 2.05032e-19, chunk.fission_yields[0] )
            self.assertAlmostEqual( 7.851250e-4, chunk.fission_yields[1] )
            self.assertAlmostEqual( 0, chunk.fission_yields[2] )
            self.assertAlmostEqual( 1.31220e-19, chunk.DY[0] )
            self.assertAlmostEqual( 4.710750e-5, chunk.DY[1] )
            self.assertAlmostEqual( 0, chunk.DY[2] )
            self.assertAlmostEqual( 1.31220e-19, chunk.fission_yield_uncertainties[0] )
            self.assertAlmostEqual( 4.710750e-5, chunk.fission_yield_uncertainties[1] )
            self.assertAlmostEqual( 0, chunk.fission_yield_uncertainties[2] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 8, 454 ) )

        # the data is given explicitly
        chunk = FissionYieldData( energy = 0.0253,
                                  interpolation = 2,
                                  identifiers = [ 23066, 54135, 72171 ],
                                  states = [ 0, 0, 0 ],
                                  yields = [ 2.05032e-19, 7.851250e-4, 0. ],
                                  uncertainties = [ 1.31220e-19, 4.710750e-5, 0. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = FissionYieldData.from_string( self.chunk, 9228, 8, 454 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = FissionYieldData( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = FissionYieldData.from_string( self.invalid, 9228, 8, 454 )

if __name__ == '__main__' :

    unittest.main()
