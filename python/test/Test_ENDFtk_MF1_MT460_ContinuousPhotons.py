# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT460 import ContinuousPhotons

class Test_ENDFtk_MF1_MT460_ContinuousPhotons( unittest.TestCase ) :
    """Unit test for the ContinuousPhotons class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          6          09228 1460     \n'
              ' 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1460     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          0          09228 1460     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LO )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( 0, chunk.NG )
            self.assertEqual( 0, chunk.number_discrete_photons )
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
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 460 ) )

        # the data is given explicitly
        chunk = ContinuousPhotons( constants = [ 1.333600e-2, 3.273900e-2,
                                                 1.207800e-1, 3.027800e-1,
                                                 8.494900e-1, 2.853000e+0 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ContinuousPhotons.from_string( self.chunk, 9228, 1, 460 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ContinuousPhotons( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = ContinuousPhotons( constants = [] )

        with self.assertRaises( Exception ) :

            chunk = ContinuousPhotons.from_string( self.invalidNNF, 9228, 1, 460 )

if __name__ == '__main__' :

    unittest.main()
