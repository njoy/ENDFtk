# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import DiscreteSpectrum

class Test_ENDFtk_MF8_MT457_DiscreteSpectrum( unittest.TestCase ) :
    """Unit test for the DiscreteSpectrum class."""

    chunk_styp_not_0_1 = ( ' 4.863000+4 5.000000+1          0          0          4          03580 8457     \n'
                           ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10                      3580 8457     \n' )

    chunk_styp_2 = ( ' 4.863000+4 5.000000+1          0          0          6          03580 8457     \n'
                     ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n' )

    chunk_styp_0 = ( ' 4.863000+4 5.000000+1          0          0         12          03580 8457     \n'
                     ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n'
                     ' 7.010000+5 1.106180-2 1.378999-1 2.000000-3 3.315735+5 5.608008+33580 8457     \n' )

    chunk_styp_8 = ( ' 4.863000+4 5.000000+1          0          0          8          03580 8457     \n'
                     ' 3.000000+0 1.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n'
                     ' 7.010000+5 1.106180-2                                            3580 8457     \n' )

    invalid = ( ' 4.863000+4 5.000000+1          0          0         10          03580 8457     \n'
                ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n'
                ' 7.010000+5 1.106180-2 1.378999-1 2.000000-3                      3580 8457     \n' )

    def test_component( self ) :

        def verify_chunk_styp_not_0_1( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.NT )
            self.assertAlmostEqual( 3., chunk.RTYP )
            self.assertAlmostEqual( 3., chunk.decay_chain )
            self.assertAlmostEqual( 4.863000e+4, chunk.ER[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.ER[1] )
            self.assertAlmostEqual( 4.863000e+4, chunk.discrete_energy[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.discrete_energy[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.RI[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.RI[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.relative_intensity[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.relative_intensity[1] )
            self.assertAlmostEqual( 0., chunk.TYPE )
            self.assertAlmostEqual( 0., chunk.type )
            self.assertAlmostEqual( 0.0, chunk.RIS[0] )
            self.assertAlmostEqual( 0.0, chunk.RIS[1] )
            self.assertAlmostEqual( 0.0, chunk.internal_pair_formation_coefficient[0] )
            self.assertAlmostEqual( 0.0, chunk.internal_pair_formation_coefficient[1] )
            self.assertAlmostEqual( 0.0, chunk.RICC[0] )
            self.assertAlmostEqual( 0.0, chunk.RICC[1] )
            self.assertAlmostEqual( 0.0, chunk.total_internal_conversion_coefficient[0] )
            self.assertAlmostEqual( 0.0, chunk.total_internal_conversion_coefficient[1] )
            self.assertAlmostEqual( 0.0, chunk.RICK[0] )
            self.assertAlmostEqual( 0.0, chunk.RICK[1] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_k_shell[0] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_k_shell[1] )
            self.assertAlmostEqual( 0.0, chunk.RICL[0] )
            self.assertAlmostEqual( 0.0, chunk.RICL[1] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_l_shell[0] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_l_shell[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_styp_not_0_1, chunk.to_string( 3580, 8, 457 ) )

        def verify_chunk_styp_2( self, chunk ) :

            # verify content
            self.assertEqual( 6, chunk.NT )
            self.assertAlmostEqual( 3., chunk.RTYP )
            self.assertAlmostEqual( 3., chunk.decay_chain )
            self.assertAlmostEqual( 4.863000e+4, chunk.discrete_energy[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.discrete_energy[1] )
            self.assertAlmostEqual( 4.863000e+4, chunk.ER[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.ER[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.relative_intensity[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.relative_intensity[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.RI[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.RI[1] )
            self.assertAlmostEqual( 0., chunk.TYPE )
            self.assertAlmostEqual( 0., chunk.type )
            self.assertAlmostEqual( 1.0, chunk.RIS[0] )
            self.assertAlmostEqual( 2.0, chunk.RIS[1] )
            self.assertAlmostEqual( 1.0, chunk.internal_pair_formation_coefficient[0] )
            self.assertAlmostEqual( 2.0, chunk.internal_pair_formation_coefficient[1] )
            self.assertAlmostEqual( 0.0, chunk.RICC[0] )
            self.assertAlmostEqual( 0.0, chunk.RICC[1] )
            self.assertAlmostEqual( 0.0, chunk.total_internal_conversion_coefficient[0] )
            self.assertAlmostEqual( 0.0, chunk.total_internal_conversion_coefficient[1] )
            self.assertAlmostEqual( 0.0, chunk.RICK[0] )
            self.assertAlmostEqual( 0.0, chunk.RICK[1] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_k_shell[0] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_k_shell[1] )
            self.assertAlmostEqual( 0.0, chunk.RICL[0] )
            self.assertAlmostEqual( 0.0, chunk.RICL[1] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_l_shell[0] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_l_shell[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_styp_2, chunk.to_string( 3580, 8, 457 ) )

        def verify_chunk_styp_0( self, chunk ) :

            # verify content
            self.assertEqual( 12, chunk.NT )
            self.assertAlmostEqual( 3., chunk.RTYP )
            self.assertAlmostEqual( 3., chunk.decay_chain )
            self.assertAlmostEqual( 4.863000e+4, chunk.ER[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.ER[1] )
            self.assertAlmostEqual( 4.863000e+4, chunk.discrete_energy[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.discrete_energy[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.RI[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.RI[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.relative_intensity[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.relative_intensity[1] )
            self.assertAlmostEqual( 0., chunk.TYPE )
            self.assertAlmostEqual( 0., chunk.type )
            self.assertAlmostEqual( 1.0, chunk.RIS[0] )
            self.assertAlmostEqual( 2.0, chunk.RIS[1] )
            self.assertAlmostEqual( 1.0, chunk.internal_pair_formation_coefficient[0] )
            self.assertAlmostEqual( 2.0, chunk.internal_pair_formation_coefficient[1] )
            self.assertAlmostEqual( 7.010000e+5, chunk.RICC[0] )
            self.assertAlmostEqual( 1.106180e-2, chunk.RICC[1] )
            self.assertAlmostEqual( 7.010000e+5, chunk.total_internal_conversion_coefficient[0] )
            self.assertAlmostEqual( 1.106180e-2, chunk.total_internal_conversion_coefficient[1] )
            self.assertAlmostEqual( 1.378999e-1, chunk.RICK[0] )
            self.assertAlmostEqual( 2.000000e-3, chunk.RICK[1] )
            self.assertAlmostEqual( 1.378999e-1, chunk.internal_conversion_coefficient_k_shell[0] )
            self.assertAlmostEqual( 2.000000e-3, chunk.internal_conversion_coefficient_k_shell[1] )
            self.assertAlmostEqual( 3.315735e+5, chunk.RICL[0] )
            self.assertAlmostEqual( 5.608008e+3, chunk.RICL[1] )
            self.assertAlmostEqual( 3.315735e+5, chunk.internal_conversion_coefficient_l_shell[0] )
            self.assertAlmostEqual( 5.608008e+3, chunk.internal_conversion_coefficient_l_shell[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_styp_0, chunk.to_string( 3580, 8, 457 ) )

        def verify_chunk_styp_8( self, chunk ) :

            # verify content
            self.assertEqual( 8, chunk.NT )
            self.assertAlmostEqual( 3., chunk.RTYP )
            self.assertAlmostEqual( 3., chunk.decay_chain )
            self.assertAlmostEqual( 4.863000e+4, chunk.ER[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.ER[1] )
            self.assertAlmostEqual( 4.863000e+4, chunk.discrete_energy[0] )
            self.assertAlmostEqual( 5.000000e+1, chunk.discrete_energy[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.RI[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.RI[1] )
            self.assertAlmostEqual( 1.420112e-6, chunk.relative_intensity[0] )
            self.assertAlmostEqual( 2.85306e-10, chunk.relative_intensity[1] )
            self.assertAlmostEqual( 1., chunk.TYPE )
            self.assertAlmostEqual( 1., chunk.type )
            self.assertAlmostEqual( 1.0, chunk.RIS[0] )
            self.assertAlmostEqual( 2.0, chunk.RIS[1] )
            self.assertAlmostEqual( 1.0, chunk.internal_pair_formation_coefficient[0] )
            self.assertAlmostEqual( 2.0, chunk.internal_pair_formation_coefficient[1] )
            self.assertAlmostEqual( 7.010000e+5, chunk.RICC[0] )
            self.assertAlmostEqual( 1.106180e-2, chunk.RICC[1] )
            self.assertAlmostEqual( 7.010000e+5, chunk.total_internal_conversion_coefficient[0] )
            self.assertAlmostEqual( 1.106180e-2, chunk.total_internal_conversion_coefficient[1] )
            self.assertAlmostEqual( 0.0, chunk.RICK[0] )
            self.assertAlmostEqual( 0.0, chunk.RICK[1] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_k_shell[0] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_k_shell[1] )
            self.assertAlmostEqual( 0.0, chunk.RICL[0] )
            self.assertAlmostEqual( 0.0, chunk.RICL[1] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_l_shell[0] )
            self.assertAlmostEqual( 0.0, chunk.internal_conversion_coefficient_l_shell[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_styp_8, chunk.to_string( 3580, 8, 457 ) )

        # the data is given explicitly
        chunk = DiscreteSpectrum( energy = [ 4.863000e+4, 5.000000e+1 ],
                                  chain = 3., type = 0.,
                                  intensity = [ 1.420112e-6, 2.85306e-10 ] )

        verify_chunk_styp_not_0_1( self, chunk )

        # the data is read from a string
        chunk = DiscreteSpectrum.from_string( self.chunk_styp_not_0_1, 3580, 8, 457 )

        verify_chunk_styp_not_0_1( self, chunk )

        # the data is copied
        copy = DiscreteSpectrum( chunk )

        verify_chunk_styp_not_0_1( self, copy )

        # the data is given explicitly
        chunk = DiscreteSpectrum( energy = [ 4.863000e+4, 5.000000e+1 ],
                                  chain = 3., type = 0.,
                                  intensity = [ 1.420112e-6, 2.85306e-10 ],
                                  ris = [ 1.0, 2.0 ] )

        verify_chunk_styp_2( self, chunk )

        # the data is read from a string
        chunk = DiscreteSpectrum.from_string( self.chunk_styp_2, 3580, 8, 457 )

        verify_chunk_styp_2( self, chunk )

        # the data is copied
        copy = DiscreteSpectrum( chunk )

        verify_chunk_styp_2( self, copy )

        # the data is given explicitly
        chunk = DiscreteSpectrum( energy = [ 4.863000e+4, 5.000000e+1 ],
                                  chain = 3., type = 0.,
                                  intensity = [ 1.420112e-6, 2.85306e-10 ],
                                  ris = [ 1.0, 2.0 ],
                                  ricc = [ 7.010000e+5, 1.106180e-2 ],
                                  rick = [ 1.378999e-1, 2.000000e-3 ],
                                  ricl = [ 3.315735e+5, 5.608008e+3 ] )

        verify_chunk_styp_0( self, chunk )

        # the data is read from a string
        chunk = DiscreteSpectrum.from_string( self.chunk_styp_0, 3580, 8, 457 )

        verify_chunk_styp_0( self, chunk )

        # the data is copied
        copy = DiscreteSpectrum( chunk )

        verify_chunk_styp_0( self, copy )

        # the data is given explicitly
        chunk = DiscreteSpectrum( energy = [ 4.863000e+4, 5.000000e+1 ],
                                  chain = 3., type = 1.,
                                  intensity = [ 1.420112e-6, 2.85306e-10 ],
                                  ris = [ 1.0, 2.0 ],
                                  ricc = [ 7.010000e+5, 1.106180e-2 ] )

        verify_chunk_styp_8( self, chunk )

        # the data is read from a string
        chunk = DiscreteSpectrum.from_string( self.chunk_styp_8, 3580, 8, 457 )

        verify_chunk_styp_8( self, chunk )

        # the data is copied
        copy = DiscreteSpectrum( chunk )

        verify_chunk_styp_8( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = DiscreteSpectrum.from_string( self.invalid, 3580, 8, 457 )

if __name__ == '__main__' :

    unittest.main()
