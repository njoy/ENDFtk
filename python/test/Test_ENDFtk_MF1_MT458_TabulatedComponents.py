# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT458 import ThermalPointComponents
from ENDFtk.MF1.MT458 import TabulatedComponents
from ENDFtk.MF1.MT458 import EnergyReleaseComponent

class Test_ENDFtk_MF1_TabulatedComponents( unittest.TestCase ) :
    """Unit test for the TabulatedComponents class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0         18          99228 1458     \n'
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

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( True, chunk.LFC )
            self.assertEqual( True, chunk.tabulated_energy_release )
            self.assertEqual( 0, chunk.NPLY )
            self.assertEqual( 0, chunk.order )
            self.assertEqual( 2, chunk.NFC )
            self.assertEqual( 2, chunk.number_tabulated_components )

            self.assertEqual( 1.691300e+8, chunk.thermal_point_values.E[0][0] )
            self.assertEqual( 4.838000e+6, chunk.thermal_point_values.E[1][0] )
            self.assertEqual( 7.400000e+3, chunk.thermal_point_values.E[2][0] )
            self.assertEqual( 6.600000e+6, chunk.thermal_point_values.E[3][0] )
            self.assertEqual( 6.330000e+6, chunk.thermal_point_values.E[4][0] )
            self.assertEqual( 6.500000e+6, chunk.thermal_point_values.E[5][0] )
            self.assertEqual( 8.750000e+6, chunk.thermal_point_values.E[6][0] )
            self.assertEqual( 1.934054e+8, chunk.thermal_point_values.E[7][0] )
            self.assertEqual( 2.021554e+8, chunk.thermal_point_values.E[8][0] )

            self.assertEqual( 4.900000e+5, chunk.thermal_point_values.E[0][1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.E[1][1] )
            self.assertEqual( 1.110000e+3, chunk.thermal_point_values.E[2][1] )
            self.assertEqual( 5.000000e+5, chunk.thermal_point_values.E[3][1] )
            self.assertEqual( 5.000000e+4, chunk.thermal_point_values.E[4][1] )
            self.assertEqual( 5.100000e+4, chunk.thermal_point_values.E[5][1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.E[6][1] )
            self.assertEqual( 1.500000e+5, chunk.thermal_point_values.E[7][1] )
            self.assertEqual( 1.300000e+5, chunk.thermal_point_values.E[8][1] )

            self.assertEqual( 1.691300e+8, chunk.thermal_point_values.energy_release[0][0] )
            self.assertEqual( 4.838000e+6, chunk.thermal_point_values.energy_release[1][0] )
            self.assertEqual( 7.400000e+3, chunk.thermal_point_values.energy_release[2][0] )
            self.assertEqual( 6.600000e+6, chunk.thermal_point_values.energy_release[3][0] )
            self.assertEqual( 6.330000e+6, chunk.thermal_point_values.energy_release[4][0] )
            self.assertEqual( 6.500000e+6, chunk.thermal_point_values.energy_release[5][0] )
            self.assertEqual( 8.750000e+6, chunk.thermal_point_values.energy_release[6][0] )
            self.assertEqual( 1.934054e+8, chunk.thermal_point_values.energy_release[7][0] )
            self.assertEqual( 2.021554e+8, chunk.thermal_point_values.energy_release[8][0] )

            self.assertEqual( 4.900000e+5, chunk.thermal_point_values.energy_release[0][1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.energy_release[1][1] )
            self.assertEqual( 1.110000e+3, chunk.thermal_point_values.energy_release[2][1] )
            self.assertEqual( 5.000000e+5, chunk.thermal_point_values.energy_release[3][1] )
            self.assertEqual( 5.000000e+4, chunk.thermal_point_values.energy_release[4][1] )
            self.assertEqual( 5.100000e+4, chunk.thermal_point_values.energy_release[5][1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.energy_release[6][1] )
            self.assertEqual( 1.500000e+5, chunk.thermal_point_values.energy_release[7][1] )
            self.assertEqual( 1.300000e+5, chunk.thermal_point_values.energy_release[8][1] )

            self.assertEqual( 1.691300e+8, chunk.thermal_point_values.EFR[0] )
            self.assertEqual( 4.838000e+6, chunk.thermal_point_values.ENP[0] )
            self.assertEqual( 7.400000e+3, chunk.thermal_point_values.END[0] )
            self.assertEqual( 6.600000e+6, chunk.thermal_point_values.EGP[0] )
            self.assertEqual( 6.330000e+6, chunk.thermal_point_values.EGD[0] )
            self.assertEqual( 6.500000e+6, chunk.thermal_point_values.EB[0] )
            self.assertEqual( 8.750000e+6, chunk.thermal_point_values.ENU[0] )
            self.assertEqual( 1.934054e+8, chunk.thermal_point_values.ER[0] )
            self.assertEqual( 2.021554e+8, chunk.thermal_point_values.ET[0] )

            self.assertEqual( 4.900000e+5, chunk.thermal_point_values.EFR[1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.ENP[1] )
            self.assertEqual( 1.110000e+3, chunk.thermal_point_values.END[1] )
            self.assertEqual( 5.000000e+5, chunk.thermal_point_values.EGP[1] )
            self.assertEqual( 5.000000e+4, chunk.thermal_point_values.EGD[1] )
            self.assertEqual( 5.100000e+4, chunk.thermal_point_values.EB[1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.ENU[1] )
            self.assertEqual( 1.500000e+5, chunk.thermal_point_values.ER[1] )
            self.assertEqual( 1.300000e+5, chunk.thermal_point_values.ET[1] )

            self.assertEqual( 1.691300e+8, chunk.thermal_point_values.fission_fragments[0] )
            self.assertEqual( 4.838000e+6, chunk.thermal_point_values.prompt_neutrons[0] )
            self.assertEqual( 7.400000e+3, chunk.thermal_point_values.delayed_neutrons[0] )
            self.assertEqual( 6.600000e+6, chunk.thermal_point_values.prompt_gammas[0] )
            self.assertEqual( 6.330000e+6, chunk.thermal_point_values.delayed_gammas[0] )
            self.assertEqual( 6.500000e+6, chunk.thermal_point_values.delayed_betas[0] )
            self.assertEqual( 8.750000e+6, chunk.thermal_point_values.neutrinos[0] )
            self.assertEqual( 1.934054e+8, chunk.thermal_point_values.total_minus_neutrinos[0] )
            self.assertEqual( 2.021554e+8, chunk.thermal_point_values.total[0] )

            self.assertEqual( 4.900000e+5, chunk.thermal_point_values.fission_fragments[1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.prompt_neutrons[1] )
            self.assertEqual( 1.110000e+3, chunk.thermal_point_values.delayed_neutrons[1] )
            self.assertEqual( 5.000000e+5, chunk.thermal_point_values.prompt_gammas[1] )
            self.assertEqual( 5.000000e+4, chunk.thermal_point_values.delayed_gammas[1] )
            self.assertEqual( 5.100000e+4, chunk.thermal_point_values.delayed_betas[1] )
            self.assertEqual( 7.000000e+4, chunk.thermal_point_values.neutrinos[1] )
            self.assertEqual( 1.500000e+5, chunk.thermal_point_values.total_minus_neutrinos[1] )
            self.assertEqual( 1.300000e+5, chunk.thermal_point_values.total[1] )

            self.assertEqual( True, None != chunk.tabulated_EFR )
            self.assertEqual( None, chunk.tabulated_ENP )
            self.assertEqual( None, chunk.tabulated_END )
            self.assertEqual( None, chunk.tabulated_EGP )
            self.assertEqual( None, chunk.tabulated_EGD )
            self.assertEqual( None, chunk.tabulated_EB )
            self.assertEqual( None, chunk.tabulated_ENU )
            self.assertEqual( None, chunk.tabulated_ER )
            self.assertEqual( True, None != chunk.tabulated_ET )

            self.assertEqual( True, None != chunk.tabulated_fission_fragments )
            self.assertEqual( None, chunk.tabulated_prompt_neutrons )
            self.assertEqual( None, chunk.tabulated_delayed_neutrons )
            self.assertEqual( None, chunk.tabulated_prompt_gammas )
            self.assertEqual( None, chunk.tabulated_delayed_gammas )
            self.assertEqual( None, chunk.tabulated_delayed_betas )
            self.assertEqual( None, chunk.tabulated_neutrinos )
            self.assertEqual( None, chunk.tabulated_total_minus_neutrinos )
            self.assertEqual( True, None != chunk.tabulated_total )

            component = chunk.tabulated_fission_fragments
            self.assertEqual( False, component.LDRV )
            self.assertEqual( 1, component.IFC )
            self.assertEqual( 3, component.NP )
            self.assertEqual( 1, component.NR )
            self.assertEqual( 1, len( component.interpolants ) )
            self.assertEqual( 1, len( component.boundaries ) )
            self.assertEqual( 2, component.interpolants[0] );
            self.assertEqual( 3, component.boundaries[0] );
            self.assertEqual( 3, len( component.energies ) )
            self.assertEqual( 3, len( component.q_values ) )
            self.assertEqual( 1e-5, component.energies[0] )
            self.assertEqual( 0.0253, component.energies[1] )
            self.assertEqual( 2e+7, component.energies[2] )
            self.assertEqual( 1.6913e+8, component.q_values[0] )
            self.assertEqual( 1.691e+8, component.q_values[1] )
            self.assertEqual( 1.69e+8, component.q_values[2] )

            component = chunk.tabulated_total
            self.assertEqual( True, component.LDRV )
            self.assertEqual( 9, component.IFC )
            self.assertEqual( 4, component.NP )
            self.assertEqual( 1, component.NR )
            self.assertEqual( 1, len( component.interpolants ) )
            self.assertEqual( 1, len( component.boundaries ) )
            self.assertEqual( 2, component.interpolants[0] );
            self.assertEqual( 4, component.boundaries[0] );
            self.assertEqual( 4, len( component.energies ) )
            self.assertEqual( 4, len( component.q_values ) )
            self.assertEqual( 1e-5, component.energies[0] )
            self.assertEqual( 0.0253, component.energies[1] )
            self.assertEqual( 1e+6, component.energies[2] )
            self.assertEqual( 2e+7, component.energies[3] )
            self.assertEqual( 2.021554e+8, component.q_values[0] )
            self.assertEqual( 3e+8, component.q_values[1] )
            self.assertEqual( 2.5e+8, component.q_values[2] )
            self.assertEqual( 1.5e+8, component.q_values[3] )

            self.assertEqual( 11, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 458 ) )

        # the data is given explicitly
        chunk = TabulatedComponents(
                    thermal = ThermalPointComponents( efr = [ 1.691300e+8, 4.900000e+5 ],
                                                      enp = [ 4.838000e+6, 7.000000e+4 ],
                                                      end = [ 7.400000e+3, 1.110000e+3 ],
                                                      egp = [ 6.600000e+6, 5.000000e+5 ],
                                                      egd = [ 6.330000e+6, 5.000000e+4 ],
                                                      eb = [ 6.500000e+6, 5.100000e+4 ],
                                                      enu = [ 8.750000e+6, 7.000000e+4 ],
                                                      er = [ 1.934054e+8, 1.500000e+5 ],
                                                      et = [ 2.021554e+8, 1.300000e+5 ] ),
                    tables = [ EnergyReleaseComponent( False, 1, [ 3 ], [ 2 ],
                                                       [ 1.000000e-5, 2.530000e-2, 2.000000e+7 ],
                                                       [ 1.691300e+8, 1.691000e+8, 1.690000e+8 ] ),
                               EnergyReleaseComponent( True, 9, [ 4 ], [ 2 ],
                                                       [ 1.000000e-5, 2.530000e-2, 1.000000e+6,
                                                         2.000000e+7 ],
                                                       [ 2.021554e+8, 3.000000e+8, 2.500000e+8,
                                                         1.500000e+8 ] ) ] )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedComponents( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid IFC
        with self.assertRaises( Exception ) :

            chunk = TabulatedComponents(
                        thermal = ThermalPointComponents( efr = [ 1.691300e+8, 4.900000e+5 ],
                                                          enp = [ 4.838000e+6, 7.000000e+4 ],
                                                          end = [ 7.400000e+3, 1.110000e+3 ],
                                                          egp = [ 6.600000e+6, 5.000000e+5 ],
                                                          egd = [ 6.330000e+6, 5.000000e+4 ],
                                                          eb = [ 6.500000e+6, 5.100000e+4 ],
                                                          enu = [ 8.750000e+6, 7.000000e+4 ],
                                                          er = [ 1.934054e+8, 1.500000e+5 ],
                                                          et = [ 2.021554e+8, 1.300000e+5 ] ),
                        tables = [ EnergyReleaseComponent( false, 1, [ 3 ], [ 2 ],
                                                           [ 1.000000e-5, 2.530000e-2, 2.000000e+7 ],
                                                           [ 1.691300e+8, 1.691000e+8, 1.690000e+8 ] ),
                                   EnergyReleaseComponent( true, 10, [ 4 ], [ 2 ],
                                                           [ 1.000000e-5, 2.530000e-2, 1.000000e+6,
                                                             2.000000e+7 ],
                                                           [ 2.021554e+8, 3.000000e+8, 2.500000e+8,
                                                             1.500000e+8 ] ) ] )

        # duplicate IFC
        with self.assertRaises( Exception ) :

            chunk = TabulatedComponents(
                        thermal = ThermalPointComponents( efr = [ 1.691300e+8, 4.900000e+5 ],
                                                          enp = [ 4.838000e+6, 7.000000e+4 ],
                                                          end = [ 7.400000e+3, 1.110000e+3 ],
                                                          egp = [ 6.600000e+6, 5.000000e+5 ],
                                                          egd = [ 6.330000e+6, 5.000000e+4 ],
                                                          eb = [ 6.500000e+6, 5.100000e+4 ],
                                                          enu = [ 8.750000e+6, 7.000000e+4 ],
                                                          er = [ 1.934054e+8, 1.500000e+5 ],
                                                          et = [ 2.021554e+8, 1.300000e+5 ] ),
                        tables = [ EnergyReleaseComponent( false, 1, [ 3 ], [ 2 ],
                                                           [ 1.000000e-5, 2.530000e-2, 2.000000e+7 ],
                                                           [ 1.691300e+8, 1.691000e+8, 1.690000e+8 ] ),
                                   EnergyReleaseComponent( true, 1, [ 4 ], [ 2 ],
                                                           [ 1.000000e-5, 2.530000e-2, 1.000000e+6,
                                                             2.000000e+7 ],
                                                           [ 2.021554e+8, 3.000000e+8, 2.500000e+8,
                                                             1.500000e+8 ] ) ] )

if __name__ == '__main__' :

    unittest.main()
