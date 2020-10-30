# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import AverageDecayEnergies

class Test_ENDFtk_MF8_MT457_AverageDecayEnergies( unittest.TestCase ) :
    """Unit test for the AverageDecayEnergies class."""

    chunk = ( ' 4.449622+9 6.311520+7          0          0          6          03580 8457     \n'
              ' 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n' )

    chunk_stable = ( ' 0.000000+0 0.000000+0          0          0          6          03580 8457     \n'
                     ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n' )


    invalid = ( ' 4.449622+9 6.311520+7          0          0          8          03580 8457     \n'
                ' 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n'
                ' 1.000000+0 2.000000+1                                            3580 8457     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 4.449622e+9, chunk.T[0] )
            self.assertAlmostEqual( 6.311520e+7, chunk.T[1] )
            self.assertAlmostEqual( 4.449622e+9, chunk.half_life[0] )
            self.assertAlmostEqual( 6.311520e+7, chunk.half_life[1] )

            self.assertEqual( 3, chunk.NCE )
            self.assertEqual( 3, chunk.number_decay_energies )
            self.assertEqual( 3, len( chunk.E ) )
            self.assertEqual( 3, len( chunk.decay_energies ) )
            self.assertAlmostEqual( 4.008322e+4, chunk.E[0][0] )
            self.assertAlmostEqual( 4.128931e+3, chunk.E[0][1] )
            self.assertAlmostEqual( 5.373671e+3, chunk.E[1][0] )
            self.assertAlmostEqual( 3.660206e+2, chunk.E[1][1] )
            self.assertAlmostEqual( 2.441003e+4, chunk.E[2][0] )
            self.assertAlmostEqual( 6.191754e+2, chunk.E[2][1] )
            self.assertAlmostEqual( 4.008322e+4, chunk.decay_energies[0][0] )
            self.assertAlmostEqual( 4.128931e+3, chunk.decay_energies[0][1] )
            self.assertAlmostEqual( 5.373671e+3, chunk.decay_energies[1][0] )
            self.assertAlmostEqual( 3.660206e+2, chunk.decay_energies[1][1] )
            self.assertAlmostEqual( 2.441003e+4, chunk.decay_energies[2][0] )
            self.assertAlmostEqual( 6.191754e+2, chunk.decay_energies[2][1] )

            self.assertAlmostEqual( 4.008322e+4, chunk.ELP[0] )
            self.assertAlmostEqual( 4.128931e+3, chunk.ELP[1] )
            self.assertAlmostEqual( 4.008322e+4, chunk.light_particle_decay_energy[0] )
            self.assertAlmostEqual( 4.128931e+3, chunk.light_particle_decay_energy[1] )
            self.assertAlmostEqual( 5.373671e+3, chunk.EEM[0] )
            self.assertAlmostEqual( 3.660206e+2, chunk.EEM[1] )
            self.assertAlmostEqual( 5.373671e+3, chunk.electromagnetic_decay_energy[0] )
            self.assertAlmostEqual( 3.660206e+2, chunk.electromagnetic_decay_energy[1] )
            self.assertAlmostEqual( 2.441003e+4, chunk.EHP[0] )
            self.assertAlmostEqual( 6.191754e+2, chunk.EHP[1] )
            self.assertAlmostEqual( 2.441003e+4, chunk.heavy_particle_decay_energy[0] )
            self.assertAlmostEqual( 6.191754e+2, chunk.heavy_particle_decay_energy[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 3580, 8, 457 ) )

        def verify_chunk_stable( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.0, chunk.T[0] )
            self.assertAlmostEqual( 0.0, chunk.T[1] )
            self.assertAlmostEqual( 0.0, chunk.half_life[0] )
            self.assertAlmostEqual( 0.0, chunk.half_life[1] )

            self.assertEqual( 3, chunk.NCE )
            self.assertEqual( 3, chunk.number_decay_energies )
            self.assertEqual( 3, len( chunk.E ) )
            self.assertEqual( 3, len( chunk.decay_energies ) )

            self.assertAlmostEqual( 0.0, chunk.E[0][0] )
            self.assertAlmostEqual( 0.0, chunk.E[0][1] )
            self.assertAlmostEqual( 0.0, chunk.E[1][0] )
            self.assertAlmostEqual( 0.0, chunk.E[1][1] )
            self.assertAlmostEqual( 0.0, chunk.E[2][0] )
            self.assertAlmostEqual( 0.0, chunk.E[2][1] )
            self.assertAlmostEqual( 0.0, chunk.decay_energies[0][0] )
            self.assertAlmostEqual( 0.0, chunk.decay_energies[0][1] )
            self.assertAlmostEqual( 0.0, chunk.decay_energies[1][0] )
            self.assertAlmostEqual( 0.0, chunk.decay_energies[1][1] )
            self.assertAlmostEqual( 0.0, chunk.decay_energies[2][0] )
            self.assertAlmostEqual( 0.0, chunk.decay_energies[2][1] )

            self.assertAlmostEqual( 0.0, chunk.ELP[0] )
            self.assertAlmostEqual( 0.0, chunk.ELP[1] )
            self.assertAlmostEqual( 0.0, chunk.light_particle_decay_energy[0] )
            self.assertAlmostEqual( 0.0, chunk.light_particle_decay_energy[1] )
            self.assertAlmostEqual( 0.0, chunk.EEM[0] )
            self.assertAlmostEqual( 0.0, chunk.EEM[1] )
            self.assertAlmostEqual( 0.0, chunk.electromagnetic_decay_energy[0] )
            self.assertAlmostEqual( 0.0, chunk.electromagnetic_decay_energy[1] )
            self.assertAlmostEqual( 0.0, chunk.EHP[0] )
            self.assertAlmostEqual( 0.0, chunk.EHP[1] )
            self.assertAlmostEqual( 0.0, chunk.heavy_particle_decay_energy[0] )
            self.assertAlmostEqual( 0.0, chunk.heavy_particle_decay_energy[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_stable, chunk.to_string( 3580, 8, 457 ) )

        # the data is given explicitly
        chunk = AverageDecayEnergies( halflife = [ 4.449622e+9, 6.311520e+7 ],
                                      energies =  [ [ 4.008322e+4, 4.128931e+3 ],
                                                    [ 5.373671e+3, 3.660206e+2 ],
                                                    [ 2.441003e+4, 6.191754e+2 ] ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = AverageDecayEnergies.from_string( self.chunk, 3580, 8, 457 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = AverageDecayEnergies( chunk )

        verify_chunk( self, copy )

        # the data is given explicitly
        chunk = AverageDecayEnergies()

        verify_chunk_stable( self, chunk )

        # the data is read from a string
        chunk = AverageDecayEnergies.from_string( self.chunk_stable, 3580, 8, 457 )

        verify_chunk_stable( self, chunk )

        # the data is copied
        copy = AverageDecayEnergies( chunk )

        verify_chunk_stable( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # inconsistent data
        with self.assertRaises( Exception ) :

            chunk = AverageDecayEnergies( halflife = [ 4.449622e+9, 6.311520e+7 ],
                                          energies =  [ [ 4.008322e+4, 4.128931e+3 ],
                                                        [ 5.373671e+3, 3.660206e+2 ],
                                                        [ 2.441003e+4, 6.191754e+2 ],
                                                        [ 1., 2. ] ] )

        with self.assertRaises( Exception ) :

            chunk = AverageDecayEnergies.from_string( self.invalid, 27, 7, 4 )

if __name__ == '__main__' :

    unittest.main()
