# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6.LAW1 import ThermalScatteringData

class Test_ENDFtk_MF6_LAW1_ThermalScatteringData( unittest.TestCase ) :
    """Unit test for the ThermalScatteringData class."""

    chunk_ltt5 = ( ' 0.000000+0 1.000000-5          0          0         18          61301 6222     \n'
                   ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n'
                   ' 9.999999-6 9.477167+1-5.379121-1 0.21062848 0.70490082 9.552579-11301 6222     \n'
                   ' 1.265100-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n' )

    chunk_ltt6 = ( ' 0.000000+0 1.000000-5          0          0          6          61301 6222     \n'
                  ' 1.000000-5 1.000000+0-5.379121-1 0.21062848 0.70490082 9.552579-11301 6222     \n' )

    def test_component( self ) :

        def verify_chunk_ltt5( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.LANG )
            self.assertEqual( 3, chunk.representation )
            self.assertEqual( 5, chunk.LTT )
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 18, chunk.NW )
            self.assertEqual( 6, chunk.N2 )

            data = chunk.data
            self.assertEqual( 18, len( data ) )
            self.assertAlmostEqual( 0., data[0] )
            self.assertAlmostEqual( 0., data[1] )
            self.assertAlmostEqual( 0., data[2] )
            self.assertAlmostEqual( 0., data[3] )
            self.assertAlmostEqual( 0., data[4] )
            self.assertAlmostEqual( 0., data[5] )
            self.assertAlmostEqual( 9.999999e-6, data[6] )
            self.assertAlmostEqual( 9.477167e+1, data[7] )
            self.assertAlmostEqual( -5.379121e-1, data[8] )
            self.assertAlmostEqual( 0.21062848, data[9] )
            self.assertAlmostEqual( 0.70490082, data[10] )
            self.assertAlmostEqual( 9.552579e-1, data[11] )
            self.assertAlmostEqual( 1.265100e-1, data[12] )
            self.assertAlmostEqual( 0., data[13] )
            self.assertAlmostEqual( 0., data[14] )
            self.assertAlmostEqual( 0., data[15] )
            self.assertAlmostEqual( 0., data[16] )
            self.assertAlmostEqual( 0., data[17] )

            self.assertEqual( 3, chunk.NEP )
            self.assertEqual( 3, chunk.number_secondary_energies )

            self.assertEqual( 3, len( chunk.EP ) )
            self.assertEqual( 3, len( chunk.energies ) )
            self.assertAlmostEqual( 0., chunk.EP[0] )
            self.assertAlmostEqual( 9.999999e-6, chunk.EP[1] )
            self.assertAlmostEqual( 1.265100e-1, chunk.EP[2] )
            self.assertAlmostEqual( 0., chunk.energies[0] )
            self.assertAlmostEqual( 9.999999e-6, chunk.energies[1] )
            self.assertAlmostEqual( 1.265100e-1, chunk.energies[2] )

            pp = chunk.PP
            self.assertEqual( 3, len( pp ) )
            self.assertAlmostEqual( 0., pp[0] )
            self.assertAlmostEqual( 9.477167e+1, pp[1] )
            self.assertAlmostEqual( 0., pp[2] )

            self.assertEqual( 3, len( chunk.MU ) )
            self.assertEqual( 3, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.MU[0] ) )
            self.assertAlmostEqual( 0., chunk.MU[0][0] )
            self.assertAlmostEqual( 0., chunk.MU[0][1] )
            self.assertAlmostEqual( 0., chunk.MU[0][2] )
            self.assertAlmostEqual( 0., chunk.MU[0][3] )
            self.assertEqual( 4, len( chunk.MU[1] ) )
            self.assertAlmostEqual( -5.379121e-1, chunk.MU[1][0] )
            self.assertAlmostEqual( 0.21062848, chunk.MU[1][1] )
            self.assertAlmostEqual( 0.70490082, chunk.MU[1][2] )
            self.assertAlmostEqual( 9.552579e-1, chunk.MU[1][3] )
            self.assertEqual( 4, len( chunk.MU[2] ) )
            self.assertAlmostEqual( 0., chunk.MU[2][0] )
            self.assertAlmostEqual( 0., chunk.MU[2][1] )
            self.assertAlmostEqual( 0., chunk.MU[2][2] )
            self.assertAlmostEqual( 0., chunk.MU[2][3] )
            self.assertEqual( 4, len( chunk.cosines[0] ) )
            self.assertAlmostEqual( 0., chunk.cosines[0][0] )
            self.assertAlmostEqual( 0., chunk.cosines[0][1] )
            self.assertAlmostEqual( 0., chunk.cosines[0][2] )
            self.assertAlmostEqual( 0., chunk.cosines[0][3] )
            self.assertEqual( 4, len( chunk.cosines[1] ) )
            self.assertAlmostEqual( -5.379121e-1, chunk.cosines[1][0] )
            self.assertAlmostEqual( 0.21062848, chunk.cosines[1][1] )
            self.assertAlmostEqual( 0.70490082, chunk.cosines[1][2] )
            self.assertAlmostEqual( 9.552579e-1, chunk.cosines[1][3] )
            self.assertEqual( 4, len( chunk.cosines[2] ) )
            self.assertAlmostEqual( 0., chunk.cosines[2][0] )
            self.assertAlmostEqual( 0., chunk.cosines[2][1] )
            self.assertAlmostEqual( 0., chunk.cosines[2][2] )
            self.assertAlmostEqual( 0., chunk.cosines[2][3] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_ltt5, chunk.to_string( 1301, 6, 222 ) )

        def verify_chunk_ltt6( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.LANG )
            self.assertEqual( 3, chunk.representation )
            self.assertEqual( 6, chunk.LTT )
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 6, chunk.NW )
            self.assertEqual( 6, chunk.N2 )

            data = chunk.data
            self.assertEqual( 6, len( data ) )
            self.assertAlmostEqual( 1e-5, data[0] )
            self.assertAlmostEqual( 1., data[1] )
            self.assertAlmostEqual( -5.379121e-1, data[2] )
            self.assertAlmostEqual( 0.21062848, data[3] )
            self.assertAlmostEqual( 0.70490082, data[4] )
            self.assertAlmostEqual( 9.552579e-1, data[5] )

            self.assertEqual( 1, chunk.NEP )
            self.assertEqual( 1, chunk.number_secondary_energies )

            self.assertEqual( 1, len( chunk.EP ) )
            self.assertEqual( 1, len( chunk.energies ) )
            self.assertAlmostEqual( 1e-5, chunk.EP[0] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )

            self.assertEqual( 1, len( chunk.PP ) )
            self.assertEqual( 1., chunk.PP[0] )

            self.assertEqual( 1, len( chunk.MU ) )
            self.assertEqual( 1, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.MU[0] ) )
            self.assertAlmostEqual( -5.379121e-1, chunk.MU[0][0] )
            self.assertAlmostEqual( 0.21062848, chunk.MU[0][1] )
            self.assertAlmostEqual( 0.70490082, chunk.MU[0][2] )
            self.assertAlmostEqual( 9.552579e-1, chunk.MU[0][3] )
            self.assertEqual( 4, len( chunk.cosines[0] ) )
            self.assertAlmostEqual( -5.379121e-1, chunk.cosines[0][0] )
            self.assertAlmostEqual( 0.21062848, chunk.cosines[0][1] )
            self.assertAlmostEqual( 0.70490082, chunk.cosines[0][2] )
            self.assertAlmostEqual( 9.552579e-1, chunk.cosines[0][3] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_ltt6, chunk.to_string( 1301, 6, 222 ) )

        # the data is given explicitly
        chunk = ThermalScatteringData( energy = 1e-5, n2 = 6,
                                       data = [ 0., 0., 0., 0., 0., 0.,
                                                9.999999e-6, 9.477167e+1, -5.379121e-1,
                                                0.21062848, 0.70490082, 9.552579e-1,
                                                1.265100e-1, 0., 0., 0., 0., 0. ] )

        verify_chunk_ltt5( self, chunk )

        # the data is read from a string
        chunk = ThermalScatteringData.from_string( self.chunk_ltt5, 1301, 6, 222 )

        verify_chunk_ltt5( self, chunk )

        # the data is copied
        copy = ThermalScatteringData( chunk )

        verify_chunk_ltt5( self, copy )

        # the data is given explicitly
        chunk = ThermalScatteringData( energy = 1e-5,
                                       cosines = [ -5.379121e-1, 0.21062848,
                                                   0.70490082, 9.552579e-1 ] )

        verify_chunk_ltt6( self, chunk )

        # the data is read from a string
        chunk = ThermalScatteringData.from_string( self.chunk_ltt6, 1301, 6, 222 )

        verify_chunk_ltt6( self, chunk )

        # the data is copied
        copy = ThermalScatteringData( chunk )

        verify_chunk_ltt6( self, copy )

if __name__ == '__main__' :

    unittest.main()
