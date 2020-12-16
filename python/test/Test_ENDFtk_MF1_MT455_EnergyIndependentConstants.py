# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT455 import EnergyIndependentConstants

class Test_ENDFtk_MF1_MT455_EnergyIndependentConstants( unittest.TestCase ) :
    """Unit test for the EnergyIndependentConstants class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          6          09228 1455     \n'
              ' 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LDG )
            self.assertEqual( 0, chunk.type )
            self.assertEqual( 6, chunk.NNF )
            self.assertEqual( 6, chunk.number_precursors )

            self.assertEqual( 6, len( chunk.lambdas ) )
            self.assertEqual( 6, len( chunk.decay_constants ) )
            self.assertAlmostEqual( 0.013336, chunk.lambdas[0] )
            self.assertAlmostEqual( 0.032739, chunk.lambdas[1] )
            self.assertAlmostEqual( 0.12078, chunk.lambdas[2] )
            self.assertAlmostEqual( 0.30278, chunk.lambdas[3] )
            self.assertAlmostEqual( 0.84949, chunk.lambdas[4] )
            self.assertAlmostEqual( 2.853000, chunk.lambdas[5] )
            self.assertAlmostEqual( 0.013336, chunk.decay_constants[0] )
            self.assertAlmostEqual( 0.032739, chunk.decay_constants[1] )
            self.assertAlmostEqual( 0.12078, chunk.decay_constants[2] )
            self.assertAlmostEqual( 0.30278, chunk.decay_constants[3] )
            self.assertAlmostEqual( 0.84949, chunk.decay_constants[4] )
            self.assertAlmostEqual( 2.853000, chunk.decay_constants[5] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 455 ) )

        # the data is given explicitly
        chunk = EnergyIndependentConstants(
                    constants = [ 1.3336e-2, 3.2739e-2, 1.2078e-1,
                                  3.0278e-1, 8.4949e-1, 2.853 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = EnergyIndependentConstants.from_string( self.chunk, 9228, 1, 455 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = EnergyIndependentConstants( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = EnergyIndependentConstants.from_string( self.invalid, 9228, 1, 455 )

if __name__ == '__main__' :

    unittest.main()
