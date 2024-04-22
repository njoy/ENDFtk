# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import Parameter

class Test_ENDFtk_MF5_Parameter( unittest.TestCase ) :
    """Unit test for the Parameter class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          59437 5455     \n'
              '          5          1                                            9437 5455     \n'
              ' 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n'
              ' 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          59437 5455     \n'
                '          5          1                                            9437 5455     \n'
                ' 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n'
                ' 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 5, chunk.NP )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, chunk.INT[0] )
            self.assertEqual( 5, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 5, chunk.boundaries[0] )
            self.assertEqual( 5, len( chunk.E ) )
            self.assertEqual( 5, len( chunk.energies ) )
            self.assertEqual( 5, len( chunk.values ) )
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
            self.assertAlmostEqual( 6.0, chunk.values[0] )
            self.assertAlmostEqual( 7.0, chunk.values[1] )
            self.assertAlmostEqual( 8.0, chunk.values[2] )
            self.assertAlmostEqual( 9.0, chunk.values[3] )
            self.assertAlmostEqual( 10.0, chunk.values[4] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9437, 5, 455 ) )

        # the data is given explicitly
        chunk = Parameter( boundaries = [ 5 ],
                           interpolants = [ 1 ],
                           energies = [ 1., 2., 3., 4., 5. ],
                           values = [ 6., 7., 8., 9., 10. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Parameter.from_string( self.chunk, 9437, 5, 455 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = Parameter( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = Parameter( boundaries = [ 5 ],
                               interpolants = [ 1, 2 ],
                               energies = [ 1., 2., 3., 4., 5. ],
                               values = [ 6., 7., 8., 9., 10. ] )

        with self.assertRaises( Exception ) :

            chunk = Parameter.from_string( self.invalid, 9437, 5, 455 )

if __name__ == '__main__' :

    unittest.main()
