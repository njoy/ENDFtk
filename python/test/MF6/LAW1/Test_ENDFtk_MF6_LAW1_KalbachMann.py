# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6.LAW1 import KalbachMann

class Test_ENDFtk_MF6_LAW1_KalbachMann( unittest.TestCase ) :
    """Unit test for the KalbachMann class."""

    chunk_na1 = ( ' 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n'
                  ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    chunk_na2 = ( ' 0.000000+0 1.000000-5          0          2          8          29228 6  5     \n'
                  ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                  ' 7.000000+0 8.000000+0                                            9228 6  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          3         10          29228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1                      9228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk_na1( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LANG )
            self.assertEqual( 2, chunk.representation )
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 0, chunk.ND )
            self.assertEqual( 0, chunk.number_discrete_energies )
            self.assertEqual( 1, chunk.NA )
            self.assertEqual( 1, chunk.number_angular_parameters )
            self.assertEqual( 6, chunk.NW )
            self.assertEqual( 2, chunk.NEP )
            self.assertEqual( 2, chunk.number_secondary_energies )
            self.assertEqual( 2, len( chunk.EP ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertAlmostEqual( 1., chunk.EP[0] )
            self.assertAlmostEqual( 4., chunk.EP[1] )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 4., chunk.energies[1] )
            self.assertEqual( 2, len( chunk.parameters ) )
            self.assertAlmostEqual( 2., chunk.parameters[0][0] )
            self.assertAlmostEqual( 3., chunk.parameters[0][1] )
            self.assertAlmostEqual( 5., chunk.parameters[1][0] )
            self.assertAlmostEqual( 6., chunk.parameters[1][1] )
            self.assertEqual( 2, len( chunk.F0 ) )
            self.assertEqual( 2, len( chunk.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., chunk.F0[0] )
            self.assertAlmostEqual( 5., chunk.F0[1] )
            self.assertAlmostEqual( 2., chunk.total_emission_probabilities[0] )
            self.assertAlmostEqual( 5., chunk.total_emission_probabilities[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_na1, chunk.to_string( 9228, 6, 5 ) )

        def verify_chunk_na2( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LANG )
            self.assertEqual( 2, chunk.representation )
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 0, chunk.ND )
            self.assertEqual( 0, chunk.number_discrete_energies )
            self.assertEqual( 2, chunk.NA )
            self.assertEqual( 2, chunk.number_angular_parameters )
            self.assertEqual( 8, chunk.NW )
            self.assertEqual( 2, chunk.NEP )
            self.assertEqual( 2, chunk.number_secondary_energies )
            self.assertEqual( 2, len( chunk.EP ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertAlmostEqual( 1., chunk.EP[0] )
            self.assertAlmostEqual( 5., chunk.EP[1] )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 5., chunk.energies[1] )
            self.assertEqual( 2, len( chunk.parameters ) )
            self.assertAlmostEqual( 2., chunk.parameters[0][0] )
            self.assertAlmostEqual( 3., chunk.parameters[0][1] )
            self.assertAlmostEqual( 4., chunk.parameters[0][2] )
            self.assertAlmostEqual( 6., chunk.parameters[1][0] )
            self.assertAlmostEqual( 7., chunk.parameters[1][1] )
            self.assertAlmostEqual( 8., chunk.parameters[1][2] )
            self.assertEqual( 2, len( chunk.F0 ) )
            self.assertEqual( 2, len( chunk.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., chunk.F0[0] )
            self.assertAlmostEqual( 6., chunk.F0[1] )
            self.assertAlmostEqual( 2., chunk.total_emission_probabilities[0] )
            self.assertAlmostEqual( 6., chunk.total_emission_probabilities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_na2, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = KalbachMann( energy = 1e-5, nd = 0,
                             data = [ [ 1., 2., 3. ], [ 4., 5., 6. ] ] )

        verify_chunk_na1( self, chunk )

        # the data is read from a string
        chunk = KalbachMann.from_string( self.chunk_na1, 9228, 6, 5 )

        verify_chunk_na1( self, chunk )

        # the data is copied
        copy = KalbachMann( chunk )

        verify_chunk_na1( self, copy )

        # the data is given explicitly
        chunk = KalbachMann( energy = 1e-5, nd = 0,
                             data = [ [ 1., 2., 3., 4. ], [ 5., 6., 7., 8. ] ] )

        verify_chunk_na2( self, chunk )

        # the data is read from a string
        chunk = KalbachMann.from_string( self.chunk_na2, 9228, 6, 5 )

        verify_chunk_na2( self, chunk )

        # the data is copied
        copy = KalbachMann( chunk )

        verify_chunk_na2( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # not the same NA
        with self.assertRaises( Exception ) :

            chunk = KalbachMann( energy = 1e-5, nd = 0,
                                 data = [ [ 1., 2. ], [ 4., 5., 6. ] ] )

        with self.assertRaises( Exception ) :

            chunk = KalbachMann.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
