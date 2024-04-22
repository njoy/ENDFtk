# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1 import TabulatedMultiplicity

class Test_ENDFtk_MF1_TabulatedMultiplicity( unittest.TestCase ) :
    """Unit test for the TabulatedMultiplicity class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          49228 1455     \n'
              '          4          2                                            9228 1455     \n'
              ' 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n'
              ' 2.000000+7 5.209845+0                                            9228 1455     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          49228 1455     \n'
                '          4          2                                            9228 1455     \n'
                ' 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n'
                ' 2.000000+7 5.209845+0                                            9228 1455     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LNU )
            self.assertEqual( 2, chunk.representation )

            self.assertEqual( 4, chunk.NP )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 2, chunk.INT[0] )
            self.assertEqual( 4, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 4, chunk.boundaries[0] )

            self.assertEqual( 4, len( chunk.E ) )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.NU ) )
            self.assertEqual( 4, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 0.0253, chunk.E[1] )
            self.assertAlmostEqual( 0.05, chunk.E[2] )
            self.assertAlmostEqual( 2e+7, chunk.E[3] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 0.0253, chunk.energies[1] )
            self.assertAlmostEqual( 0.05, chunk.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.energies[3] )
            self.assertAlmostEqual( 2.4367, chunk.NU[0] )
            self.assertAlmostEqual( 2.4367, chunk.NU[1] )
            self.assertAlmostEqual( 2.4367, chunk.NU[2] )
            self.assertAlmostEqual( 5.209845, chunk.NU[3] )
            self.assertAlmostEqual( 2.4367, chunk.multiplicities[0] )
            self.assertAlmostEqual( 2.4367, chunk.multiplicities[1] )
            self.assertAlmostEqual( 2.4367, chunk.multiplicities[2] )
            self.assertAlmostEqual( 5.209845, chunk.multiplicities[3] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 455 ) )

        # the data is given explicitly
        chunk = TabulatedMultiplicity( boundaries = [ 4 ], interpolants = [ 2 ],
                                       energies = [ 1e-5, 2.53e-2, 5e-2, 2e+7 ],
                                       multiplicities = [ 2.4367, 2.4367, 2.4367, 5.209845 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = TabulatedMultiplicity.from_string( self.chunk, 9228, 1, 455 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedMultiplicity( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = TabulatedMultiplicity( boundaries = [ 4, 6 ], interpolants = [ 2 ],
                                           energies = [ 1e-5, 2.53e-2, 5e-2, 2e+7 ],
                                           multiplicities = [ 2.4367, 2.4367, 2.4367, 5.209845 ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedMultiplicity.from_string( self.invalid, 9228, 1, 455 )

if __name__ == '__main__' :

    unittest.main()
