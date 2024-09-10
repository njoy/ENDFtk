# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF26.LAW2 import TabulatedDistribution

class Test_ENDFtk_MF26_LAW2_TabulatedDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedDistribution class."""

    chunk_lang12 = ( ' 0.000000+0 1.000000-5         12          0          6          3922826  5     \n'
                     ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n' )

    chunk_lang14 = ( ' 0.000000+0 1.000000-5         14          0          6          3922826  5     \n'
                     ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          1          0          6          3922826  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n' )

    invalid_size = ( ' 0.000000+0 1.000000-5         12          0          6          4922826  5     \n'
                     ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n' )

    def test_component( self ) :

        def verify_chunk_lang12( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 12, chunk.LANG )
            self.assertEqual( 6, chunk.NW )
            self.assertEqual( 3, chunk.NL )
            self.assertEqual( 3, chunk.number_cosine_values )
            self.assertEqual( 3, len( chunk.MU ) )
            self.assertEqual( 3, len( chunk.cosines ) )
            self.assertAlmostEqual( 1., chunk.MU[0] )
            self.assertAlmostEqual( 3., chunk.MU[1] )
            self.assertAlmostEqual( 5., chunk.MU[2] )
            self.assertAlmostEqual( 1., chunk.cosines[0] )
            self.assertAlmostEqual( 3., chunk.cosines[1] )
            self.assertAlmostEqual( 5., chunk.cosines[2] )
            self.assertEqual( 3, len( chunk.F ) )
            self.assertEqual( 3, len( chunk.probabilities ) )
            self.assertAlmostEqual( 2., chunk.F[0] )
            self.assertAlmostEqual( 4., chunk.F[1] )
            self.assertAlmostEqual( 6., chunk.F[2] )
            self.assertAlmostEqual( 2., chunk.probabilities[0] )
            self.assertAlmostEqual( 4., chunk.probabilities[1] )
            self.assertAlmostEqual( 6., chunk.probabilities[2] )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 2, chunk.INT[0] )
            self.assertEqual( 3, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 3, chunk.boundaries[0] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lang12, chunk.to_string( 9228, 26, 5 ) )

        def verify_chunk_lang14( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 14, chunk.LANG )
            self.assertEqual( 6, chunk.NW )
            self.assertEqual( 3, chunk.NL )
            self.assertEqual( 3, chunk.number_cosine_values )
            self.assertEqual( 3, len( chunk.MU ) )
            self.assertEqual( 3, len( chunk.cosines ) )
            self.assertAlmostEqual( 1., chunk.MU[0] )
            self.assertAlmostEqual( 3., chunk.MU[1] )
            self.assertAlmostEqual( 5., chunk.MU[2] )
            self.assertAlmostEqual( 1., chunk.cosines[0] )
            self.assertAlmostEqual( 3., chunk.cosines[1] )
            self.assertAlmostEqual( 5., chunk.cosines[2] )
            self.assertEqual( 3, len( chunk.F ) )
            self.assertEqual( 3, len( chunk.probabilities ) )
            self.assertAlmostEqual( 2., chunk.F[0] )
            self.assertAlmostEqual( 4., chunk.F[1] )
            self.assertAlmostEqual( 6., chunk.F[2] )
            self.assertAlmostEqual( 2., chunk.probabilities[0] )
            self.assertAlmostEqual( 4., chunk.probabilities[1] )
            self.assertAlmostEqual( 6., chunk.probabilities[2] )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 4, chunk.INT[0] )
            self.assertEqual( 3, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 4, chunk.interpolants[0] )
            self.assertEqual( 3, chunk.boundaries[0] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lang14, chunk.to_string( 9228, 26, 5 ) )

        # the data is given explicitly
        chunk = TabulatedDistribution( energy = 1e-5, lang = 12,
                                       cosines = [ 1, 3, 5 ], probabilities = [ 2, 4, 6 ] )

        verify_chunk_lang12( self, chunk )

        # the data is read from a string
        chunk = TabulatedDistribution.from_string( self.chunk_lang12, 9228, 26, 5 )

        verify_chunk_lang12( self, chunk )

        # the data is copied
        copy = TabulatedDistribution( chunk )

        verify_chunk_lang12( self, copy )

        # the data is given explicitly
        chunk = TabulatedDistribution( energy = 1e-5, lang = 14,
                                       cosines = [ 1, 3, 5 ], probabilities = [ 2, 4, 6 ] )

        verify_chunk_lang14( self, chunk )

        # the data is read from a string
        chunk = TabulatedDistribution.from_string( self.chunk_lang14, 9228, 26, 5 )

        verify_chunk_lang14( self, chunk )

        # the data is copied
        copy = TabulatedDistribution( chunk )

        verify_chunk_lang14( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = TabulatedDistribution.from_string( self.invalid, 9228, 26, 5 )

        with self.assertRaises( Exception ) :

            chunk = TabulatedDistribution.from_string( self.invalid_size, 9228, 26, 5 )

if __name__ == '__main__' :

    unittest.main()
