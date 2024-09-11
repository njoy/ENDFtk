# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151.LCOMP1 import ResonanceParameters

class Test_ENDFtk_MF32_MT151_LCOMP1_ResonanceParameters( unittest.TestCase ) :
    """Unit test for the ResonanceParameters class."""

    chunk = ( ' 0.000000+0 0.000000+0          6          2         24          4262532151     \n'
              '-1.223300+6 1.000000+0 9.611086+5 2.000000+0 3.000000+0 4.000000+0262532151     \n'
              ' 5.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 7.788000+3 1.455000+0 1.187354+3 6.000000+0 7.000000+0 8.000000+0262532151     \n'
              ' 9.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n' )

    invalid_size = ( ' 0.000000+0 0.000000+0          6          2         23          4262532151     \n'
                     '-1.223300+6 1.000000+0 9.611086+5 1.000000+0 2.000000+0 3.000000+0262532151     \n'
                     ' 4.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
                     ' 7.788000+3 1.455000+0 1.187354+3 5.000000+0 6.000000+0 7.000000+0262532151     \n'
                     ' 8.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0           262532151     \n' )

    zero_size = ( ' 0.000000+0 0.000000+0          6          2          0          4262532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 6, chunk.NCH )
            self.assertEqual( 6, chunk.number_channels )
            self.assertEqual( 2, chunk.NRB )
            self.assertEqual( 2, chunk.number_resonances )
            self.assertEqual( 4, chunk.NX )
            self.assertEqual( 4, chunk.number_lines )

            self.assertEqual( 2, len( chunk.ER ) )
            self.assertEqual( 2, len( chunk.resonance_energies ) )
            self.assertEqual( 2, len( chunk.GAM ) )
            self.assertEqual( 2, len( chunk.resonance_parameters ) )

            self.assertAlmostEqual( -1.223300e+6, chunk.ER[0] )
            self.assertAlmostEqual(  7.788000e+3, chunk.ER[1] )
            self.assertAlmostEqual( -1.223300e+6, chunk.resonance_energies[0] )
            self.assertAlmostEqual(  7.788000e+3, chunk.resonance_energies[1] )
            self.assertEqual( 11, len( chunk.GAM[0] ) )
            self.assertEqual( 11, len( chunk.GAM[1] ) )
            self.assertAlmostEqual( 1., chunk.GAM[0][0] )
            self.assertAlmostEqual( 9.611086e+5, chunk.GAM[0][1] )
            self.assertAlmostEqual( 2., chunk.GAM[0][2] )
            self.assertAlmostEqual( 3., chunk.GAM[0][3] )
            self.assertAlmostEqual( 4., chunk.GAM[0][4] )
            self.assertAlmostEqual( 5., chunk.GAM[0][5] )
            self.assertAlmostEqual( 0., chunk.GAM[0][6] )
            self.assertAlmostEqual( 0., chunk.GAM[0][7] )
            self.assertAlmostEqual( 0., chunk.GAM[0][8] )
            self.assertAlmostEqual( 0., chunk.GAM[0][9] )
            self.assertAlmostEqual( 0., chunk.GAM[0][10] )
            self.assertAlmostEqual( 1.455, chunk.GAM[1][0] )
            self.assertAlmostEqual( 1.187354e+3, chunk.GAM[1][1] )
            self.assertAlmostEqual( 6., chunk.GAM[1][2] )
            self.assertAlmostEqual( 7., chunk.GAM[1][3] )
            self.assertAlmostEqual( 8., chunk.GAM[1][4] )
            self.assertAlmostEqual( 9., chunk.GAM[1][5] )
            self.assertAlmostEqual( 0., chunk.GAM[1][6] )
            self.assertAlmostEqual( 0., chunk.GAM[1][7] )
            self.assertAlmostEqual( 0., chunk.GAM[1][8] )
            self.assertAlmostEqual( 0., chunk.GAM[1][9] )
            self.assertAlmostEqual( 0., chunk.GAM[1][10] )
            self.assertEqual( 11, len( chunk.resonance_parameters[0] ) )
            self.assertEqual( 11, len( chunk.resonance_parameters[1] ) )
            self.assertAlmostEqual( 1., chunk.resonance_parameters[0][0] )
            self.assertAlmostEqual( 9.611086e+5, chunk.resonance_parameters[0][1] )
            self.assertAlmostEqual( 2., chunk.resonance_parameters[0][2] )
            self.assertAlmostEqual( 3., chunk.resonance_parameters[0][3] )
            self.assertAlmostEqual( 4., chunk.resonance_parameters[0][4] )
            self.assertAlmostEqual( 5., chunk.resonance_parameters[0][5] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[0][6] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[0][7] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[0][8] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[0][9] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[0][10] )
            self.assertAlmostEqual( 1.455, chunk.resonance_parameters[1][0] )
            self.assertAlmostEqual( 1.187354e+3, chunk.resonance_parameters[1][1] )
            self.assertAlmostEqual( 6., chunk.resonance_parameters[1][2] )
            self.assertAlmostEqual( 7., chunk.resonance_parameters[1][3] )
            self.assertAlmostEqual( 8., chunk.resonance_parameters[1][4] )
            self.assertAlmostEqual( 9., chunk.resonance_parameters[1][5] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[1][6] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[1][7] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[1][8] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[1][9] )
            self.assertAlmostEqual( 0., chunk.resonance_parameters[1][10] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 32, 151 ) )

        # the data is given explicitly
        chunk = ResonanceParameters( energies = [ -1.223300e+6, 7.788000e+3 ],
                                     parameters = [ [ 1., 9.611086e+5, 2., 3., 4., 5. ],
                                                    [ 1.455, 1.187354e+3, 6., 7., 8., 9. ] ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ResonanceParameters.from_string( self.chunk, 2625, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ResonanceParameters( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = ResonanceParameters( energies = [ -1.223300e+6, 7.788000e+3 ],
                                         parameters = [ [ 1., 9.611086e+5, 2., 3., 4., 5. ] ] )

        # channel data incorrect
        with self.assertRaises( Exception ) :

            chunk = ResonanceParameters( energies = [ -1.223300e+6, 7.788000e+3 ],
                                         parameters = [ [ 1., 9.611086e+5, 2., 3., 4., 5. ],
                                                        [ 1.455, 1.187354e+3, 6., 7., 8. ] ] )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = ResonanceParameters( energies = [], parameters = [] )

        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = ResonanceParameters.from_string( self.invalid_size, 2625, 32, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = ResonanceParameters.from_string( self.zero_size, 2625, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
