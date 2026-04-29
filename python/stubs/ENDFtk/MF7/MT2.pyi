"""
MT2 - coherent and incoherent elastic scattering
"""
from __future__ import annotations
import typing
__all__: list[str] = ['CoherentElastic', 'IncoherentElastic', 'MixedElastic', 'Section']
class CoherentElastic:
    """
    MF7 MT2 section - coherent elastic scattering
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CoherentElastic:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], temperatures: list[float], li: list[int], energies: list[float], s: list[list[float]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries for S(E)
            interpolants    the interpolation types for each range
            temperatures    the temperatures (NT values)
            li              the temperature interpolation flags (NT-1 values)
            energies        the energy values (NP values)
            s               the thermal scattering values (NT arrays of NP values)
        """
    @typing.overload
    def __init__(self, temperature: float, boundaries: list[int], interpolants: list[int], energies: list[float], s: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            temperature     the temperature
            boundaries      the interpolation range boundaries for S(E)
            interpolants    the interpolation types for each range
            energies        the energy values (NP values)
            s               the thermal scattering values (NP values)
        """
    @typing.overload
    def __init__(self, component: CoherentElastic) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LI(self) -> ...:
        """
        The temperature interpolation flags (LT values will be given)
        """
    @property
    def LT(self) -> int:
        """
        The LT flag indicating the temperature dependence (equal to NT - 1)
        """
    @property
    def LTHR(self) -> int:
        """
        The LTHR flag (coherent, incoherent or mixed elastic scattering)
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The number of points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NT(self) -> int:
        """
        The number of temperatures
        """
    @property
    def S(self) -> ...:
        """
        The thermal scattering law values as an array, one for each temperature
        """
    @property
    def T(self) -> ...:
        """
        The temperature values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def elastic_scattering_type(self) -> int:
        """
        The LTHR flag (coherent, incoherent or mixed elastic scattering)
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_bragg_edges(self) -> int:
        """
        The number of Bragg edges, equal to the number of energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def number_temperatures(self) -> int:
        """
        The number of temperatures
        """
    @property
    def temperature_dependence_flag(self) -> int:
        """
        The LT flag indicating the temperature dependence (equal to NT - 1)
        """
    @property
    def temperature_interpolants(self) -> ...:
        """
        The temperature interpolation flags (LT values will be given)
        """
    @property
    def temperatures(self) -> ...:
        """
        The temperature values
        """
    @property
    def thermal_scattering_values(self) -> ...:
        """
        The thermal scattering law values as an array, one for each temperature
        """
class IncoherentElastic:
    """
    MF7 MT2 section - incoherent elastic scattering
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> IncoherentElastic:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, sb: float, boundaries: list[int], interpolants: list[int], temperatures: list[float], integrals: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            sb              the characteristic bound cross section
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            temperatures    the temperature values
            integrals       the values of the Debye-Waller integral divided by
                            the atomic mass (expressed in eV^-1)
        """
    @typing.overload
    def __init__(self, component: IncoherentElastic) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LTHR(self) -> int:
        """
        The LTHR flag (coherent, incoherent or mixed elastic scattering)
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The number of points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NT(self) -> int:
        """
        The number of temperatures
        """
    @property
    def SB(self) -> float:
        """
        The characteristic bound cross section (barns)
        """
    @property
    def T(self) -> ...:
        """
        The temperature values
        """
    @property
    def W(self) -> ...:
        """
        The Debye-Waller integral divided by the atomic mass (eV^-1)
        """
    @property
    def bound_cross_section(self) -> float:
        """
        The characteristic bound cross section (barns)
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def debye_waller_values(self) -> ...:
        """
        The Debye-Waller integral divided by the atomic mass (eV^-1)
        """
    @property
    def elastic_scattering_type(self) -> int:
        """
        The LTHR flag (coherent, incoherent or mixed elastic scattering)
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def number_temperatures(self) -> int:
        """
        The number of temperatures
        """
    @property
    def temperatures(self) -> ...:
        """
        The temperature values
        """
class MixedElastic:
    """
    MF7 MT2 section - mixed coherent and incoherent elastic scattering
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> MixedElastic:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, coherent: CoherentElastic, incoherent: IncoherentElastic) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            coherent      the coherent elastic data
            incoherent    the incoherent elastic data
        """
    @typing.overload
    def __init__(self, component: MixedElastic) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def LTHR(self) -> int:
        """
        The LTHR flag (coherent, incoherent or mixed elastic scattering)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def coherent(self) -> CoherentElastic:
        """
        The coherent elastic scattering data
        """
    @property
    def elastic_scattering_type(self) -> int:
        """
        The LTHR flag (coherent, incoherent or mixed elastic scattering)
        """
    @property
    def incoherent(self) -> IncoherentElastic:
        """
        The incoherent elastic scattering data
        """
class Section:
    """
    MF7 MT2 section - coherent and incoherent elastic scattering
    """
    @staticmethod
    def from_string(section: str) -> Section:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, law: CoherentElastic | IncoherentElastic | MixedElastic) -> None:
        """
        Initialise the section using isotopes
        
        Arguments:
            self    the section
            zaid    the ZA value of the material
            awr     the atomic weight ratio
            law     the thermal scattering law
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def LTHR(self) -> int:
        """
        The LTHR flag (coherent or incoherent elastic scattering)
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def elastic_scattering_type(self) -> int:
        """
        The LTHR flag (coherent or incoherent elastic scattering)
        """
    @property
    def scattering_law(self) -> CoherentElastic | IncoherentElastic | MixedElastic:
        """
        The LTHR flag (coherent or incoherent elastic scattering)
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
