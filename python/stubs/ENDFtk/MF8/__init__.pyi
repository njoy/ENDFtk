"""
MF8 - radioactive decay and fission product yield data
"""
from __future__ import annotations
import pybind11_stubgen.typing_ext
import typing
from . import MT454
from . import MT457
from . import MT459
__all__: list[str] = ['File', 'FissionYieldData', 'MT454', 'MT457', 'MT459']
class File:
    """
    MF8 file - radioactive decay and fission product yield data
    """
    @staticmethod
    def from_string(file: str) -> File:
        """
        Read the file from a string
        
        An exception is raised if something goes wrong while reading the
        file
        
        Arguments:
            file    the string representing the file
        """
    def MT(self, mt: int) -> MT454.Section | MT457.Section | MT459.Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, decay: MT457.Section) -> None:
        """
        Initialise the file with radioactive decay data
        
        Arguments:
            self    the file
            decay   the decay data (MT457)
        """
    @typing.overload
    def __init__(self, direct: MT454.Section) -> None:
        """
        Initialise the file with direct fission yield data
        
        Arguments:
            self     the file
            direct   the direct fission yield data (MT454)
        """
    @typing.overload
    def __init__(self, cumulative: MT459.Section) -> None:
        """
        Initialise the file with cumulative fission yield data
        
        Arguments:
            self         the file
            cumulative   the cumulative fission yield data (MT459)
        """
    @typing.overload
    def __init__(self, direct: MT454.Section, cumulative: MT459.Section) -> None:
        """
        Initialise the file with direct and cumulative fission yield data
        
        Arguments:
            self         the file
            direct       the direct fission yield data (MT454)
            cumulative   the cumulative fission yield data (MT459)
        """
    @typing.overload
    def __init__(self, sections: list[MT454.Section | MT457.Section | MT459.Section]) -> None:
        """
        Initialise the file
        
        Arguments:
            self       the file
            sections   the sections to be put into the file
        """
    @typing.overload
    def __init__(self, file: File) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def has_MT(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def section(self, mt: int) -> MT454.Section | MT457.Section | MT459.Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    def to_string(self, mat: int) -> str:
        """
        The string representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def MTs(self) -> ...:
        """
        The sections defined in the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def sections(self) -> ...:
        """
        The sections defined in the file
        """
class FissionYieldData:
    """
    MF8 component - fission yield data for a specific incident energy (or 
                    energy independent yields)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> FissionYieldData:
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
    def __init__(self, identifiers: list[int], states: list[int], yields: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]], energy: float = 0.0, interpolation: int = 0) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            identifiers     the fission product identifiers (ZA identifier)
            states          the isomeric state for each fission product
            yields          the fission yield values and uncertainties
            energy          the incident neutron energy (equal to zero for
                            energy independent yields)
            interpolation   the interpolation type (equal to zero for
                            energy independent yields)
        """
    @typing.overload
    def __init__(self, component: FissionYieldData) -> None:
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
    def DFY(self) -> ...:
        """
        The fission yield uncertainties
        """
    @property
    def E(self) -> float:
        """
        The incident energy value
        """
    @property
    def FPS(self) -> ...:
        """
        The fission product isomeric states
        """
    @property
    def FY(self) -> ...:
        """
        The fission yield values
        """
    @property
    def I(self) -> int:
        """
        The interpolation type (or LE value)
        """
    @property
    def LE(self) -> bool:
        """
        Whether or not the fission yield data is energy independent
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NFP(self) -> int:
        """
        The number of fission products
        """
    @property
    def Y(self) -> ...:
        """
        The fission yield values and uncertainties
        """
    @property
    def ZAFP(self) -> ...:
        """
        The fission product ZA identifiers
        """
    @property
    def fission_product_identifiers(self) -> ...:
        """
        The fission product ZA identifiers
        """
    @property
    def fission_yield_uncertainties(self) -> ...:
        """
        The fission yield uncertainties
        """
    @property
    def fission_yield_values(self) -> ...:
        """
        The fission yield values
        """
    @property
    def fission_yields(self) -> ...:
        """
        The fission yield values and uncertainties
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def interpolation_type(self) -> int:
        """
        The interpolation type (or LE value)
        """
    @property
    def is_energy_independent(self) -> bool:
        """
        Whether or not the fission yield data is energy independent
        """
    @property
    def isomeric_states(self) -> ...:
        """
        The fission product isomeric states
        """
    @property
    def number_fission_products(self) -> int:
        """
        The number of fission products
        """
