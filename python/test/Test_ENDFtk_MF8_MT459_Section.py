# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT459 import Section
from ENDFtk.MF8 import FissionYieldData
from ENDFtk.tree import Tape

class Test_ENDFtk_MF8_MT457_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.223500+4 2.330250+2          2          0          0          09228 8459     \n'
              ' 2.530000-2 0.000000+0          1          0         12          39228 8459     \n'
              ' 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8459     \n'
              ' 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8459     \n'
              ' 5.000000+5 0.000000+0          3          0         12          39228 8459     \n'
              ' 2.306600+4 0.000000+0 4.48456-18 2.87012-18 5.413500+4 0.000000+09228 8459     \n'
              ' 1.196100-3 2.751030-4 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8459     \n' )

    chunk_energy_independent = ( ' 9.223500+4 2.330250+2          1          0          0          09228 8459     \n'
                                 ' 0.000000+0 0.000000+0          0          0         12          39228 8459     \n'
                                 ' 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8459     \n'
                                 ' 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8459     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 8  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 8457     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 459, chunk.MT )
            self.assertEqual( 459, chunk.section_number )

            self.assertAlmostEqual( 92235., chunk.ZA )
            self.assertAlmostEqual( 233.0250, chunk.AWR )
            self.assertAlmostEqual( 233.0250, chunk.atomic_weight_ratio )

            self.assertEqual( False, chunk.LE )
            self.assertEqual( False, chunk.is_energy_independent )

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 0.0253, chunk.E[0] )
            self.assertAlmostEqual( 500e+3, chunk.E[1] )
            self.assertAlmostEqual( 0.0253, chunk.incident_energies[0] )
            self.assertAlmostEqual( 500e+3, chunk.incident_energies[1] )

            self.assertEqual( 2, len( chunk.yields ) )

            data = chunk.yields[0]
            self.assertEqual( 1, data.I )
            self.assertEqual( 1, data.interpolation_type )
            self.assertEqual( False, data.LE )
            self.assertEqual( False, data.is_energy_independent )
            self.assertEqual( 3, data.NFP )
            self.assertEqual( 3, data.number_fission_products )
            self.assertAlmostEqual( 0.0253, data.E )
            self.assertAlmostEqual( 0.0253, data.incident_energy )

            self.assertEqual( 3, len( data.ZAFP ) )
            self.assertEqual( 3, len( data.fission_product_identifiers ) )
            self.assertEqual( 3, len( data.FPS ) )
            self.assertEqual( 3, len( data.isomeric_states ) )
            self.assertEqual( 3, len( data.Y ) )
            self.assertEqual( 3, len( data.fission_yields ) )
            self.assertEqual( 23066, data.ZAFP[0] );
            self.assertEqual( 54135, data.ZAFP[1] );
            self.assertEqual( 72171, data.ZAFP[2] );
            self.assertEqual( 23066, data.fission_product_identifiers[0] );
            self.assertEqual( 54135, data.fission_product_identifiers[1] );
            self.assertEqual( 72171, data.fission_product_identifiers[2] );
            self.assertEqual( 0, data.FPS[0] );
            self.assertEqual( 0, data.FPS[1] );
            self.assertEqual( 0, data.FPS[2] );
            self.assertEqual( 0, data.isomeric_states[0] );
            self.assertEqual( 0, data.isomeric_states[1] );
            self.assertEqual( 0, data.isomeric_states[2] );
            self.assertEqual( 2, len( data.Y[0] ) )
            self.assertEqual( 2, len( data.Y[1] ) )
            self.assertEqual( 2, len( data.Y[2] ) )
            self.assertEqual( 2, len( data.fission_yields[0] ) )
            self.assertEqual( 2, len( data.fission_yields[1] ) )
            self.assertEqual( 2, len( data.fission_yields[2] ) )
            self.assertAlmostEqual( 2.05032e-19, data.Y[0][0] )
            self.assertAlmostEqual( 1.31220e-19, data.Y[0][1] )
            self.assertAlmostEqual( 7.851250e-4, data.Y[1][0] )
            self.assertAlmostEqual( 4.710750e-5, data.Y[1][1] )
            self.assertAlmostEqual( 0, data.Y[2][0] )
            self.assertAlmostEqual( 0, data.Y[2][1] )
            self.assertAlmostEqual( 2.05032e-19, data.fission_yields[0][0] )
            self.assertAlmostEqual( 1.31220e-19, data.fission_yields[0][1] )
            self.assertAlmostEqual( 7.851250e-4, data.fission_yields[1][0] )
            self.assertAlmostEqual( 4.710750e-5, data.fission_yields[1][1] )
            self.assertAlmostEqual( 0, data.fission_yields[2][0] )
            self.assertAlmostEqual( 0, data.fission_yields[2][1] )

            data = chunk.yields[1]
            self.assertEqual( 3, data.I )
            self.assertEqual( 3, data.interpolation_type )
            self.assertEqual( False, data.LE )
            self.assertEqual( False, data.is_energy_independent )
            self.assertEqual( 3, data.NFP )
            self.assertEqual( 3, data.number_fission_products )
            self.assertAlmostEqual( 500e+3, data.E )
            self.assertAlmostEqual( 500e+3, data.incident_energy )

            self.assertEqual( 3, len( data.ZAFP ) )
            self.assertEqual( 3, len( data.fission_product_identifiers ) )
            self.assertEqual( 3, len( data.FPS ) )
            self.assertEqual( 3, len( data.isomeric_states ) )
            self.assertEqual( 3, len( data.Y ) )
            self.assertEqual( 3, len( data.fission_yields ) )
            self.assertEqual( 23066, data.ZAFP[0] );
            self.assertEqual( 54135, data.ZAFP[1] );
            self.assertEqual( 72171, data.ZAFP[2] );
            self.assertEqual( 23066, data.fission_product_identifiers[0] );
            self.assertEqual( 54135, data.fission_product_identifiers[1] );
            self.assertEqual( 72171, data.fission_product_identifiers[2] );
            self.assertEqual( 0, data.FPS[0] );
            self.assertEqual( 0, data.FPS[1] );
            self.assertEqual( 0, data.FPS[2] );
            self.assertEqual( 0, data.isomeric_states[0] );
            self.assertEqual( 0, data.isomeric_states[1] );
            self.assertEqual( 0, data.isomeric_states[2] );
            self.assertEqual( 2, len( data.Y[0] ) )
            self.assertEqual( 2, len( data.Y[1] ) )
            self.assertEqual( 2, len( data.Y[2] ) )
            self.assertEqual( 2, len( data.fission_yields[0] ) )
            self.assertEqual( 2, len( data.fission_yields[1] ) )
            self.assertEqual( 2, len( data.fission_yields[2] ) )
            self.assertAlmostEqual( 4.48456e-18, data.Y[0][0] )
            self.assertAlmostEqual( 2.87012e-18, data.Y[0][1] )
            self.assertAlmostEqual( 1.196100e-3, data.Y[1][0] )
            self.assertAlmostEqual( 2.751030e-4, data.Y[1][1] )
            self.assertAlmostEqual( 0, data.Y[2][0] )
            self.assertAlmostEqual( 0, data.Y[2][1] )
            self.assertAlmostEqual( 4.48456e-18, data.fission_yields[0][0] )
            self.assertAlmostEqual( 2.87012e-18, data.fission_yields[0][1] )
            self.assertAlmostEqual( 1.196100e-3, data.fission_yields[1][0] )
            self.assertAlmostEqual( 2.751030e-4, data.fission_yields[1][1] )
            self.assertAlmostEqual( 0, data.fission_yields[2][0] )
            self.assertAlmostEqual( 0, data.fission_yields[2][1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9228, 8 ) )

        def verify_chunk_energy_independent( self, chunk ) :

            self.assertEqual( 459, chunk.MT )
            self.assertEqual( 459, chunk.section_number )

            self.assertAlmostEqual( 92235., chunk.ZA )
            self.assertAlmostEqual( 233.0250, chunk.AWR )
            self.assertAlmostEqual( 233.0250, chunk.atomic_weight_ratio )

            self.assertEqual( True, chunk.LE )
            self.assertEqual( True, chunk.is_energy_independent )

            self.assertEqual( 1, len( chunk.E ) )
            self.assertEqual( 1, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 0., chunk.E[0] )
            self.assertAlmostEqual( 0., chunk.incident_energies[0] )

            self.assertEqual( 1, len( chunk.yields ) )

            data = chunk.yields[0]
            self.assertEqual( 0, data.I )
            self.assertEqual( 0, data.interpolation_type )
            self.assertEqual( True, data.LE )
            self.assertEqual( True, data.is_energy_independent )
            self.assertEqual( 3, data.NFP )
            self.assertEqual( 3, data.number_fission_products )
            self.assertEqual( 0., data.E )
            self.assertEqual( 0., data.incident_energy )

            self.assertEqual( 3, len( data.ZAFP ) )
            self.assertEqual( 3, len( data.fission_product_identifiers ) )
            self.assertEqual( 3, len( data.FPS ) )
            self.assertEqual( 3, len( data.isomeric_states ) )
            self.assertEqual( 3, len( data.Y ) )
            self.assertEqual( 3, len( data.fission_yields ) )
            self.assertEqual( 23066, data.ZAFP[0] );
            self.assertEqual( 54135, data.ZAFP[1] );
            self.assertEqual( 72171, data.ZAFP[2] );
            self.assertEqual( 23066, data.fission_product_identifiers[0] );
            self.assertEqual( 54135, data.fission_product_identifiers[1] );
            self.assertEqual( 72171, data.fission_product_identifiers[2] );
            self.assertEqual( 0, data.FPS[0] );
            self.assertEqual( 0, data.FPS[1] );
            self.assertEqual( 0, data.FPS[2] );
            self.assertEqual( 0, data.isomeric_states[0] );
            self.assertEqual( 0, data.isomeric_states[1] );
            self.assertEqual( 0, data.isomeric_states[2] );
            self.assertEqual( 2, len( data.Y[0] ) )
            self.assertEqual( 2, len( data.Y[1] ) )
            self.assertEqual( 2, len( data.Y[2] ) )
            self.assertEqual( 2, len( data.fission_yields[0] ) )
            self.assertEqual( 2, len( data.fission_yields[1] ) )
            self.assertEqual( 2, len( data.fission_yields[2] ) )
            self.assertAlmostEqual( 2.05032e-19, data.Y[0][0] )
            self.assertAlmostEqual( 1.31220e-19, data.Y[0][1] )
            self.assertAlmostEqual( 7.851250e-4, data.Y[1][0] )
            self.assertAlmostEqual( 4.710750e-5, data.Y[1][1] )
            self.assertAlmostEqual( 0, data.Y[2][0] )
            self.assertAlmostEqual( 0, data.Y[2][1] )
            self.assertAlmostEqual( 2.05032e-19, data.fission_yields[0][0] )
            self.assertAlmostEqual( 1.31220e-19, data.fission_yields[0][1] )
            self.assertAlmostEqual( 7.851250e-4, data.fission_yields[1][0] )
            self.assertAlmostEqual( 4.710750e-5, data.fission_yields[1][1] )
            self.assertAlmostEqual( 0, data.fission_yields[2][0] )
            self.assertAlmostEqual( 0, data.fission_yields[2][1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_energy_independent + self.valid_SEND,
                              chunk.to_string( 9228, 8 ) )

        # the data is given explicitly
        chunk = Section( zaid = 92235., awr = 233.0250,
                         identifiers = [ 23066, 54135, 72171 ],
                         states = [ 0, 0, 0 ],
                         energies = [ 0.0253, 500e+3 ],
                         interpolants = [ 3 ],
                         yields = [ [ [ 2.05032e-19, 1.31220e-19 ], [ 4.48456e-18, 2.87012e-18 ] ],
                                    [ [ 7.851250e-4, 4.710750e-5 ], [ 1.196100e-3, 2.751030e-4 ] ],
                                    [ [ 0, 0 ], [ 0, 0 ] ] ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 8 ).section( 459 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

        # the data is given explicitly as a FissionYieldData array
        chunk = Section( zaid = 92235., awr = 233.0250,
                         yields = [ FissionYieldData( [ 23066, 54135, 72171 ], [ 0, 0, 0 ],
                                                      [ [ 2.05032e-19, 1.31220e-19 ],
                                                        [ 7.851250e-4, 4.710750e-5 ],
                                                        [ 0, 0 ] ],
                                                      0.0253, 1 ),
                                    FissionYieldData( [ 23066, 54135, 72171 ], [ 0, 0, 0 ],
                                                      [ [ 4.48456e-18, 2.87012e-18 ],
                                                        [ 1.196100e-3, 2.751030e-4 ],
                                                        [ 0, 0 ] ],
                                                      500e+3, 3 ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 8 ).section( 459 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

        # the data is given explicitly for energy independent yields
        chunk = Section( zaid = 92235., awr = 233.0250,
                         identifiers = [ 23066, 54135, 72171 ],
                         states = [ 0, 0, 0 ],
                         yields = [ [ 2.05032e-19, 1.31220e-19 ],
                                    [ 7.851250e-4, 4.710750e-5 ],
                                    [ 0, 0 ] ] )

        verify_chunk_energy_independent( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_energy_independent + self.valid_SEND )

        verify_chunk_energy_independent( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_energy_independent +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 8 ).section( 459 ).parse()

        verify_chunk_energy_independent( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_energy_independent( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
