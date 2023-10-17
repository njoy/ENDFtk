# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import GeneralReichMoore
from ENDFtk.MF32.MT151 import ShortRangeReichMooreBlock

class Test_ENDFtk_MF32_MT151_GeneralReichMoore( unittest.TestCase ) :
    """Unit test for the GeneralReichMoore class."""

    chunk = ( ' 1.500000+0 3.365100-1          0          1          1          0102532151     \n'
              ' 1.982069+1 0.000000+0          0          0          1          0102532151     \n'
              ' 0.000000+0 0.000000+0          4          0         48          2102532151     \n'
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
            self.assertEqual( 1, chunk.LRU )
            self.assertEqual( 1, chunk.type )
            self.assertEqual( 3, chunk.LRF )
            self.assertEqual( 3, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )
            self.assertEqual( 1, chunk.LCOMP )
            self.assertEqual( 1, chunk.covariance_representation )

            self.assertAlmostEqual( 1.5, chunk.SPI )
            self.assertAlmostEqual( 1.5, chunk.spin )
            self.assertAlmostEqual( .33651, chunk.AP )
            self.assertAlmostEqual( .33651, chunk.scattering_radius )

            self.assertEqual( None, chunk.DAP )
            self.assertEqual( None, chunk.scattering_radius_uncertainty )
            self.assertEqual( False, chunk.ISR )
            self.assertEqual( False, chunk.scattering_radius_uncertainty_flag )

            self.assertAlmostEqual( 19.82069, chunk.AWRI )
            self.assertAlmostEqual( 19.82069, chunk.atomic_weight_ratio )

            self.assertEqual( 1, chunk.NLS )
            self.assertEqual( 1, chunk.number_l_values )

            self.assertEqual( 1, chunk.NSRS )
            self.assertEqual( 1, chunk.number_short_range_blocks )
            self.assertEqual( 0, chunk.NLRS )
            self.assertEqual( 0, chunk.number_long_range_blocks )
            self.assertEqual( 1, len( chunk.short_range_blocks ) )
            self.assertEqual( 0, len( chunk.long_range_blocks ) )

            block = chunk.short_range_blocks[0]
            self.assertEqual( 4, block.MPAR )
            self.assertEqual( 4, block.number_parameters_with_covariances )

            self.assertEqual( 2, block.NRB )
            self.assertEqual( 2, block.number_resonances )
            self.assertEqual( 2, len( block.ER ) )
            self.assertEqual( 2, len( block.resonance_energies ) )
            self.assertEqual( 2, len( block.AJ ) )
            self.assertEqual( 2, len( block.spin_values ) )
            self.assertEqual( 2, len( block.GN ) )
            self.assertEqual( 2, len( block.neutron_widths ) )
            self.assertEqual( 2, len( block.GG ) )
            self.assertEqual( 2, len( block.gamma_widths ) )
            self.assertEqual( 2, len( block.GFA ) )
            self.assertEqual( 2, len( block.first_fission_widths ) )
            self.assertEqual( 2, len( block.GFB ) )
            self.assertEqual( 2, len( block.second_fission_widths ) )

            self.assertAlmostEqual( -1.470000e+5, block.ER[0] )
            self.assertAlmostEqual(  4.730000e+5, block.ER[1] )
            self.assertAlmostEqual( -1.470000e+5, block.resonance_energies[0] )
            self.assertAlmostEqual(  4.730000e+5, block.resonance_energies[1] )
            self.assertAlmostEqual( 0.5, block.AJ[0] )
            self.assertAlmostEqual( 0.5, block.AJ[1] )
            self.assertAlmostEqual( 0.5, block.spin_values[0] )
            self.assertAlmostEqual( 0.5, block.spin_values[1] )
            self.assertAlmostEqual( 5.470695e+2, block.GN[0] )
            self.assertAlmostEqual( 1.072946e+5, block.GN[1] )
            self.assertAlmostEqual( 5.470695e+2, block.neutron_widths[0] )
            self.assertAlmostEqual( 1.072946e+5, block.neutron_widths[1] )
            self.assertAlmostEqual( 3.680695e+2, block.GG[0] )
            self.assertAlmostEqual( 1.072900e+5, block.GG[1] )
            self.assertAlmostEqual( 3.680695e+2, block.gamma_widths[0] )
            self.assertAlmostEqual( 1.072900e+5, block.gamma_widths[1] )
            self.assertAlmostEqual( 1.750000e+2, block.GFA[0] )
            self.assertAlmostEqual( 0.56, block.GFA[1] )
            self.assertAlmostEqual( 1.750000e+2, block.first_fission_widths[0] )
            self.assertAlmostEqual( 0.56, block.first_fission_widths[1] )
            self.assertAlmostEqual( 3., block.GFB[0] )
            self.assertAlmostEqual( 4., block.GFB[1] )
            self.assertAlmostEqual( 3., block.second_fission_widths[0] )
            self.assertAlmostEqual( 4., block.second_fission_widths[1] )

            self.assertEqual( 8, block.NPARB )
            self.assertEqual( 8, block.covariance_matrix_order )
            self.assertEqual( 36, len( block.covariance_matrix ) )
            self.assertEqual( 36, block.NVS )
            self.assertEqual( 36, block.number_values )

            self.assertAlmostEqual(  5., block.covariance_matrix[ 0] )
            self.assertAlmostEqual(  6., block.covariance_matrix[ 1] )
            self.assertAlmostEqual(  7., block.covariance_matrix[ 2] )
            self.assertAlmostEqual(  8., block.covariance_matrix[ 3] )
            self.assertAlmostEqual(  9., block.covariance_matrix[ 4] )
            self.assertAlmostEqual( 10., block.covariance_matrix[ 5] )
            self.assertAlmostEqual( 11., block.covariance_matrix[ 6] )
            self.assertAlmostEqual( 12., block.covariance_matrix[ 7] )
            self.assertAlmostEqual( 13., block.covariance_matrix[ 8] )
            self.assertAlmostEqual( 14., block.covariance_matrix[ 9] )
            self.assertAlmostEqual( 15., block.covariance_matrix[10] )
            self.assertAlmostEqual( 16., block.covariance_matrix[11] )
            self.assertAlmostEqual( 17., block.covariance_matrix[12] )
            self.assertAlmostEqual( 18., block.covariance_matrix[13] )
            self.assertAlmostEqual( 19., block.covariance_matrix[14] )
            self.assertAlmostEqual( 20., block.covariance_matrix[15] )
            self.assertAlmostEqual( 21., block.covariance_matrix[16] )
            self.assertAlmostEqual( 22., block.covariance_matrix[17] )
            self.assertAlmostEqual( 23., block.covariance_matrix[18] )
            self.assertAlmostEqual( 24., block.covariance_matrix[19] )
            self.assertAlmostEqual( 25., block.covariance_matrix[20] )
            self.assertAlmostEqual( 26., block.covariance_matrix[21] )
            self.assertAlmostEqual( 27., block.covariance_matrix[22] )
            self.assertAlmostEqual( 28., block.covariance_matrix[23] )
            self.assertAlmostEqual( 29., block.covariance_matrix[24] )
            self.assertAlmostEqual( 30., block.covariance_matrix[25] )
            self.assertAlmostEqual( 31., block.covariance_matrix[26] )
            self.assertAlmostEqual( 32., block.covariance_matrix[27] )
            self.assertAlmostEqual( 33., block.covariance_matrix[28] )
            self.assertAlmostEqual( 34., block.covariance_matrix[29] )
            self.assertAlmostEqual( 35., block.covariance_matrix[30] )
            self.assertAlmostEqual( 36., block.covariance_matrix[31] )
            self.assertAlmostEqual( 37., block.covariance_matrix[32] )
            self.assertAlmostEqual( 38., block.covariance_matrix[33] )
            self.assertAlmostEqual( 39., block.covariance_matrix[34] )
            self.assertAlmostEqual( 40., block.covariance_matrix[35] )

            self.assertEqual( 11, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 32, 151 ) )

        # the data is given explicitly
        chunk = GeneralReichMoore(
                    awri = 19.82069,
                    spin = 1.5,
                    ap = .33651,
                    nls = 1,
                    short = [ ShortRangeReichMooreBlock(
                                  mpar = 4,
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
                                                                               40. ] ) ],
                    long = [] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = GeneralReichMoore.from_string( self.chunk, 1025, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = GeneralReichMoore( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
