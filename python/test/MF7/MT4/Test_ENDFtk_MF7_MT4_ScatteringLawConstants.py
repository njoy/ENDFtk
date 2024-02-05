# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT4 import ScatteringLawConstants

class Test_ENDFtk_MF7_MT4_ScatteringLawConstants( unittest.TestCase ) :
    """Unit test for the ScatteringLawConstants class."""

    chunk_principal = ( ' 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n'
                        ' 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n' )

    chunk_principal_one_secondary = ( ' 0.000000+0 0.000000+0          0          0         12          1  27 7  4     \n'
                                      ' 2.021000+0 9.750000+1 2.784423+1 2.466750+0 0.000000+0 1.000000+0  27 7  4     \n'
                                      ' 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n' )

    chunk_principal_two_secondary = ( ' 0.000000+0 0.000000+0          0          0         18          2  27 7  4     \n'
                                      ' 2.021000+0 9.750000+1 2.784423+1 2.466750+0 0.000000+0 1.000000+0  27 7  4     \n'
                                      ' 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n'
                                      ' 1.000000+0 4.000000+0 2.000000+0 0.000000+0 0.000000+0 3.000000+0  27 7  4     \n' )

    chunk_principal_three_secondary = ( ' 0.000000+0 0.000000+0          0          0         24          3  27 7  4     \n'
                                        ' 2.021000+0 9.750000+1 2.784423+1 2.466750+0 0.000000+0 1.000000+0  27 7  4     \n'
                                        ' 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n'
                                        ' 1.000000+0 4.000000+0 2.000000+0 0.000000+0 0.000000+0 3.000000+0  27 7  4     \n'
                                        ' 2.000000+0 8.000000+0 4.000000+0 0.000000+0 0.000000+0 4.000000+0  27 7  4     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0         12          0  27 7  4     \n'
                ' 2.021000+0 9.750000+1 2.784423+1 2.466750+0 0.000000+0 1.000000+0  27 7  4     \n'
                ' 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n' )

    def test_component( self ) :

        def verify_chunk_principal( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LLN )
            self.assertEqual( 0, chunk.sab_storage_type )
            self.assertEqual( 6, chunk.NI )
            self.assertEqual( 6, chunk.number_constants )
            self.assertEqual( 0, chunk.NS )
            self.assertEqual( 0, chunk.number_non_principal_scatterers )

            self.assertAlmostEqual( 1.976285e+2, chunk.epsilon )
            self.assertAlmostEqual( 5.000001e+0, chunk.EMAX )
            self.assertAlmostEqual( 5.000001e+0, chunk.upper_energy_limit )
            self.assertEqual( 1, len( chunk.MSIGMA ) )
            self.assertEqual( 1, len( chunk.total_free_cross_sections ) )
            self.assertAlmostEqual( 6.153875e+0, chunk.MSIGMA[0] )
            self.assertAlmostEqual( 6.153875e+0, chunk.total_free_cross_sections[0] )
            self.assertEqual( 1, len( chunk.AWR ) )
            self.assertEqual( 1, len( chunk.atomic_weight_ratios ) )
            self.assertAlmostEqual( 8.934780e+0, chunk.AWR[0] )
            self.assertAlmostEqual( 8.934780e+0, chunk.atomic_weight_ratios[0] )
            self.assertEqual( 1, len( chunk.M ) )
            self.assertEqual( 1, len( chunk.number_atoms ) )
            self.assertAlmostEqual( 1., chunk.M[0] )
            self.assertAlmostEqual( 1., chunk.number_atoms[0] )
            self.assertEqual( 0, len( chunk.analytical_function_types ) )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_principal, chunk.to_string( 27, 7, 4 ) )

        def verify_chunk_principal_one_secondary( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LLN )
            self.assertEqual( 0, chunk.sab_storage_type )
            self.assertEqual( 12, chunk.NI )
            self.assertEqual( 12, chunk.number_constants )
            self.assertEqual( 1, chunk.NS )
            self.assertEqual( 1, chunk.number_non_principal_scatterers )

            self.assertAlmostEqual( 9.750000e+1, chunk.epsilon )
            self.assertAlmostEqual( 2.466750e+0, chunk.EMAX )
            self.assertAlmostEqual( 2.466750e+0, chunk.upper_energy_limit )
            self.assertEqual( 2, len( chunk.MSIGMA ) )
            self.assertEqual( 2, len( chunk.total_free_cross_sections ) )
            self.assertAlmostEqual( 2.021000e+0, chunk.MSIGMA[0] )
            self.assertAlmostEqual( 3.748750e+0, chunk.MSIGMA[1] )
            self.assertAlmostEqual( 2.021000e+0, chunk.total_free_cross_sections[0] )
            self.assertAlmostEqual( 3.748750e+0, chunk.total_free_cross_sections[1] )
            self.assertEqual( 2, len( chunk.AWR ) )
            self.assertEqual( 2, len( chunk.atomic_weight_ratios ) )
            self.assertAlmostEqual( 2.784423e+1, chunk.AWR[0] )
            self.assertAlmostEqual( 1.586200e+1, chunk.AWR[1] )
            self.assertAlmostEqual( 2.784423e+1, chunk.atomic_weight_ratios[0] )
            self.assertAlmostEqual( 1.586200e+1, chunk.atomic_weight_ratios[1] )
            self.assertEqual( 2, len( chunk.M ) )
            self.assertEqual( 2, len( chunk.number_atoms ) )
            self.assertAlmostEqual( 1., chunk.M[0] )
            self.assertAlmostEqual( 2., chunk.M[1] )
            self.assertAlmostEqual( 1., chunk.number_atoms[0] )
            self.assertAlmostEqual( 2., chunk.number_atoms[1] )
            self.assertEqual( 1, len( chunk.analytical_function_types ) )
            self.assertAlmostEqual( 0., chunk.analytical_function_types[0] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_principal_one_secondary, chunk.to_string( 27, 7, 4 ) )

        def verify_chunk_principal_two_secondary( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LLN )
            self.assertEqual( 0, chunk.sab_storage_type )
            self.assertEqual( 18, chunk.NI )
            self.assertEqual( 18, chunk.number_constants )
            self.assertEqual( 2, chunk.NS )
            self.assertEqual( 2, chunk.number_non_principal_scatterers )

            self.assertAlmostEqual( 9.750000e+1, chunk.epsilon )
            self.assertAlmostEqual( 2.466750e+0, chunk.EMAX )
            self.assertAlmostEqual( 2.466750e+0, chunk.upper_energy_limit )
            self.assertEqual( 3, len( chunk.MSIGMA ) )
            self.assertEqual( 3, len( chunk.total_free_cross_sections ) )
            self.assertAlmostEqual( 2.021000e+0, chunk.MSIGMA[0] )
            self.assertAlmostEqual( 3.748750e+0, chunk.MSIGMA[1] )
            self.assertAlmostEqual( 4.000000e+0, chunk.MSIGMA[2] )
            self.assertAlmostEqual( 2.021000e+0, chunk.total_free_cross_sections[0] )
            self.assertAlmostEqual( 3.748750e+0, chunk.total_free_cross_sections[1] )
            self.assertAlmostEqual( 4.000000e+0, chunk.total_free_cross_sections[2] )
            self.assertEqual( 3, len( chunk.AWR ) )
            self.assertEqual( 3, len( chunk.atomic_weight_ratios ) )
            self.assertAlmostEqual( 2.784423e+1, chunk.AWR[0] )
            self.assertAlmostEqual( 1.586200e+1, chunk.AWR[1] )
            self.assertAlmostEqual( 2.000000e+0, chunk.AWR[2] )
            self.assertAlmostEqual( 2.784423e+1, chunk.atomic_weight_ratios[0] )
            self.assertAlmostEqual( 1.586200e+1, chunk.atomic_weight_ratios[1] )
            self.assertAlmostEqual( 2.000000e+0, chunk.atomic_weight_ratios[2] )
            self.assertEqual( 3, len( chunk.M ) )
            self.assertEqual( 3, len( chunk.number_atoms ) )
            self.assertAlmostEqual( 1., chunk.M[0] )
            self.assertAlmostEqual( 2., chunk.M[1] )
            self.assertAlmostEqual( 3., chunk.M[2] )
            self.assertAlmostEqual( 1., chunk.number_atoms[0] )
            self.assertAlmostEqual( 2., chunk.number_atoms[1] )
            self.assertAlmostEqual( 3., chunk.number_atoms[2] )
            self.assertEqual( 2, len( chunk.analytical_function_types ) )
            self.assertAlmostEqual( 0., chunk.analytical_function_types[0] )
            self.assertAlmostEqual( 1., chunk.analytical_function_types[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_principal_two_secondary, chunk.to_string( 27, 7, 4 ) )

        def verify_chunk_principal_three_secondary( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LLN )
            self.assertEqual( 0, chunk.sab_storage_type )
            self.assertEqual( 24, chunk.NI )
            self.assertEqual( 24, chunk.number_constants )
            self.assertEqual( 3, chunk.NS )
            self.assertEqual( 3, chunk.number_non_principal_scatterers )

            self.assertAlmostEqual( 9.750000e+1, chunk.epsilon )
            self.assertAlmostEqual( 2.466750e+0, chunk.EMAX )
            self.assertAlmostEqual( 2.466750e+0, chunk.upper_energy_limit )
            self.assertEqual( 4, len( chunk.MSIGMA ) )
            self.assertEqual( 4, len( chunk.total_free_cross_sections ) )
            self.assertAlmostEqual( 2.021000e+0, chunk.MSIGMA[0] )
            self.assertAlmostEqual( 3.748750e+0, chunk.MSIGMA[1] )
            self.assertAlmostEqual( 4.000000e+0, chunk.MSIGMA[2] )
            self.assertAlmostEqual( 8.000000e+0, chunk.MSIGMA[3] )
            self.assertAlmostEqual( 2.021000e+0, chunk.total_free_cross_sections[0] )
            self.assertAlmostEqual( 3.748750e+0, chunk.total_free_cross_sections[1] )
            self.assertAlmostEqual( 4.000000e+0, chunk.total_free_cross_sections[2] )
            self.assertAlmostEqual( 8.000000e+0, chunk.total_free_cross_sections[3] )
            self.assertEqual( 4, len( chunk.AWR ) )
            self.assertEqual( 4, len( chunk.atomic_weight_ratios ) )
            self.assertAlmostEqual( 2.784423e+1, chunk.AWR[0] )
            self.assertAlmostEqual( 1.586200e+1, chunk.AWR[1] )
            self.assertAlmostEqual( 2.000000e+0, chunk.AWR[2] )
            self.assertAlmostEqual( 4.000000e+0, chunk.AWR[3] )
            self.assertAlmostEqual( 2.784423e+1, chunk.atomic_weight_ratios[0] )
            self.assertAlmostEqual( 1.586200e+1, chunk.atomic_weight_ratios[1] )
            self.assertAlmostEqual( 2.000000e+0, chunk.atomic_weight_ratios[2] )
            self.assertAlmostEqual( 4.000000e+0, chunk.atomic_weight_ratios[3] )
            self.assertEqual( 4, len( chunk.M ) )
            self.assertEqual( 4, len( chunk.number_atoms ) )
            self.assertAlmostEqual( 1., chunk.M[0] )
            self.assertAlmostEqual( 2., chunk.M[1] )
            self.assertAlmostEqual( 3., chunk.M[2] )
            self.assertAlmostEqual( 4., chunk.M[3] )
            self.assertAlmostEqual( 1., chunk.number_atoms[0] )
            self.assertAlmostEqual( 2., chunk.number_atoms[1] )
            self.assertAlmostEqual( 3., chunk.number_atoms[2] )
            self.assertAlmostEqual( 4., chunk.number_atoms[3] )
            self.assertEqual( 3, len( chunk.analytical_function_types ) )
            self.assertAlmostEqual( 0., chunk.analytical_function_types[0] )
            self.assertAlmostEqual( 1., chunk.analytical_function_types[1] )
            self.assertAlmostEqual( 2., chunk.analytical_function_types[2] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_principal_three_secondary, chunk.to_string( 27, 7, 4 ) )

        # the data is given explicitly
        chunk = ScatteringLawConstants( lln = 0, epsilon = 1.976285e+2, emax= 5.000001e+0,
                                        xs = 6.153875e+0, awr = 8.934780e+0, natoms = 1 )

        verify_chunk_principal( self, chunk )

        # the data is read from a string
        chunk = ScatteringLawConstants.from_string( self.chunk_principal, 27, 7, 4 )

        verify_chunk_principal( self, chunk )

        # the data is copied
        copy = ScatteringLawConstants( chunk )

        verify_chunk_principal( self, copy )

        # the data is given explicitly
        chunk = ScatteringLawConstants( lln = 0, ns = 1, epsilon = 9.750000e+1,  emax = 2.466750e+0,
                                        xs = [ 2.021000e+0, 3.748750e+0 ], awr = [ 2.784423e+1, 1.586200e+1 ],
                                        natoms = [ 1, 2 ], types = [ 0 ] )

        verify_chunk_principal_one_secondary( self, chunk )

        # the data is read from a string
        chunk = ScatteringLawConstants.from_string( self.chunk_principal_one_secondary, 27, 7, 4 )

        verify_chunk_principal_one_secondary( self, chunk )

        # the data is copied
        copy = ScatteringLawConstants( chunk )

        verify_chunk_principal_one_secondary( self, copy )

        # the data is given explicitly
        chunk = ScatteringLawConstants( lln = 0, ns = 2, epsilon = 9.750000e+1, emax = 2.466750e+0,
                                        xs = [ 2.021000e+0, 3.748750e+0, 4. ],
                                        awr = [ 2.784423e+1, 1.586200e+1, 2. ],
                                        natoms = [ 1, 2, 3 ], types = [ 0, 1 ] )

        verify_chunk_principal_two_secondary( self, chunk )

        # the data is read from a string
        chunk = ScatteringLawConstants.from_string( self.chunk_principal_two_secondary, 27, 7, 4 )

        verify_chunk_principal_two_secondary( self, chunk )

        # the data is copied
        copy = ScatteringLawConstants( chunk )

        verify_chunk_principal_two_secondary( self, copy )

        # the data is given explicitly
        chunk = ScatteringLawConstants( lln = 0, ns = 3, epsilon = 9.750000e+1, emax = 2.466750e+0,
                                        xs = [ 2.021000e+0, 3.748750e+0, 4., 8. ],
                                        awr = [ 2.784423e+1, 1.586200e+1, 2., 4. ],
                                        natoms = [ 1, 2, 3, 4 ], types = [ 0, 1, 2 ] )

        verify_chunk_principal_three_secondary( self, chunk )

        # the data is read from a string
        chunk = ScatteringLawConstants.from_string( self.chunk_principal_three_secondary, 27, 7, 4 )

        verify_chunk_principal_three_secondary( self, chunk )

        # the data is copied
        copy = ScatteringLawConstants( chunk )

        verify_chunk_principal_three_secondary( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # inconsistent data
        with self.assertRaises( Exception ) :

            chunk = ScatteringLawConstants( lln = 0, ns = 3, epsilon = 9.750000e+1, emax = 2.466750e+0,
                                            xs = [ 2.021000e+0, 3.748750e+0, 4., 8. ],
                                            awr = [ 2.784423e+1, 1.586200e+1, 2., 4. ],
                                            natoms = [ 1, 2, 3, 4 ], types = [] )

        with self.assertRaises( Exception ) :

            chunk = ScatteringLawConstants.from_string( self.invalid, 27, 7, 4 )

if __name__ == '__main__' :

    unittest.main()
