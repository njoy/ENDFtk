# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT458 import Section
from ENDFtk.MF1.MT458 import ThermalPointComponents
from ENDFtk.MF1.MT458 import PolynomialComponents
from ENDFtk.MF1.MT458 import TabulatedComponents
from ENDFtk.MF1.MT458 import EnergyReleaseComponent
from ENDFtk.tree import Tape

class Test_ENDFtk_MF1_MT458_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_thermal = ( ' 9.223500+4 2.330248+2          0          0          0          09228 1458     \n'
                      ' 0.000000+0 0.000000+0          0          0         18          99228 1458     \n'
                      ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
                      ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n'
                      ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n' )

    chunk_polynomial = ( ' 9.223500+4 2.330248+2          0          0          0          09228 1458     \n'
                         ' 0.000000+0 0.000000+0          0          1         36         189228 1458     \n'
                         ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
                         ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n'
                         ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n'
                         '-2.660000-1 2.660000-2 3.004000-1 3.004000-2 0.000000+0 0.000000+09228 1458     \n'
                         ' 7.770000-2 7.770000-3-7.500000-2 7.600000-3-7.700000-2 7.800000-39228 1458     \n'
                         '-1.000000-1 1.000000-2-3.790000-2 3.790000-3-1.379000-1 1.379000-29228 1458     \n' )

    chunk_tabulated = ( ' 9.223500+4 2.330248+2          0          1          0          29228 1458     \n'
                        ' 0.000000+0 0.000000+0          0          0         18          99228 1458     \n'
                        ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
                        ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n'
                        ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n'
                        ' 0.000000+0 0.000000+0          1          1          1          39228 1458     \n'
                        '          3          2                                            9228 1458     \n'
                        ' 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n'
                        ' 0.000000+0 0.000000+0          2          9          1          49228 1458     \n'
                        '          4          2                                            9228 1458     \n'
                        ' 1.000000-5 2.021554+8 2.530000-2 3.000000+8 1.000000+6 2.500000+89228 1458     \n'
                        ' 2.000000+7 1.500000+8                                            9228 1458     \n' )

    invalid_lfc = ( ' 9.223500+4 2.330248+2          0          3          0          09228 1458     \n'
                    ' 0.000000+0 0.000000+0          0          0         18          99228 1458     \n'
                    ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
                    ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n'
                    ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n' )

    invalid_nfc = ( ' 9.223500+4 2.330248+2          0          1          0         -19228 1458     \n'
                    ' 0.000000+0 0.000000+0          0          0         18          99228 1458     \n'
                    ' 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n'
                    ' 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n'
                    ' 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 1  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 1  1     \n'

    def test_section( self ) :

        def verify_chunk_thermal( self, chunk ) :

            # verify content
            self.assertEqual( 458, chunk.MT )
            self.assertEqual( 458, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )

            self.assertEqual( False, chunk.LFC )
            self.assertEqual( False, chunk.tabulated_energy_release )
            self.assertEqual( 0, chunk.NPLY )
            self.assertEqual( 0, chunk.order )
            self.assertEqual( 0, chunk.NFC )
            self.assertEqual( 0, chunk.number_tabulated_components )

            data = chunk.energy_release

            self.assertEqual( False, data.LFC )
            self.assertEqual( False, data.tabulated_energy_release )
            self.assertEqual( 0, data.NPLY )
            self.assertEqual( 0, data.order )
            self.assertEqual( 0, data.NFC )
            self.assertEqual( 0, data.number_tabulated_components )

            self.assertAlmostEqual( 1.691300e+8, data.E[0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.E[1][0] )
            self.assertAlmostEqual( 7.400000e+3, data.E[2][0] )
            self.assertAlmostEqual( 6.600000e+6, data.E[3][0] )
            self.assertAlmostEqual( 6.330000e+6, data.E[4][0] )
            self.assertAlmostEqual( 6.500000e+6, data.E[5][0] )
            self.assertAlmostEqual( 8.750000e+6, data.E[6][0] )
            self.assertAlmostEqual( 1.934054e+8, data.E[7][0] )
            self.assertAlmostEqual( 2.021554e+8, data.E[8][0] )

            self.assertAlmostEqual( 4.900000e+5, data.E[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.E[1][1] )
            self.assertAlmostEqual( 1.110000e+3, data.E[2][1] )
            self.assertAlmostEqual( 5.000000e+5, data.E[3][1] )
            self.assertAlmostEqual( 5.000000e+4, data.E[4][1] )
            self.assertAlmostEqual( 5.100000e+4, data.E[5][1] )
            self.assertAlmostEqual( 7.000000e+4, data.E[6][1] )
            self.assertAlmostEqual( 1.500000e+5, data.E[7][1] )
            self.assertAlmostEqual( 1.300000e+5, data.E[8][1] )

            self.assertAlmostEqual( 1.691300e+8, data.energy_release[0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.energy_release[1][0] )
            self.assertAlmostEqual( 7.400000e+3, data.energy_release[2][0] )
            self.assertAlmostEqual( 6.600000e+6, data.energy_release[3][0] )
            self.assertAlmostEqual( 6.330000e+6, data.energy_release[4][0] )
            self.assertAlmostEqual( 6.500000e+6, data.energy_release[5][0] )
            self.assertAlmostEqual( 8.750000e+6, data.energy_release[6][0] )
            self.assertAlmostEqual( 1.934054e+8, data.energy_release[7][0] )
            self.assertAlmostEqual( 2.021554e+8, data.energy_release[8][0] )

            self.assertAlmostEqual( 4.900000e+5, data.energy_release[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.energy_release[1][1] )
            self.assertAlmostEqual( 1.110000e+3, data.energy_release[2][1] )
            self.assertAlmostEqual( 5.000000e+5, data.energy_release[3][1] )
            self.assertAlmostEqual( 5.000000e+4, data.energy_release[4][1] )
            self.assertAlmostEqual( 5.100000e+4, data.energy_release[5][1] )
            self.assertAlmostEqual( 7.000000e+4, data.energy_release[6][1] )
            self.assertAlmostEqual( 1.500000e+5, data.energy_release[7][1] )
            self.assertAlmostEqual( 1.300000e+5, data.energy_release[8][1] )

            self.assertAlmostEqual( 1.691300e+8, data.EFR[0] )
            self.assertAlmostEqual( 4.838000e+6, data.ENP[0] )
            self.assertAlmostEqual( 7.400000e+3, data.END[0] )
            self.assertAlmostEqual( 6.600000e+6, data.EGP[0] )
            self.assertAlmostEqual( 6.330000e+6, data.EGD[0] )
            self.assertAlmostEqual( 6.500000e+6, data.EB[0] )
            self.assertAlmostEqual( 8.750000e+6, data.ENU[0] )
            self.assertAlmostEqual( 1.934054e+8, data.ER[0] )
            self.assertAlmostEqual( 2.021554e+8, data.ET[0] )

            self.assertAlmostEqual( 4.900000e+5, data.EFR[1] )
            self.assertAlmostEqual( 7.000000e+4, data.ENP[1] )
            self.assertAlmostEqual( 1.110000e+3, data.END[1] )
            self.assertAlmostEqual( 5.000000e+5, data.EGP[1] )
            self.assertAlmostEqual( 5.000000e+4, data.EGD[1] )
            self.assertAlmostEqual( 5.100000e+4, data.EB[1] )
            self.assertAlmostEqual( 7.000000e+4, data.ENU[1] )
            self.assertAlmostEqual( 1.500000e+5, data.ER[1] )
            self.assertAlmostEqual( 1.300000e+5, data.ET[1] )

            self.assertAlmostEqual( 1.691300e+8, data.fission_fragments[0] )
            self.assertAlmostEqual( 4.838000e+6, data.prompt_neutrons[0] )
            self.assertAlmostEqual( 7.400000e+3, data.delayed_neutrons[0] )
            self.assertAlmostEqual( 6.600000e+6, data.prompt_gammas[0] )
            self.assertAlmostEqual( 6.330000e+6, data.delayed_gammas[0] )
            self.assertAlmostEqual( 6.500000e+6, data.delayed_betas[0] )
            self.assertAlmostEqual( 8.750000e+6, data.neutrinos[0] )
            self.assertAlmostEqual( 1.934054e+8, data.total_minus_neutrinos[0] )
            self.assertAlmostEqual( 2.021554e+8, data.total[0] )

            self.assertAlmostEqual( 4.900000e+5, data.fission_fragments[1] )
            self.assertAlmostEqual( 7.000000e+4, data.prompt_neutrons[1] )
            self.assertAlmostEqual( 1.110000e+3, data.delayed_neutrons[1] )
            self.assertAlmostEqual( 5.000000e+5, data.prompt_gammas[1] )
            self.assertAlmostEqual( 5.000000e+4, data.delayed_gammas[1] )
            self.assertAlmostEqual( 5.100000e+4, data.delayed_betas[1] )
            self.assertAlmostEqual( 7.000000e+4, data.neutrinos[1] )
            self.assertAlmostEqual( 1.500000e+5, data.total_minus_neutrinos[1] )
            self.assertAlmostEqual( 1.300000e+5, data.total[1] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_thermal + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        def verify_chunk_polynomial( self, chunk ) :

            # verify content
            self.assertEqual( 458, chunk.MT )
            self.assertEqual( 458, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )

            self.assertEqual( False, chunk.LFC )
            self.assertEqual( False, chunk.tabulated_energy_release )
            self.assertEqual( 1, chunk.NPLY )
            self.assertEqual( 1, chunk.order )
            self.assertEqual( 0, chunk.NFC )
            self.assertEqual( 0, chunk.number_tabulated_components )

            data = chunk.energy_release

            self.assertEqual( False, data.LFC )
            self.assertEqual( False, data.tabulated_energy_release )
            self.assertEqual( 1, data.NPLY )
            self.assertEqual( 1, data.order )
            self.assertEqual( 0, data.NFC )
            self.assertEqual( 0, data.number_tabulated_components )

            self.assertAlmostEqual( 1.691300e+8, data.E[0][0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.E[1][0][0] )
            self.assertAlmostEqual( 7.400000e+3, data.E[2][0][0] )
            self.assertAlmostEqual( 6.600000e+6, data.E[3][0][0] )
            self.assertAlmostEqual( 6.330000e+6, data.E[4][0][0] )
            self.assertAlmostEqual( 6.500000e+6, data.E[5][0][0] )
            self.assertAlmostEqual( 8.750000e+6, data.E[6][0][0] )
            self.assertAlmostEqual( 1.934054e+8, data.E[7][0][0] )
            self.assertAlmostEqual( 2.021554e+8, data.E[8][0][0] )

            self.assertAlmostEqual( 4.900000e+5, data.E[0][0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.E[1][0][1] )
            self.assertAlmostEqual( 1.110000e+3, data.E[2][0][1] )
            self.assertAlmostEqual( 5.000000e+5, data.E[3][0][1] )
            self.assertAlmostEqual( 5.000000e+4, data.E[4][0][1] )
            self.assertAlmostEqual( 5.100000e+4, data.E[5][0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.E[6][0][1] )
            self.assertAlmostEqual( 1.500000e+5, data.E[7][0][1] )
            self.assertAlmostEqual( 1.300000e+5, data.E[8][0][1] )

            self.assertAlmostEqual( 1.691300e+8, data.energy_release[0][0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.energy_release[1][0][0] )
            self.assertAlmostEqual( 7.400000e+3, data.energy_release[2][0][0] )
            self.assertAlmostEqual( 6.600000e+6, data.energy_release[3][0][0] )
            self.assertAlmostEqual( 6.330000e+6, data.energy_release[4][0][0] )
            self.assertAlmostEqual( 6.500000e+6, data.energy_release[5][0][0] )
            self.assertAlmostEqual( 8.750000e+6, data.energy_release[6][0][0] )
            self.assertAlmostEqual( 1.934054e+8, data.energy_release[7][0][0] )
            self.assertAlmostEqual( 2.021554e+8, data.energy_release[8][0][0] )

            self.assertAlmostEqual( 4.900000e+5, data.energy_release[0][0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.energy_release[1][0][1] )
            self.assertAlmostEqual( 1.110000e+3, data.energy_release[2][0][1] )
            self.assertAlmostEqual( 5.000000e+5, data.energy_release[3][0][1] )
            self.assertAlmostEqual( 5.000000e+4, data.energy_release[4][0][1] )
            self.assertAlmostEqual( 5.100000e+4, data.energy_release[5][0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.energy_release[6][0][1] )
            self.assertAlmostEqual( 1.500000e+5, data.energy_release[7][0][1] )
            self.assertAlmostEqual( 1.300000e+5, data.energy_release[8][0][1] )

            self.assertAlmostEqual( -2.660000e-1, data.E[0][1][0] )
            self.assertAlmostEqual( 3.004000e-1,  data.E[1][1][0] )
            self.assertAlmostEqual( 0.0, data.E[2][1][0] )
            self.assertAlmostEqual( 7.770000e-2,  data.E[3][1][0] )
            self.assertAlmostEqual( -7.500000e-2, data.E[4][1][0] )
            self.assertAlmostEqual( -7.700000e-2, data.E[5][1][0] )
            self.assertAlmostEqual( -1.000000e-1, data.E[6][1][0] )
            self.assertAlmostEqual( -3.790000e-2, data.E[7][1][0] )
            self.assertAlmostEqual( -1.379000e-1, data.E[8][1][0] )

            self.assertAlmostEqual( 2.660000e-2, data.E[0][1][1] )
            self.assertAlmostEqual( 3.004000e-2, data.E[1][1][1] )
            self.assertAlmostEqual( 0.0, data.E[2][1][1] )
            self.assertAlmostEqual( 7.770000e-3, data.E[3][1][1] )
            self.assertAlmostEqual( 7.600000e-3, data.E[4][1][1] )
            self.assertAlmostEqual( 7.800000e-3, data.E[5][1][1] )
            self.assertAlmostEqual( 1.000000e-2, data.E[6][1][1] )
            self.assertAlmostEqual( 3.790000e-3, data.E[7][1][1] )
            self.assertAlmostEqual( 1.379000e-2, data.E[8][1][1] )

            self.assertAlmostEqual( -2.660000e-1, data.energy_release[0][1][0] )
            self.assertAlmostEqual( 3.004000e-1,  data.energy_release[1][1][0] )
            self.assertAlmostEqual( 0.0, data.energy_release[2][1][0] )
            self.assertAlmostEqual( 7.770000e-2,  data.energy_release[3][1][0] )
            self.assertAlmostEqual( -7.500000e-2, data.energy_release[4][1][0] )
            self.assertAlmostEqual( -7.700000e-2, data.energy_release[5][1][0] )
            self.assertAlmostEqual( -1.000000e-1, data.energy_release[6][1][0] )
            self.assertAlmostEqual( -3.790000e-2, data.energy_release[7][1][0] )
            self.assertAlmostEqual( -1.379000e-1, data.energy_release[8][1][0] )

            self.assertAlmostEqual( 2.660000e-2, data.energy_release[0][1][1] )
            self.assertAlmostEqual( 3.004000e-2, data.energy_release[1][1][1] )
            self.assertAlmostEqual( 0.0, data.energy_release[2][1][1] )
            self.assertAlmostEqual( 7.770000e-3, data.energy_release[3][1][1] )
            self.assertAlmostEqual( 7.600000e-3, data.energy_release[4][1][1] )
            self.assertAlmostEqual( 7.800000e-3, data.energy_release[5][1][1] )
            self.assertAlmostEqual( 1.000000e-2, data.energy_release[6][1][1] )
            self.assertAlmostEqual( 3.790000e-3, data.energy_release[7][1][1] )
            self.assertAlmostEqual( 1.379000e-2, data.energy_release[8][1][1] )

            self.assertAlmostEqual( 1.691300e+8, data.EFR[0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.ENP[0][0] )
            self.assertAlmostEqual( 7.400000e+3, data.END[0][0] )
            self.assertAlmostEqual( 6.600000e+6, data.EGP[0][0] )
            self.assertAlmostEqual( 6.330000e+6, data.EGD[0][0] )
            self.assertAlmostEqual( 6.500000e+6, data.EB[0][0] )
            self.assertAlmostEqual( 8.750000e+6, data.ENU[0][0] )
            self.assertAlmostEqual( 1.934054e+8, data.ER[0][0] )
            self.assertAlmostEqual( 2.021554e+8, data.ET[0][0] )

            self.assertAlmostEqual( 4.900000e+5, data.EFR[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.ENP[0][1] )
            self.assertAlmostEqual( 1.110000e+3, data.END[0][1] )
            self.assertAlmostEqual( 5.000000e+5, data.EGP[0][1] )
            self.assertAlmostEqual( 5.000000e+4, data.EGD[0][1] )
            self.assertAlmostEqual( 5.100000e+4, data.EB[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.ENU[0][1] )
            self.assertAlmostEqual( 1.500000e+5, data.ER[0][1] )
            self.assertAlmostEqual( 1.300000e+5, data.ET[0][1] )

            self.assertAlmostEqual( 1.691300e+8, data.fission_fragments[0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.prompt_neutrons[0][0] )
            self.assertAlmostEqual( 7.400000e+3, data.delayed_neutrons[0][0] )
            self.assertAlmostEqual( 6.600000e+6, data.prompt_gammas[0][0] )
            self.assertAlmostEqual( 6.330000e+6, data.delayed_gammas[0][0] )
            self.assertAlmostEqual( 6.500000e+6, data.delayed_betas[0][0] )
            self.assertAlmostEqual( 8.750000e+6, data.neutrinos[0][0] )
            self.assertAlmostEqual( 1.934054e+8, data.total_minus_neutrinos[0][0] )
            self.assertAlmostEqual( 2.021554e+8, data.total[0][0] )

            self.assertAlmostEqual( 4.900000e+5, data.fission_fragments[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.prompt_neutrons[0][1] )
            self.assertAlmostEqual( 1.110000e+3, data.delayed_neutrons[0][1] )
            self.assertAlmostEqual( 5.000000e+5, data.prompt_gammas[0][1] )
            self.assertAlmostEqual( 5.000000e+4, data.delayed_gammas[0][1] )
            self.assertAlmostEqual( 5.100000e+4, data.delayed_betas[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.neutrinos[0][1] )
            self.assertAlmostEqual( 1.500000e+5, data.total_minus_neutrinos[0][1] )
            self.assertAlmostEqual( 1.300000e+5, data.total[0][1] )

            self.assertAlmostEqual( -2.660000e-1, data.EFR[1][0] )
            self.assertAlmostEqual( 3.004000e-1,  data.ENP[1][0] )
            self.assertAlmostEqual( 0.0, data.END[1][0] )
            self.assertAlmostEqual( 7.770000e-2,  data.EGP[1][0] )
            self.assertAlmostEqual( -7.500000e-2, data.EGD[1][0] )
            self.assertAlmostEqual( -7.700000e-2, data.EB[1][0] )
            self.assertAlmostEqual( -1.000000e-1, data.ENU[1][0] )
            self.assertAlmostEqual( -3.790000e-2, data.ER[1][0] )
            self.assertAlmostEqual( -1.379000e-1, data.ET[1][0] )

            self.assertAlmostEqual( 2.660000e-2, data.EFR[1][1] )
            self.assertAlmostEqual( 3.004000e-2, data.ENP[1][1] )
            self.assertAlmostEqual( 0.0, data.END[1][1] )
            self.assertAlmostEqual( 7.770000e-3, data.EGP[1][1] )
            self.assertAlmostEqual( 7.600000e-3, data.EGD[1][1] )
            self.assertAlmostEqual( 7.800000e-3, data.EB[1][1] )
            self.assertAlmostEqual( 1.000000e-2, data.ENU[1][1] )
            self.assertAlmostEqual( 3.790000e-3, data.ER[1][1] )
            self.assertAlmostEqual( 1.379000e-2, data.ET[1][1] )

            self.assertAlmostEqual( -2.660000e-1, data.fission_fragments[1][0] )
            self.assertAlmostEqual( 3.004000e-1,  data.prompt_neutrons[1][0] )
            self.assertAlmostEqual( 0.0, data.delayed_neutrons[1][0] )
            self.assertAlmostEqual( 7.770000e-2,  data.prompt_gammas[1][0] )
            self.assertAlmostEqual( -7.500000e-2, data.delayed_gammas[1][0] )
            self.assertAlmostEqual( -7.700000e-2, data.delayed_betas[1][0] )
            self.assertAlmostEqual( -1.000000e-1, data.neutrinos[1][0] )
            self.assertAlmostEqual( -3.790000e-2, data.total_minus_neutrinos[1][0] )
            self.assertAlmostEqual( -1.379000e-1, data.total[1][0] )

            self.assertAlmostEqual( 2.660000e-2, data.fission_fragments[1][1] )
            self.assertAlmostEqual( 3.004000e-2, data.prompt_neutrons[1][1] )
            self.assertAlmostEqual( 0.0, data.delayed_neutrons[1][1] )
            self.assertAlmostEqual( 7.770000e-3, data.prompt_gammas[1][1] )
            self.assertAlmostEqual( 7.600000e-3, data.delayed_gammas[1][1] )
            self.assertAlmostEqual( 7.800000e-3, data.delayed_betas[1][1] )
            self.assertAlmostEqual( 1.000000e-2, data.neutrinos[1][1] )
            self.assertAlmostEqual( 3.790000e-3, data.total_minus_neutrinos[1][1] )
            self.assertAlmostEqual( 1.379000e-2, data.total[1][1] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_polynomial + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        def verify_chunk_tabulated( self, chunk ) :

            # verify content
            self.assertEqual( 458, chunk.MT )
            self.assertEqual( 458, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertEqual( 233.0248, chunk.AWR )
            self.assertEqual( 233.0248, chunk.atomic_weight_ratio )

            self.assertEqual( True, chunk.LFC )
            self.assertEqual( True, chunk.tabulated_energy_release )
            self.assertEqual( 0, chunk.NPLY )
            self.assertEqual( 0, chunk.order )
            self.assertEqual( 2, chunk.NFC )
            self.assertEqual( 2, chunk.number_tabulated_components )

            data = chunk.energy_release

            self.assertEqual( True, data.LFC )
            self.assertEqual( True, data.tabulated_energy_release )
            self.assertEqual( 0, data.NPLY )
            self.assertEqual( 0, data.order )
            self.assertEqual( 2, data.NFC )
            self.assertEqual( 2, data.number_tabulated_components )

            self.assertAlmostEqual( 1.691300e+8, data.thermal_point_values.E[0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.thermal_point_values.E[1][0] )
            self.assertAlmostEqual( 7.400000e+3, data.thermal_point_values.E[2][0] )
            self.assertAlmostEqual( 6.600000e+6, data.thermal_point_values.E[3][0] )
            self.assertAlmostEqual( 6.330000e+6, data.thermal_point_values.E[4][0] )
            self.assertAlmostEqual( 6.500000e+6, data.thermal_point_values.E[5][0] )
            self.assertAlmostEqual( 8.750000e+6, data.thermal_point_values.E[6][0] )
            self.assertAlmostEqual( 1.934054e+8, data.thermal_point_values.E[7][0] )
            self.assertAlmostEqual( 2.021554e+8, data.thermal_point_values.E[8][0] )

            self.assertAlmostEqual( 4.900000e+5, data.thermal_point_values.E[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.E[1][1] )
            self.assertAlmostEqual( 1.110000e+3, data.thermal_point_values.E[2][1] )
            self.assertAlmostEqual( 5.000000e+5, data.thermal_point_values.E[3][1] )
            self.assertAlmostEqual( 5.000000e+4, data.thermal_point_values.E[4][1] )
            self.assertAlmostEqual( 5.100000e+4, data.thermal_point_values.E[5][1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.E[6][1] )
            self.assertAlmostEqual( 1.500000e+5, data.thermal_point_values.E[7][1] )
            self.assertAlmostEqual( 1.300000e+5, data.thermal_point_values.E[8][1] )

            self.assertAlmostEqual( 1.691300e+8, data.thermal_point_values.energy_release[0][0] )
            self.assertAlmostEqual( 4.838000e+6, data.thermal_point_values.energy_release[1][0] )
            self.assertAlmostEqual( 7.400000e+3, data.thermal_point_values.energy_release[2][0] )
            self.assertAlmostEqual( 6.600000e+6, data.thermal_point_values.energy_release[3][0] )
            self.assertAlmostEqual( 6.330000e+6, data.thermal_point_values.energy_release[4][0] )
            self.assertAlmostEqual( 6.500000e+6, data.thermal_point_values.energy_release[5][0] )
            self.assertAlmostEqual( 8.750000e+6, data.thermal_point_values.energy_release[6][0] )
            self.assertAlmostEqual( 1.934054e+8, data.thermal_point_values.energy_release[7][0] )
            self.assertAlmostEqual( 2.021554e+8, data.thermal_point_values.energy_release[8][0] )

            self.assertAlmostEqual( 4.900000e+5, data.thermal_point_values.energy_release[0][1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.energy_release[1][1] )
            self.assertAlmostEqual( 1.110000e+3, data.thermal_point_values.energy_release[2][1] )
            self.assertAlmostEqual( 5.000000e+5, data.thermal_point_values.energy_release[3][1] )
            self.assertAlmostEqual( 5.000000e+4, data.thermal_point_values.energy_release[4][1] )
            self.assertAlmostEqual( 5.100000e+4, data.thermal_point_values.energy_release[5][1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.energy_release[6][1] )
            self.assertAlmostEqual( 1.500000e+5, data.thermal_point_values.energy_release[7][1] )
            self.assertAlmostEqual( 1.300000e+5, data.thermal_point_values.energy_release[8][1] )

            self.assertAlmostEqual( 1.691300e+8, data.thermal_point_values.EFR[0] )
            self.assertAlmostEqual( 4.838000e+6, data.thermal_point_values.ENP[0] )
            self.assertAlmostEqual( 7.400000e+3, data.thermal_point_values.END[0] )
            self.assertAlmostEqual( 6.600000e+6, data.thermal_point_values.EGP[0] )
            self.assertAlmostEqual( 6.330000e+6, data.thermal_point_values.EGD[0] )
            self.assertAlmostEqual( 6.500000e+6, data.thermal_point_values.EB[0] )
            self.assertAlmostEqual( 8.750000e+6, data.thermal_point_values.ENU[0] )
            self.assertAlmostEqual( 1.934054e+8, data.thermal_point_values.ER[0] )
            self.assertAlmostEqual( 2.021554e+8, data.thermal_point_values.ET[0] )

            self.assertAlmostEqual( 4.900000e+5, data.thermal_point_values.EFR[1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.ENP[1] )
            self.assertAlmostEqual( 1.110000e+3, data.thermal_point_values.END[1] )
            self.assertAlmostEqual( 5.000000e+5, data.thermal_point_values.EGP[1] )
            self.assertAlmostEqual( 5.000000e+4, data.thermal_point_values.EGD[1] )
            self.assertAlmostEqual( 5.100000e+4, data.thermal_point_values.EB[1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.ENU[1] )
            self.assertAlmostEqual( 1.500000e+5, data.thermal_point_values.ER[1] )
            self.assertAlmostEqual( 1.300000e+5, data.thermal_point_values.ET[1] )

            self.assertAlmostEqual( 1.691300e+8, data.thermal_point_values.fission_fragments[0] )
            self.assertAlmostEqual( 4.838000e+6, data.thermal_point_values.prompt_neutrons[0] )
            self.assertAlmostEqual( 7.400000e+3, data.thermal_point_values.delayed_neutrons[0] )
            self.assertAlmostEqual( 6.600000e+6, data.thermal_point_values.prompt_gammas[0] )
            self.assertAlmostEqual( 6.330000e+6, data.thermal_point_values.delayed_gammas[0] )
            self.assertAlmostEqual( 6.500000e+6, data.thermal_point_values.delayed_betas[0] )
            self.assertAlmostEqual( 8.750000e+6, data.thermal_point_values.neutrinos[0] )
            self.assertAlmostEqual( 1.934054e+8, data.thermal_point_values.total_minus_neutrinos[0] )
            self.assertAlmostEqual( 2.021554e+8, data.thermal_point_values.total[0] )

            self.assertAlmostEqual( 4.900000e+5, data.thermal_point_values.fission_fragments[1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.prompt_neutrons[1] )
            self.assertAlmostEqual( 1.110000e+3, data.thermal_point_values.delayed_neutrons[1] )
            self.assertAlmostEqual( 5.000000e+5, data.thermal_point_values.prompt_gammas[1] )
            self.assertAlmostEqual( 5.000000e+4, data.thermal_point_values.delayed_gammas[1] )
            self.assertAlmostEqual( 5.100000e+4, data.thermal_point_values.delayed_betas[1] )
            self.assertAlmostEqual( 7.000000e+4, data.thermal_point_values.neutrinos[1] )
            self.assertAlmostEqual( 1.500000e+5, data.thermal_point_values.total_minus_neutrinos[1] )
            self.assertAlmostEqual( 1.300000e+5, data.thermal_point_values.total[1] )

            self.assertEqual( True, None != data.tabulated_EFR )
            self.assertEqual( None, data.tabulated_ENP )
            self.assertEqual( None, data.tabulated_END )
            self.assertEqual( None, data.tabulated_EGP )
            self.assertEqual( None, data.tabulated_EGD )
            self.assertEqual( None, data.tabulated_EB )
            self.assertEqual( None, data.tabulated_ENU )
            self.assertEqual( None, data.tabulated_ER )
            self.assertEqual( True, None != data.tabulated_ET )

            self.assertEqual( True, None != data.tabulated_fission_fragments )
            self.assertEqual( None, data.tabulated_prompt_neutrons )
            self.assertEqual( None, data.tabulated_delayed_neutrons )
            self.assertEqual( None, data.tabulated_prompt_gammas )
            self.assertEqual( None, data.tabulated_delayed_gammas )
            self.assertEqual( None, data.tabulated_delayed_betas )
            self.assertEqual( None, data.tabulated_neutrinos )
            self.assertEqual( None, data.tabulated_total_minus_neutrinos )
            self.assertEqual( True, None != data.tabulated_total )

            component = data.tabulated_EFR
            self.assertEqual( False, component.LDRV )
            self.assertEqual( 1, component.IFC )
            self.assertEqual( 3, component.NP )
            self.assertEqual( 3, component.number_points )
            self.assertEqual( 1, component.NR )
            self.assertEqual( 1, component.number_interpolation_regions )
            self.assertEqual( 1, len( component.INT ) )
            self.assertEqual( 1, len( component.NBT ) )
            self.assertEqual( 2, component.INT[0] )
            self.assertEqual( 3, component.NBT[0] )
            self.assertEqual( 1, len( component.interpolants ) )
            self.assertEqual( 1, len( component.boundaries ) )
            self.assertEqual( 2, component.interpolants[0] )
            self.assertEqual( 3, component.boundaries[0] )
            self.assertEqual( 3, len( component.energies ) )
            self.assertEqual( 3, len( component.q_values ) )
            self.assertAlmostEqual( 1e-5, component.energies[0] )
            self.assertAlmostEqual( 0.0253, component.energies[1] )
            self.assertAlmostEqual( 2e+7, component.energies[2] )
            self.assertAlmostEqual( 1.6913e+8, component.q_values[0] )
            self.assertAlmostEqual( 1.691e+8, component.q_values[1] )
            self.assertAlmostEqual( 1.69e+8, component.q_values[2] )

            component = data.tabulated_ET
            self.assertEqual( True, component.LDRV )
            self.assertEqual( 9, component.IFC )
            self.assertEqual( 4, component.NP )
            self.assertEqual( 4, component.number_points )
            self.assertEqual( 1, component.NR )
            self.assertEqual( 1, component.number_interpolation_regions )
            self.assertEqual( 1, len( component.INT ) )
            self.assertEqual( 1, len( component.NBT ) )
            self.assertEqual( 2, component.INT[0] )
            self.assertEqual( 4, component.NBT[0] )
            self.assertEqual( 1, len( component.interpolants ) )
            self.assertEqual( 1, len( component.boundaries ) )
            self.assertEqual( 2, component.interpolants[0] )
            self.assertEqual( 4, component.boundaries[0] )
            self.assertEqual( 4, len( component.energies ) )
            self.assertEqual( 4, len( component.q_values ) )
            self.assertAlmostEqual( 1e-5, component.energies[0] )
            self.assertAlmostEqual( 0.0253, component.energies[1] )
            self.assertAlmostEqual( 1e+6, component.energies[2] )
            self.assertAlmostEqual( 2e+7, component.energies[3] )
            self.assertAlmostEqual( 2.021554e+8, component.q_values[0] )
            self.assertAlmostEqual( 3e+8, component.q_values[1] )
            self.assertAlmostEqual( 2.5e+8, component.q_values[2] )
            self.assertAlmostEqual( 1.5e+8, component.q_values[3] )

            self.assertEqual( 12, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_tabulated + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         fissionq = ThermalPointComponents( [ 1.691300e+8, 4.900000e+5 ],
                                                            [ 4.838000e+6, 7.000000e+4 ],
                                                            [ 7.400000e+3, 1.110000e+3 ],
                                                            [ 6.600000e+6, 5.000000e+5 ],
                                                            [ 6.330000e+6, 5.000000e+4 ],
                                                            [ 6.500000e+6, 5.100000e+4 ],
                                                            [ 8.750000e+6, 7.000000e+4 ],
                                                            [ 1.934054e+8, 1.500000e+5 ],
                                                            [ 2.021554e+8, 1.300000e+5 ] ) )

        verify_chunk_thermal( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_thermal + self.valid_SEND )

        verify_chunk_thermal( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_thermal +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 1 ).section( 458 ).parse()

        verify_chunk_thermal( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_thermal( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         fissionq = PolynomialComponents(
                                        [ [ 1.691300e+8, 4.900000e+5 ], [ -2.66e-1, 2.66e-2 ] ],
                                        [ [ 4.838000e+6, 7.000000e+4 ], [ 3.004e-1, 3.004e-2 ] ],
                                        [ [ 7.400000e+3, 1.110000e+3 ], [ 0., 0. ] ],
                                        [ [ 6.600000e+6, 5.000000e+5 ], [ 7.77e-2, 7.77e-3 ] ],
                                        [ [ 6.330000e+6, 5.000000e+4 ], [ -7.500e-2, 7.600e-3 ] ],
                                        [ [ 6.500000e+6, 5.100000e+4 ], [ -7.700e-2, 7.800e-3 ] ],
                                        [ [ 8.750000e+6, 7.000000e+4 ], [ -1.00e-1, 1.00e-2 ] ],
                                        [ [ 1.934054e+8, 1.500000e+5 ], [ -3.790e-2, 3.790e-3 ] ],
                                        [ [ 2.021554e+8, 1.300000e+5 ], [ -1.379e-1, 1.379e-2 ] ] ) )

        verify_chunk_polynomial( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_polynomial + self.valid_SEND )

        verify_chunk_polynomial( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_polynomial +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 1 ).section( 458 ).parse()

        verify_chunk_polynomial( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_polynomial( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         fissionq = TabulatedComponents(
                                        ThermalPointComponents(
                                            [ 1.691300e+8, 4.900000e+5 ],
                                            [ 4.838000e+6, 7.000000e+4 ],
                                            [ 7.400000e+3, 1.110000e+3 ],
                                            [ 6.600000e+6, 5.000000e+5 ],
                                            [ 6.330000e+6, 5.000000e+4 ],
                                            [ 6.500000e+6, 5.100000e+4 ],
                                            [ 8.750000e+6, 7.000000e+4 ],
                                            [ 1.934054e+8, 1.500000e+5 ],
                                            [ 2.021554e+8, 1.300000e+5 ] ),
                                        [ EnergyReleaseComponent( False, 1, [ 3 ], [ 2 ],
                                                                  [ 1.000000e-5, 2.530000e-2, 2.000000e+7 ],
                                                                  [ 1.691300e+8, 1.691000e+8, 1.690000e+8 ] ),
                                          EnergyReleaseComponent( True, 9, [ 4 ], [ 2 ],
                                                                  [ 1.000000e-5, 2.530000e-2, 1.000000e+6,
                                                                    2.000000e+7 ],
                                                                  [ 2.021554e+8, 3.000000e+8, 2.500000e+8,
                                                                    1.500000e+8 ] ) ] ) )

        verify_chunk_tabulated( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_tabulated + self.valid_SEND )

        verify_chunk_tabulated( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_tabulated +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 1 ).section( 458 ).parse()

        verify_chunk_tabulated( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_tabulated( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

        # illegal lfc
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.invalid_lfc + self.valid_SEND )

        # illegal nfc
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.invalid_nfc + self.valid_SEND )

if __name__ == '__main__' :

    unittest.main()
