# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import TabulatedBackgroundRMatrix

class Test_ENDFtk_MF2_MT151_TabulatedBackgroundRMatrix( unittest.TestCase ) :
    """Unit test for the TabulatedBackgroundRMatrix class."""

    chunk = ( ' 0.000000+0 0.000000+0          1          1          0          02625 2151     \n'
              ' 0.000000+0 0.000000+0          0          0          1          22625 2151     \n'
              '          2          2                                            2625 2151     \n'
              ' 1.000000-5 1.000000+0 2.000000+7 2.000000+0                      2625 2151     \n'
              ' 0.000000+0 0.000000+0          0          0          1          22625 2151     \n'
              '          2          2                                            2625 2151     \n'
              ' 1.000000-5 2.000000+0 2.000000+7 1.000000+0                      2625 2151     \n' )

    invalid_lbk = ( ' 0.000000+0 0.000000+0          1          5          0          02625 2151     \n'
                    ' 0.000000+0 0.000000+0          0          0          1          22625 2151     \n'
                    '          2          2                                            2625 2151     \n'
                    ' 1.000000-5 1.000000+0 2.000000+7 2.000000+0                      2625 2151     \n'
                    ' 0.000000+0 0.000000+0          0          0          1          22625 2151     \n'
                    '          2          2                                            2625 2151     \n'
                    ' 1.000000-5 2.000000+0 2.000000+7 1.000000+0                      2625 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LBK )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( 1, chunk.LCH )
            self.assertEqual( 1, chunk.channel_index )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.RB ) )
            self.assertEqual( 2, len( chunk.rmatrix ) )
            self.assertEqual( 2, len( chunk.RBR ) )
            self.assertEqual( 2, len( chunk.real ) )
            self.assertEqual( 2, len( chunk.RBI ) )
            self.assertEqual( 2, len( chunk.imaginary ) )

            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 2e+7, chunk.E[1] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 2e+7, chunk.energies[1] )
            self.assertAlmostEqual( 1., chunk.RBR[0] )
            self.assertAlmostEqual( 2., chunk.RBR[1] )
            self.assertAlmostEqual( 1., chunk.real[0] )
            self.assertAlmostEqual( 2., chunk.real[1] )
            self.assertAlmostEqual( 2., chunk.RBI[0] )
            self.assertAlmostEqual( 1., chunk.RBI[1] )
            self.assertAlmostEqual( 2., chunk.imaginary[0] )
            self.assertAlmostEqual( 1., chunk.imaginary[1] )
            self.assertAlmostEqual( 1., chunk.RB[0].real )
            self.assertAlmostEqual( 2., chunk.RB[1].real )
            self.assertAlmostEqual( 2., chunk.RB[0].imag )
            self.assertAlmostEqual( 1., chunk.RB[1].imag )
            self.assertAlmostEqual( 1. + 2.j, chunk.rmatrix[0] )
            self.assertAlmostEqual( 2. + 1.j, chunk.rmatrix[1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = TabulatedBackgroundRMatrix( index = 1,
                                            boundaries = [ 2 ],
                                            interpolants = [ 2 ],
                                            energies = [ 1e-5, 2e+7 ],
                                            rmatrix = [ 1. + 2.j, 2. + 1.j ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = TabulatedBackgroundRMatrix.from_string( self.chunk, 2625, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedBackgroundRMatrix( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid list
        with self.assertRaises( Exception ) :

            chunk = TabulatedBackgroundRMatrix.from_string( self.invalid_lbk, 2625, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
