# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import ShortRangeRMatrixLimitedBlock
from ENDFtk.MF32.MT151 import ResonanceParameters
from ENDFtk.MF32.MT151 import CovarianceMatrix

class Test_ENDFtk_MF32_MT151_ShortRangeRMatrixLimitedBlock( unittest.TestCase ) :
    """Unit test for the ShortRangeRMatrixLimitedBlock class."""

    chunk = ( ' 0.000000+0 0.000000+0          2          0          0          0102532151     \n'
              ' 0.000000+0 0.000000+0          2          2         12          2102532151     \n'
              '-4.586687+5 1.000091+0 9.809761+2 0.000000+0 0.000000+0 0.000000+0102532151     \n'
              ' 1.913996+6 1.000000+0 1.878975+5 0.000000+0 0.000000+0 0.000000+0102532151     \n'
              ' 0.000000+0 0.000000+0          1          3         18          3102532151     \n'
              ' 2.880782+3 3.499989-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0102532151     \n'
              ' 6.957171+3 3.500785-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0102532151     \n'
              ' 1.003819+5 1.382810+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102532151     \n'
              ' 0.000000+0 0.000000+0          0          0         78         12102532151     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0102532151     \n'
              ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1102532151     \n'
              ' 1.300000+1 1.400000+1 1.500000+1 1.600000+1 1.700000+1 1.800000+1102532151     \n'
              ' 1.900000+1 2.000000+1 2.100000+1 2.200000+1 2.300000+1 2.400000+1102532151     \n'
              ' 2.500000+1 2.600000+1 2.700000+1 2.800000+1 2.900000+1 3.000000+1102532151     \n'
              ' 3.100000+1 3.200000+1 3.300000+1 3.400000+1 3.500000+1 3.600000+1102532151     \n'
              ' 3.700000+1 3.800000+1 3.900000+1 4.000000+1 4.100000+1 4.200000+1102532151     \n'
              ' 4.300000+1 4.400000+1 4.500000+1 4.600000+1 4.700000+1 4.800000+1102532151     \n'
              ' 4.900000+1 5.000000+1 5.100000+1 5.200000+1 5.300000+1 5.400000+1102532151     \n'
              ' 5.500000+1 5.600000+1 5.700000+1 5.800000+1 5.900000+1 6.000000+1102532151     \n'
              ' 6.100000+1 6.200000+1 6.300000+1 6.400000+1 6.500000+1 6.600000+1102532151     \n'
              ' 6.700000+1 6.800000+1 6.900000+1 7.000000+1 7.100000+1 7.200000+1102532151     \n'
              ' 7.300000+1 7.400000+1 7.500000+1 7.600000+1 7.700000+1 7.800000+1102532151     \n' )

    # invalid_size = ( ' 1.982069+1 0.000000+0          4          0         47          2102532151     \n'
    #                  '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
    #                  ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
    #                  ' 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n'
    #                  ' 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n'
    #                  ' 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n'
    #                  ' 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n'
    #                  ' 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n'
    #                  ' 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1           102532151     \n' )

    # zero_size = ( ' 1.982069+1 0.000000+0          0          0          0          2102532151     \n' )

    # no_number_resonances = ( ' 1.982069+1 0.000000+0          4          0         48          0102532151     \n'
    #                          '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
    #                          ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
    #                          ' 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n'
    #                          ' 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n'
    #                          ' 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n'
    #                          ' 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n'
    #                          ' 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n'
    #                          ' 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.NJSX )
            self.assertEqual( 2, chunk.number_spin_groups )
            self.assertEqual( 2, len( chunk.resonance_parameters ) )

            parameters1 = chunk.resonance_parameters[0]
            self.assertEqual( 2, parameters1.NCH )
            self.assertEqual( 2, parameters1.number_channels )
            self.assertEqual( 2, parameters1.NRB )
            self.assertEqual( 2, parameters1.number_resonances )
            self.assertEqual( 2, parameters1.NX )
            self.assertEqual( 2, parameters1.number_lines )

            self.assertEqual( 2, len( parameters1.ER ) )
            self.assertEqual( 2, len( parameters1.resonance_energies ) )
            self.assertEqual( 2, len( parameters1.GAM ) )
            self.assertEqual( 2, len( parameters1.resonance_parameters ) )

            self.assertAlmostEqual( -4.586687e+5, parameters1.ER[0] )
            self.assertAlmostEqual(  1.913996e+6, parameters1.ER[1] )
            self.assertAlmostEqual( -4.586687e+5, parameters1.resonance_energies[0] )
            self.assertAlmostEqual(  1.913996e+6, parameters1.resonance_energies[1] )
            self.assertEqual( 2, len( parameters1.GAM[0] ) )
            self.assertEqual( 2, len( parameters1.GAM[1] ) )
            self.assertAlmostEqual( 1.000091, parameters1.GAM[0][0] )
            self.assertAlmostEqual( 9.809761e+2, parameters1.GAM[0][1] )
            self.assertAlmostEqual( 1., parameters1.GAM[1][0] )
            self.assertAlmostEqual( 1.878975e+5, parameters1.GAM[1][1] )
            self.assertEqual( 2, len( parameters1.resonance_parameters[0] ) )
            self.assertEqual( 2, len( parameters1.resonance_parameters[1] ) )
            self.assertAlmostEqual( 1.000091, parameters1.resonance_parameters[0][0] )
            self.assertAlmostEqual( 9.809761e+2, parameters1.resonance_parameters[0][1] )
            self.assertAlmostEqual( 1., parameters1.resonance_parameters[1][0] )
            self.assertAlmostEqual( 1.878975e+5, parameters1.resonance_parameters[1][1] )

            parameters2 = chunk.resonance_parameters[1]
            self.assertEqual( 1, parameters2.NCH )
            self.assertEqual( 1, parameters2.number_channels )
            self.assertEqual( 3, parameters2.NRB )
            self.assertEqual( 3, parameters2.number_resonances )
            self.assertEqual( 3, parameters2.NX )
            self.assertEqual( 3, parameters2.number_lines )

            self.assertEqual( 3, len( parameters2.ER ) )
            self.assertEqual( 3, len( parameters2.resonance_energies ) )
            self.assertEqual( 3, len( parameters2.GAM ) )
            self.assertEqual( 3, len( parameters2.resonance_parameters ) )

            self.assertAlmostEqual( 2.880782e+3, parameters2.ER[0] )
            self.assertAlmostEqual( 6.957171e+3, parameters2.ER[1] )
            self.assertAlmostEqual( 1.003819e+5, parameters2.ER[2] )
            self.assertAlmostEqual( 2.880782e+3, parameters2.resonance_energies[0] )
            self.assertAlmostEqual( 6.957171e+3, parameters2.resonance_energies[1] )
            self.assertAlmostEqual( 1.003819e+5, parameters2.resonance_energies[2] )
            self.assertEqual( 1, len( parameters2.GAM[0] ) )
            self.assertEqual( 1, len( parameters2.GAM[1] ) )
            self.assertEqual( 1, len( parameters2.GAM[2] ) )
            self.assertAlmostEqual( .3499989, parameters2.GAM[0][0] )
            self.assertAlmostEqual( .3500785, parameters2.GAM[1][0] )
            self.assertAlmostEqual( 1.382810, parameters2.GAM[2][0] )
            self.assertEqual( 1, len( parameters2.resonance_parameters[0] ) )
            self.assertEqual( 1, len( parameters2.resonance_parameters[1] ) )
            self.assertEqual( 1, len( parameters2.resonance_parameters[2] ) )
            self.assertAlmostEqual( .3499989, parameters2.resonance_parameters[0][0] )
            self.assertAlmostEqual( .3500785, parameters2.resonance_parameters[1][0] )
            self.assertAlmostEqual( 1.382810, parameters2.resonance_parameters[2][0] )

            matrix = chunk.covariance_matrix
            self.assertEqual( 12, matrix.NPARB )
            self.assertEqual( 12, matrix.covariance_matrix_order )

            self.assertEqual( 78, len( matrix.covariance_matrix ) )
            self.assertEqual( 78, matrix.NVS )
            self.assertEqual( 78, matrix.number_values )

            self.assertAlmostEqual(  1., matrix.covariance_matrix[ 0] )
            self.assertAlmostEqual(  2., matrix.covariance_matrix[ 1] )
            self.assertAlmostEqual(  3., matrix.covariance_matrix[ 2] )
            self.assertAlmostEqual(  4., matrix.covariance_matrix[ 3] )
            self.assertAlmostEqual(  5., matrix.covariance_matrix[ 4] )
            self.assertAlmostEqual(  6., matrix.covariance_matrix[ 5] )
            self.assertAlmostEqual(  7., matrix.covariance_matrix[ 6] )
            self.assertAlmostEqual(  8., matrix.covariance_matrix[ 7] )
            self.assertAlmostEqual(  9., matrix.covariance_matrix[ 8] )
            self.assertAlmostEqual( 10., matrix.covariance_matrix[ 9] )
            self.assertAlmostEqual( 11., matrix.covariance_matrix[10] )
            self.assertAlmostEqual( 12., matrix.covariance_matrix[11] )
            self.assertAlmostEqual( 13., matrix.covariance_matrix[12] )
            self.assertAlmostEqual( 14., matrix.covariance_matrix[13] )
            self.assertAlmostEqual( 15., matrix.covariance_matrix[14] )
            self.assertAlmostEqual( 16., matrix.covariance_matrix[15] )
            self.assertAlmostEqual( 17., matrix.covariance_matrix[16] )
            self.assertAlmostEqual( 18., matrix.covariance_matrix[17] )
            self.assertAlmostEqual( 19., matrix.covariance_matrix[18] )
            self.assertAlmostEqual( 20., matrix.covariance_matrix[19] )
            self.assertAlmostEqual( 21., matrix.covariance_matrix[20] )
            self.assertAlmostEqual( 22., matrix.covariance_matrix[21] )
            self.assertAlmostEqual( 23., matrix.covariance_matrix[22] )
            self.assertAlmostEqual( 24., matrix.covariance_matrix[23] )
            self.assertAlmostEqual( 25., matrix.covariance_matrix[24] )
            self.assertAlmostEqual( 26., matrix.covariance_matrix[25] )
            self.assertAlmostEqual( 27., matrix.covariance_matrix[26] )
            self.assertAlmostEqual( 28., matrix.covariance_matrix[27] )
            self.assertAlmostEqual( 29., matrix.covariance_matrix[28] )
            self.assertAlmostEqual( 30., matrix.covariance_matrix[29] )
            self.assertAlmostEqual( 31., matrix.covariance_matrix[30] )
            self.assertAlmostEqual( 32., matrix.covariance_matrix[31] )
            self.assertAlmostEqual( 33., matrix.covariance_matrix[32] )
            self.assertAlmostEqual( 34., matrix.covariance_matrix[33] )
            self.assertAlmostEqual( 35., matrix.covariance_matrix[34] )
            self.assertAlmostEqual( 36., matrix.covariance_matrix[35] )
            self.assertAlmostEqual( 37., matrix.covariance_matrix[36] )
            self.assertAlmostEqual( 38., matrix.covariance_matrix[37] )
            self.assertAlmostEqual( 39., matrix.covariance_matrix[38] )
            self.assertAlmostEqual( 40., matrix.covariance_matrix[39] )
            self.assertAlmostEqual( 41., matrix.covariance_matrix[40] )
            self.assertAlmostEqual( 42., matrix.covariance_matrix[41] )
            self.assertAlmostEqual( 43., matrix.covariance_matrix[42] )
            self.assertAlmostEqual( 44., matrix.covariance_matrix[43] )
            self.assertAlmostEqual( 45., matrix.covariance_matrix[44] )
            self.assertAlmostEqual( 46., matrix.covariance_matrix[45] )
            self.assertAlmostEqual( 47., matrix.covariance_matrix[46] )
            self.assertAlmostEqual( 48., matrix.covariance_matrix[47] )
            self.assertAlmostEqual( 49., matrix.covariance_matrix[48] )
            self.assertAlmostEqual( 50., matrix.covariance_matrix[49] )
            self.assertAlmostEqual( 51., matrix.covariance_matrix[50] )
            self.assertAlmostEqual( 52., matrix.covariance_matrix[51] )
            self.assertAlmostEqual( 53., matrix.covariance_matrix[52] )
            self.assertAlmostEqual( 54., matrix.covariance_matrix[53] )
            self.assertAlmostEqual( 55., matrix.covariance_matrix[54] )
            self.assertAlmostEqual( 56., matrix.covariance_matrix[55] )
            self.assertAlmostEqual( 57., matrix.covariance_matrix[56] )
            self.assertAlmostEqual( 58., matrix.covariance_matrix[57] )
            self.assertAlmostEqual( 59., matrix.covariance_matrix[58] )
            self.assertAlmostEqual( 60., matrix.covariance_matrix[59] )
            self.assertAlmostEqual( 61., matrix.covariance_matrix[60] )
            self.assertAlmostEqual( 62., matrix.covariance_matrix[61] )
            self.assertAlmostEqual( 63., matrix.covariance_matrix[62] )
            self.assertAlmostEqual( 64., matrix.covariance_matrix[63] )
            self.assertAlmostEqual( 65., matrix.covariance_matrix[64] )
            self.assertAlmostEqual( 66., matrix.covariance_matrix[65] )
            self.assertAlmostEqual( 67., matrix.covariance_matrix[66] )
            self.assertAlmostEqual( 68., matrix.covariance_matrix[67] )
            self.assertAlmostEqual( 69., matrix.covariance_matrix[68] )
            self.assertAlmostEqual( 70., matrix.covariance_matrix[69] )
            self.assertAlmostEqual( 71., matrix.covariance_matrix[70] )
            self.assertAlmostEqual( 72., matrix.covariance_matrix[71] )
            self.assertAlmostEqual( 73., matrix.covariance_matrix[72] )
            self.assertAlmostEqual( 74., matrix.covariance_matrix[73] )
            self.assertAlmostEqual( 75., matrix.covariance_matrix[74] )
            self.assertAlmostEqual( 76., matrix.covariance_matrix[75] )
            self.assertAlmostEqual( 77., matrix.covariance_matrix[76] )
            self.assertAlmostEqual( 78., matrix.covariance_matrix[77] )

            self.assertEqual( 22, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 32, 151 ) )

        # the data is given explicitly
        chunk = ShortRangeRMatrixLimitedBlock(

                    parameters = [

                      ResonanceParameters( [ -4.586687e+5, 1.913996e+6 ],
                                           [ [ 1.000091, 9.809761e+2 ],
                                             [ 1., 1.878975e+5 ] ] ),
                      ResonanceParameters( [ 2.880782e+3, 6.957171e+3, 1.003819e+5 ],
                                           [ [ 3.499989e-1 ], [ 3.500785e-1 ], [ 1.382810e+0 ] ] )
                    ],
                    covariances =  CovarianceMatrix(
                                     [  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                                            13., 14., 15., 16., 17., 18., 19., 20., 21., 22., 23.,
                                                 24., 25., 26., 27., 28., 29., 30., 31., 32., 33.,
                                                      34., 35., 36., 37., 38., 39., 40., 41., 42.,
                                                           43., 44., 45., 46., 47., 48., 49., 50.,
                                                                51., 52., 53., 54., 55., 56., 57.,
                                                                     58., 59., 60., 61., 62., 63.,
                                                                          64., 65., 66., 67., 68.,
                                                                               69., 70., 71., 72.,
                                                                                    73., 74., 75.,
                                                                                         76., 77.,
                                                                                              78. ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ShortRangeRMatrixLimitedBlock.from_string( self.chunk, 1025, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ShortRangeRMatrixLimitedBlock( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
