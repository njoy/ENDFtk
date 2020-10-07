# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import ScatteringRadius

class Test_ENDFtk_MF2_MT151_ScatteringRadius( unittest.TestCase ) :
    """Unit test for the ScatteringRadius class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          59228 2151     \n'
              '          5          1                                            9228 2151     \n'
              ' 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09228 2151     \n'
              ' 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9228 2151     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          59228 2151     \n'
                '          5          1                                            9228 2151     \n'
                ' 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09228 2151     \n'
                ' 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9228 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 5, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 5, chunk.boundaries[0] )
            self.assertEqual( 5, len( chunk.E ) )
            self.assertEqual( 5, len( chunk.energies ) )
            self.assertEqual( 5, len( chunk.AP ) )
            self.assertEqual( 5, len( chunk.radii ) )
            self.assertAlmostEqual( 1.0, chunk.E[0] )
            self.assertAlmostEqual( 2.0, chunk.E[1] )
            self.assertAlmostEqual( 3.0, chunk.E[2] )
            self.assertAlmostEqual( 4.0, chunk.E[3] )
            self.assertAlmostEqual( 5.0, chunk.E[4] )
            self.assertAlmostEqual( 1.0, chunk.energies[0] )
            self.assertAlmostEqual( 2.0, chunk.energies[1] )
            self.assertAlmostEqual( 3.0, chunk.energies[2] )
            self.assertAlmostEqual( 4.0, chunk.energies[3] )
            self.assertAlmostEqual( 5.0, chunk.energies[4] )
            self.assertAlmostEqual( 6.0, chunk.AP[0] )
            self.assertAlmostEqual( 7.0, chunk.AP[1] )
            self.assertAlmostEqual( 8.0, chunk.AP[2] )
            self.assertAlmostEqual( 9.0, chunk.AP[3] )
            self.assertAlmostEqual( 10.0, chunk.AP[4] )
            self.assertAlmostEqual( 6.0, chunk.radii[0] )
            self.assertAlmostEqual( 7.0, chunk.radii[1] )
            self.assertAlmostEqual( 8.0, chunk.radii[2] )
            self.assertAlmostEqual( 9.0, chunk.radii[3] )
            self.assertAlmostEqual( 10.0, chunk.radii[4] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 2, 151 ) )

        # the data is given explicitly
        chunk = ScatteringRadius( boundaries = [ 5 ],
                                  interpolants = [ 1 ],
                                  energies = [ 1., 2., 3., 4., 5. ],
                                  radii = [ 6., 7., 8., 9., 10. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ScatteringRadius.from_string( self.chunk, 9228, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ScatteringRadius( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid TAB1
        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid )

if __name__ == '__main__' :

    unittest.main()
