# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import ShortRangeReichMooreBlock

class Test_ENDFtk_MF32_MT151_ShortRangeReichMooreBlock( unittest.TestCase ) :
    """Unit test for the ShortRangeReichMooreBlock class."""

    chunk = ( ' 0.000000+0 0.000000+0          4          0         48          2102532151     \n'
              '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
              ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
              ' 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n'
              ' 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n'
              ' 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n'
              ' 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n'
              ' 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n'
              ' 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n' )

    invalid_size = ( ' 0.000000+0 0.000000+0          4          0         47          2102532151     \n'
                     '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                     ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                     ' 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n'
                     ' 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n'
                     ' 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n'
                     ' 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n'
                     ' 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n'
                     ' 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1           102532151     \n' )

    zero_size = ( ' 0.000000+0 0.000000+0          0          0          0          2102532151     \n' )

    no_number_resonances = ( ' 0.000000+0 0.000000+0          4          0         48          0102532151     \n'
                             '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                             ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                             ' 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n'
                             ' 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n'
                             ' 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n'
                             ' 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n'
                             ' 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n'
                             ' 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.MPAR )
            self.assertEqual( 4, chunk.number_parameters_with_covariances )

            self.assertEqual( 2, chunk.NRB )
            self.assertEqual( 2, chunk.number_resonances )
            self.assertEqual( 2, len( chunk.ER ) )
            self.assertEqual( 2, len( chunk.resonance_energies ) )
            self.assertEqual( 2, len( chunk.AJ ) )
            self.assertEqual( 2, len( chunk.spin_values ) )
            self.assertEqual( 2, len( chunk.GN ) )
            self.assertEqual( 2, len( chunk.neutron_widths ) )
            self.assertEqual( 2, len( chunk.GG ) )
            self.assertEqual( 2, len( chunk.gamma_widths ) )
            self.assertEqual( 2, len( chunk.GFA ) )
            self.assertEqual( 2, len( chunk.first_fission_widths ) )
            self.assertEqual( 2, len( chunk.GFB ) )
            self.assertEqual( 2, len( chunk.second_fission_widths ) )

            self.assertAlmostEqual( -1.470000e+5, chunk.ER[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.ER[1] )
            self.assertAlmostEqual( -1.470000e+5, chunk.resonance_energies[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.resonance_energies[1] )
            self.assertAlmostEqual( 0.5, chunk.AJ[0] )
            self.assertAlmostEqual( 0.5, chunk.AJ[1] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[0] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[1] )
            self.assertAlmostEqual( 5.470695e+2, chunk.GN[0] )
            self.assertAlmostEqual( 1.072946e+5, chunk.GN[1] )
            self.assertAlmostEqual( 5.470695e+2, chunk.neutron_widths[0] )
            self.assertAlmostEqual( 1.072946e+5, chunk.neutron_widths[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.GG[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.GG[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.gamma_widths[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.gamma_widths[1] )
            self.assertAlmostEqual( 1.750000e+2, chunk.GFA[0] )
            self.assertAlmostEqual( 0.56, chunk.GFA[1] )
            self.assertAlmostEqual( 1.750000e+2, chunk.first_fission_widths[0] )
            self.assertAlmostEqual( 0.56, chunk.first_fission_widths[1] )
            self.assertAlmostEqual( 3., chunk.GFB[0] )
            self.assertAlmostEqual( 4., chunk.GFB[1] )
            self.assertAlmostEqual( 3., chunk.second_fission_widths[0] )
            self.assertAlmostEqual( 4., chunk.second_fission_widths[1] )

            self.assertEqual( 8, chunk.NPARB )
            self.assertEqual( 8, chunk.covariance_matrix_order )
            self.assertEqual( 36, len( chunk.covariance_matrix ) )
            self.assertEqual( 36, chunk.NVS )
            self.assertEqual( 36, chunk.number_values )

            self.assertAlmostEqual(  5., chunk.covariance_matrix[ 0] )
            self.assertAlmostEqual(  6., chunk.covariance_matrix[ 1] )
            self.assertAlmostEqual(  7., chunk.covariance_matrix[ 2] )
            self.assertAlmostEqual(  8., chunk.covariance_matrix[ 3] )
            self.assertAlmostEqual(  9., chunk.covariance_matrix[ 4] )
            self.assertAlmostEqual( 10., chunk.covariance_matrix[ 5] )
            self.assertAlmostEqual( 11., chunk.covariance_matrix[ 6] )
            self.assertAlmostEqual( 12., chunk.covariance_matrix[ 7] )
            self.assertAlmostEqual( 13., chunk.covariance_matrix[ 8] )
            self.assertAlmostEqual( 14., chunk.covariance_matrix[ 9] )
            self.assertAlmostEqual( 15., chunk.covariance_matrix[10] )
            self.assertAlmostEqual( 16., chunk.covariance_matrix[11] )
            self.assertAlmostEqual( 17., chunk.covariance_matrix[12] )
            self.assertAlmostEqual( 18., chunk.covariance_matrix[13] )
            self.assertAlmostEqual( 19., chunk.covariance_matrix[14] )
            self.assertAlmostEqual( 20., chunk.covariance_matrix[15] )
            self.assertAlmostEqual( 21., chunk.covariance_matrix[16] )
            self.assertAlmostEqual( 22., chunk.covariance_matrix[17] )
            self.assertAlmostEqual( 23., chunk.covariance_matrix[18] )
            self.assertAlmostEqual( 24., chunk.covariance_matrix[19] )
            self.assertAlmostEqual( 25., chunk.covariance_matrix[20] )
            self.assertAlmostEqual( 26., chunk.covariance_matrix[21] )
            self.assertAlmostEqual( 27., chunk.covariance_matrix[22] )
            self.assertAlmostEqual( 28., chunk.covariance_matrix[23] )
            self.assertAlmostEqual( 29., chunk.covariance_matrix[24] )
            self.assertAlmostEqual( 30., chunk.covariance_matrix[25] )
            self.assertAlmostEqual( 31., chunk.covariance_matrix[26] )
            self.assertAlmostEqual( 32., chunk.covariance_matrix[27] )
            self.assertAlmostEqual( 33., chunk.covariance_matrix[28] )
            self.assertAlmostEqual( 34., chunk.covariance_matrix[29] )
            self.assertAlmostEqual( 35., chunk.covariance_matrix[30] )
            self.assertAlmostEqual( 36., chunk.covariance_matrix[31] )
            self.assertAlmostEqual( 37., chunk.covariance_matrix[32] )
            self.assertAlmostEqual( 38., chunk.covariance_matrix[33] )
            self.assertAlmostEqual( 39., chunk.covariance_matrix[34] )
            self.assertAlmostEqual( 40., chunk.covariance_matrix[35] )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 32, 151 ) )

        # the data is given explicitly
        chunk = ShortRangeReichMooreBlock( mpar = 4,
                                           energies = [ -1.470000e+5, 4.730000e+5 ],
                                           spins = [ 0.5, 0.5 ],
                                           gn = [ 5.470695e+2, 1.072946e+5 ],
                                           gg = [ 3.680695e+2, 1.072900e+5 ],
                                           gfa = [ 1.750000e+2, 5.600000e-1 ],
                                           gfb = [ 3., 4. ],
                                           values = [ 5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                                                          13., 14., 15., 16., 17., 18., 19.,
                                                               20., 21., 22., 23., 24., 25.,
                                                                    26., 27., 28., 29., 30.,
                                                                         31., 32., 33., 34.,
                                                                              35., 36., 37.,
                                                                                   38., 39.,
                                                                                        40. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ShortRangeReichMooreBlock.from_string( self.chunk, 1025, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ShortRangeReichMooreBlock( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = ShortRangeReichMooreBlock(
                        mpar = 4,
                        energies = [ -1.470000e+5 ],
                        spins = [ 0.5, 0.5 ],
                        gt = [ 5.470695e+2, 1.072946e+5 ],
                        gn = [ 3.680695e+2, 1.072900e+5 ],
                        gg = [ 1.750000e+2, 5.600000e-1 ],
                        gf = [ 3., 4. ],
                        values = [ 5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                                       13., 14., 15., 16., 17., 18., 19.,
                                            20., 21., 22., 23., 24., 25.,
                                                 26., 27., 28., 29., 30.,
                                                      31., 32., 33., 34.,
                                                           35., 36., 37.,
                                                                38., 39.,
                                                                     40. ] )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = ShortRangeReichMooreBlock(
                        mpar = 4,
                        energies = [], spins = [], gt = [],
                        gn = [], gg = [], gf = [],
                        de2 = [], dn2 = [], dndg = [],
                        dg2 = [], dndf = [], dgdf = [],
                        df2 = [], djdn = [], djdg = [],
                        djdf = [], dj2 = [] )

        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = ShortRangeReichMooreBlock.from_string( self.invalid_size,
                                                                1025, 32, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = ShortRangeReichMooreBlock.from_string( self.zero_size,
                                                           1025, 32, 151 )

        # no number resonances
        with self.assertRaises( Exception ) :

            chunk = ShortRangeReichMooreBlock.from_string( self.no_number_resonances,
                                                           1025, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
