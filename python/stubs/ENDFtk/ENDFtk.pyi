from __future__ import annotations
import typing
from . import MF1
from . import MF10
from . import MF12
from . import MF13
from . import MF14
from . import MF15
from . import MF16
from . import MF2
from . import MF23
from . import MF26
from . import MF27
from . import MF28
from . import MF3
from . import MF31
from . import MF32
from . import MF33
from . import MF34
from . import MF35
from . import MF4
from . import MF40
from . import MF5
from . import MF6
from . import MF7
from . import MF8
from . import MF9
from . import sequence
from . import tree
__all__: list[str] = ['ControlRecord', 'CovariancePairs', 'DerivedRatioToStandard', 'DerivedRedundant', 'DirectoryRecord', 'InterpolationRecord', 'ListRecord', 'MF1', 'MF10', 'MF12', 'MF13', 'MF14', 'MF15', 'MF16', 'MF2', 'MF23', 'MF26', 'MF27', 'MF28', 'MF3', 'MF31', 'MF32', 'MF33', 'MF34', 'MF35', 'MF4', 'MF40', 'MF5', 'MF6', 'MF7', 'MF8', 'MF9', 'Material', 'ReactionBlock', 'RectangularMatrix', 'SquareMatrix', 'TabulationRecord', 'TapeIdentification', 'sequence', 'tree']
class ControlRecord:
    """
    ENDF CONT record
    
    The control record is a single line record consisting of 2 doubles and
    4 integer values.
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ControlRecord:
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
    def __init__(self, C1: float, C2: float, L1: int, L2: int, N1: int, N2: int) -> None:
        """
        Initialise the record
        
        Arguments:
            self   the record
            C1     the double in column 1
            C2     the double in column 2
            L1     the integer in column 3
            L2     the integer in column 4
            N1     the integer in column 5
            N2     the integer in column 6
        """
    @typing.overload
    def __init__(self, record: ControlRecord) -> None:
        """
        Initialise the record with another record
        
        Arguments:
            self      the record
            record    the record to be copied
        """
    @typing.overload
    def __init__(self, component: ControlRecord) -> None:
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
    def C1(self) -> float:
        """
        The double in column 1
        """
    @property
    def C2(self) -> float:
        """
        The double in column 2
        """
    @property
    def L1(self) -> int:
        """
        The integer in column 3
        """
    @property
    def L2(self) -> int:
        """
        The integer in column 4
        """
    @property
    def N1(self) -> int:
        """
        The integer in column 5
        """
    @property
    def N2(self) -> int:
        """
        The integer in column 6
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
class CovariancePairs:
    """
    Covariance component - NI-type sub-subsection with {{E,F}} pairs
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CovariancePairs:
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
    def __init__(self, lb: int, energies: list[float], fvalues: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            lb             covariance procedure
            energies       energies
            fvalues        F-values
        """
    @typing.overload
    def __init__(self, lb: int, ek: list[float], fk: list[float], el: list[float], fl: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            lb             covariance procedure
            ek             first array energies
            fk             first array F-values
            el             second array energies
            fl             second array F-values
        """
    @typing.overload
    def __init__(self, component: CovariancePairs) -> None:
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
    def EK(self) -> ...:
        """
        The energy values from the first array
        """
    @property
    def EL(self) -> ...:
        """
        The energy values from the second array
        """
    @property
    def FK(self) -> ...:
        """
        The F values from the first array
        """
    @property
    def FL(self) -> ...:
        """
        The F values from the second array
        """
    @property
    def LB(self) -> int:
        """
        The procedure
        """
    @property
    def LT(self) -> int:
        """
        The number of pairs in the second array
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The total number of pairs
        """
    @property
    def NT(self) -> int:
        """
        The number of values in this component
        """
    @property
    def first_array_energies(self) -> ...:
        """
        The F values from the first array
        """
    @property
    def first_array_fvalues(self) -> ...:
        """
        The F values from the first array
        """
    @property
    def number_pairs(self) -> int:
        """
        The total number of pairs
        """
    @property
    def number_second_pairs(self) -> int:
        """
        The number of pairs in the second array
        """
    @property
    def number_values(self) -> int:
        """
        The number of values in this component
        """
    @property
    def procedure(self) -> int:
        """
        The procedure
        """
    @property
    def second_array_energies(self) -> ...:
        """
        The F values from the second array
        """
    @property
    def second_array_fvalues(self) -> ...:
        """
        The F values from the second array
        """
class DerivedRatioToStandard:
    """
    Covariance component - NC-type sub-subsection for ratios to standards
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DerivedRatioToStandard:
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
    def __init__(self, lty: int, e1: float, e2: float, mats: int, mts: int, xmfs: float, xlfss: float, energies: list[float], weights: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            lty            covariance procedure
            e1             lower energy
            e2             upper energy
            mats           standard's material number
            mts            standard's MT number
            xmfs           standard's MF number
            xlfss          standard's final excited state
            energies       energy boundaries of intervals
            weights        weights of energies
        """
    @typing.overload
    def __init__(self, component: DerivedRatioToStandard) -> None:
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
    def E1(self) -> float:
        """
        the lower energy bound
        """
    @property
    def E2(self) -> float:
        """
        the upper energy bound
        """
    @property
    def EI(self) -> ...:
        """
        the energies
        """
    @property
    def LTY(self) -> int:
        """
        the procedure
        """
    @property
    def MATS(self) -> int:
        """
        the standard's material number
        """
    @property
    def MTS(self) -> int:
        """
        the standard's section number
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NEI(self) -> int:
        """
        the number of energies
        """
    @property
    def WEI(self) -> ...:
        """
        the weights
        """
    @property
    def XLFSS(self) -> int:
        """
        the standard's final excited state
        """
    @property
    def XMFS(self) -> int:
        """
        the standard's file number
        """
    @property
    def energies(self) -> ...:
        """
        the energies
        """
    @property
    def lower_energy(self) -> float:
        """
        the lower energy bound
        """
    @property
    def number_energies(self) -> int:
        """
        the number of energies
        """
    @property
    def procedure(self) -> int:
        """
        the procedure
        """
    @property
    def standard_file_number(self) -> int:
        """
        the standard's file number
        """
    @property
    def standard_final_excited_state(self) -> int:
        """
        the standard's final excited state
        """
    @property
    def standard_material_number(self) -> int:
        """
        the standard's material number
        """
    @property
    def standard_section_number(self) -> int:
        """
        the standard's section number
        """
    @property
    def upper_energy(self) -> float:
        """
        the upper energy bound
        """
    @property
    def weights(self) -> ...:
        """
        the weights
        """
class DerivedRedundant:
    """
    Covariance component - NC-type sub-subsection for derived redundant quantities
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DerivedRedundant:
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
    def __init__(self, e1: float, e2: float, coefficients: list[float], reactions: list[int]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            e1             the lower energy
            e2             the upper energy
            coefficients   the coefficients for linear combination
            reactions      the reaction MTs
        """
    @typing.overload
    def __init__(self, component: DerivedRedundant) -> None:
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
    def CI(self) -> ...:
        """
        the coefficients
        """
    @property
    def E1(self) -> float:
        """
        the lower energy bound
        """
    @property
    def E2(self) -> float:
        """
        the upper energy bound
        """
    @property
    def LTY(self) -> int:
        """
        the procedure
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NCI(self) -> int:
        """
        the number of reactions
        """
    @property
    def XMTI(self) -> ...:
        """
        the reaction MTs
        """
    @property
    def coefficients(self) -> ...:
        """
        the coefficients
        """
    @property
    def lower_energy(self) -> float:
        """
        the lower energy bound
        """
    @property
    def number_reactions(self) -> int:
        """
        the number of reactions
        """
    @property
    def procedure(self) -> int:
        """
        the procedure
        """
    @property
    def reactions(self) -> ...:
        """
        the reaction MTs
        """
    @property
    def upper_energy(self) -> float:
        """
        the upper energy bound
        """
class DirectoryRecord:
    """
    Directory record
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, right: DirectoryRecord) -> bool:
        """
        Compare two records
        
        Arguments:
            self     the record
            right    the record on the right
        """
    @typing.overload
    def __init__(self, mf: int, mt: int, nc: int, mod: int) -> None:
        """
        Initialise the record
        
        Arguments:
            self   the record
            mf     the MF number
            mt     the MT number
            nc     the number of lines that make up this section
            mod    the modification number
        """
    @typing.overload
    def __init__(self, record: DirectoryRecord) -> None:
        """
        Initialise the record with another record
        
        Arguments:
            self      the record
            record    the record to be copied
        """
    def to_string(self, mat: int) -> str:
        """
        Return the string representation of the record
        
        Arguments:
            self   the record
            mat    the MAT number to be used
        """
    @property
    def MF(self) -> int:
        """
        The MF number
        """
    @property
    def MOD(self) -> int:
        """
        The modification number
        """
    @property
    def MT(self) -> int:
        """
        the MT number
        """
    @property
    def NC(self) -> int:
        """
        The number of lines NC that make up this record
        """
class InterpolationRecord:
    """
    ENDF TAB2 record
    
    The interpolation record is a multi-line ENDF record containing 2 doubles
    and 4 integers on the first line, followed by interpolation information
    on the following lines.
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> InterpolationRecord:
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
    def __init__(self, C1: float, C2: float, L1: int, L2: int, boundaries: list[int], interpolants: list[int]) -> None:
        """
        Initialise the record
        
        Arguments:
            self           the record
            C1             the double in column 1
            C2             the double in column 2
            L1             the integer in column 3
            L2             the integer in column 4
            boundaries     the interpolation range boundaries
            interpolants   the interpolation types for each range
        """
    @typing.overload
    def __init__(self, record: InterpolationRecord) -> None:
        """
        Initialise the record with another record
        
        Arguments:
            self      the record
            record    the record to be copied
        """
    @typing.overload
    def __init__(self, component: InterpolationRecord) -> None:
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
    def C1(self) -> float:
        """
        The double in column 1
        """
    @property
    def C2(self) -> float:
        """
        The double in column 2
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def L1(self) -> int:
        """
        The integer in column 3
        """
    @property
    def L2(self) -> int:
        """
        The integer in column 4
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
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NZ(self) -> int:
        """
        The number of points
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
class ListRecord:
    """
    ENDF LIST record
    
    The list record is a multi-line ENDF record containing 2 doubles
    and 4 integers on the first line, followed by a list of values on the
    following lines.
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ListRecord:
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
    def __init__(self, C1: float, C2: float, L1: int, L2: int, N2: int, list: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self   the record
            C1     the double in column 1
            C2     the double in column 2
            L1     the integer in column 3
            L2     the integer in column 4
            N2     the integer in column 6
            list   the list of values
        """
    @typing.overload
    def __init__(self, record: ListRecord) -> None:
        """
        Initialise the record with another record
        
        Arguments:
            self      the record
            record    the record to be copied
        """
    @typing.overload
    def __init__(self, component: ListRecord) -> None:
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
    def C1(self) -> float:
        """
        The double in column 1
        """
    @property
    def C2(self) -> float:
        """
        The double in column 2
        """
    @property
    def L1(self) -> int:
        """
        The integer in column 3
        """
    @property
    def L2(self) -> int:
        """
        The integer in column 4
        """
    @property
    def N2(self) -> int:
        """
        The integer in column 6
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NPL(self) -> int:
        """
        The number of values in the list
        """
    @property
    def list(self) -> ...:
        """
        The list of values
        """
    @property
    def number_values(self) -> int:
        """
        The number of values in the list
        """
class Material:
    """
    Material - nuclear data for a single material
    """
    @staticmethod
    def from_string(material: str) -> Material:
        """
        Read the material from a string
        
        An exception is raised if something goes wrong while reading the
        material
        
        Arguments:
            material    the string representing the material
        """
    def MF(self, mf: int) -> MF1.File | MF2.File | MF3.File | MF4.File | MF5.File | MF6.File | MF7.File | MF8.File | MF9.File | MF10.File | MF12.File | MF13.File | MF14.File | MF15.File | MF23.File | MF26.File | MF27.File | MF28.File | ... | MF31.File | MF32.File | MF33.File | MF34.File | MF35.File | MF40.File:
        """
        Return the file with the requested MF number
        
        Arguments:
            self    the file
            mf      the MF number of the file to be returned
        """
    def MFMT(self, mf: int, mt: int) -> MF1.MT451.Section | MF1.MT452.Section | MF1.MT455.Section | MF1.MT456.Section | MF1.MT458.Section | MF1.MT460.Section | MF2.MT151.Section | MF2.MT152.Section | MF3.Section | MF4.Section | MF5.Section | MF6.Section | MF7.MT2.Section | MF7.MT4.Section | MF7.MT451.Section | MF8.MT454.Section | MF8.MT457.Section | MF8.MT459.Section | MF9.Section | MF10.Section | MF12.Section | MF13.Section | MF14.Section | MF15.Section | MF23.Section | MF26.Section | MF27.Section | MF28.Section | MF31.Section | MF32.MT151.Section | MF33.Section | MF34.Section | MF35.Section | MF40.Section:
        """
            mt      the MT number of the section to be returned
        """
    def file(self, mf: int) -> MF1.File | MF2.File | MF3.File | MF4.File | MF5.File | MF6.File | MF7.File | MF8.File | MF9.File | MF10.File | MF12.File | MF13.File | MF14.File | MF15.File | MF23.File | MF26.File | MF27.File | MF28.File | ... | MF31.File | MF32.File | MF33.File | MF34.File | MF35.File | MF40.File:
        """
        Return the file with the requested MF number
        
        Arguments:
            self    the file
            mf      the MF number of the file to be returned
        """
    def has_MF(self, mf: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the file
            mf      the MF number of the file
        """
    def has_MF_MT(self, arg0: int, arg1: int) -> bool:
        """
        Return whether or not the material has a section with the given MF and MT number
        
        Arguments:
            self    the material
            mf      the MF number of the section
            mt      the MT number of the section
        """
    def has_file(self, mf: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the file
            mf      the MF number of the file
        """
    def has_section(self, arg0: int, arg1: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the material
            mf      the MF number of the section
            mt      the MT number of the section
        """
    def section(self, mf: int, mt: int) -> MF1.MT451.Section | MF1.MT452.Section | MF1.MT455.Section | MF1.MT456.Section | MF1.MT458.Section | MF1.MT460.Section | MF2.MT151.Section | MF2.MT152.Section | MF3.Section | MF4.Section | MF5.Section | MF6.Section | MF7.MT2.Section | MF7.MT4.Section | MF7.MT451.Section | MF8.MT454.Section | MF8.MT457.Section | MF8.MT459.Section | MF9.Section | MF10.Section | MF12.Section | MF13.Section | MF14.Section | MF15.Section | MF23.Section | MF26.Section | MF27.Section | MF28.Section | MF31.Section | MF32.MT151.Section | MF33.Section | MF34.Section | MF35.Section | MF40.Section:
        """
            mt      the MT number of the section to be returned
        """
    def to_string(self) -> str:
        """
        The string representation of the material
        
        Arguments:
            self    the material
        """
    def to_tree(self) -> ...:
        """
        Return the ENDF tree representation of the material
        
        Arguments:
            self    the file
        """
    @property
    def MAT(self) -> int:
        """
        The material number
        """
    @property
    def MFs(self) -> ...:
        """
        The files defined in the material
        """
    @property
    def files(self) -> ...:
        """
        The files defined in the material
        """
    @property
    def material_number(self) -> int:
        """
        The material number
        """
class ReactionBlock:
    """
    Covariance component - a covariance subsection
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ReactionBlock:
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
    def __init__(self, xmf1: float, xlfs1: float, mat1: int, mt1: int, nc: list[DerivedRedundant | DerivedRatioToStandard], ni: list[CovariancePairs | SquareMatrix | RectangularMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            xmf1           the file number of the second cross section
            xlfs1          the final excited state of the second cross section
            mat1           the material number of the second cross section
            mt1            the section number of the second cross section
            nc             the NC-type (derived) subsubsections
            ni             the NI-type (explicit) subsubsections
        """
    @typing.overload
    def __init__(self, xmf1: float, xlfs1: float, mat1: int, mt1: int, nc: list[DerivedRedundant | DerivedRatioToStandard]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            xmf1           the file number of the second cross section
            xlfs1          the final excited state of the second cross section
            mat1           the material number of the second cross section
            mt1            the section number of the second cross section
            nc             the NC-type (derived) subsubsections
        """
    @typing.overload
    def __init__(self, xmf1: float, xlfs1: float, mat1: int, mt1: int, ni: list[CovariancePairs | SquareMatrix | RectangularMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            xmf1           the file number of the second cross section
            xlfs1          the final excited state of the second cross section
            mat1           the material number of the second cross section
            mt1            the section number of the second cross section
            ni             the NI-type (explicit) subsubsections
        """
    @typing.overload
    def __init__(self, component: ReactionBlock) -> None:
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
    def MAT1(self) -> int:
        """
        the material number for the second cross section
        """
    @property
    def MT1(self) -> int:
        """
        the section number for the second cross section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NI(self) -> int:
        """
        the number of NI-type (explicit) subsubsections
        """
    @property
    def NK(self) -> int:
        """
        the number of NC-type (derived) subsubsections
        """
    @property
    def XLFS1(self) -> int:
        """
        the final excited state for the second cross section
        """
    @property
    def XMF1(self) -> int:
        """
        the file number for the second cross section
        """
    @property
    def derived_covariances(self) -> ...:
        """
        the NC-type (derived) subsubsections
        """
    @property
    def explicit_covariances(self) -> ...:
        """
        the NI-type (explicit) subsubsections
        """
    @property
    def number_derived(self) -> int:
        """
        the number of NC-type (derived) subsubsections
        """
    @property
    def number_explicit(self) -> int:
        """
        the number of NI-type (explicit) subsubsections
        """
    @property
    def second_file_number(self) -> int:
        """
        the file number for the second cross section
        """
    @property
    def second_final_excited_state(self) -> int:
        """
        the final excited state for the second cross section
        """
    @property
    def second_material_number(self) -> int:
        """
        the material number for the second cross section
        """
    @property
    def second_section_number(self) -> int:
        """
        the section number for the second cross section
        """
class RectangularMatrix:
    """
    Covariance component - NI-type sub-subsection given as a rectangular matrix
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> RectangularMatrix:
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
    def __init__(self, row_energies: list[float], column_energies: list[float], values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            row_energies           row energies
            column_energies        column energies
            values                 matrix values
        """
    @typing.overload
    def __init__(self, component: RectangularMatrix) -> None:
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
    def LB(self) -> int:
        """
        The procedure
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NEC(self) -> int:
        """
        The number of energies representing a column
        """
    @property
    def NER(self) -> int:
        """
        The number of energies representing a row
        """
    @property
    def NT(self) -> int:
        """
        The number of values in this component
        """
    @property
    def column_energies(self) -> ...:
        """
        The column energy values
        """
    @property
    def number_column_energies(self) -> int:
        """
        The number of energies representing a column
        """
    @property
    def number_row_energies(self) -> int:
        """
        The number of energies representing a row
        """
    @property
    def number_values(self) -> int:
        """
        The number of values in this component
        """
    @property
    def procedure(self) -> int:
        """
        The procedure
        """
    @property
    def row_energies(self) -> ...:
        """
        The row energy values
        """
    @property
    def values(self) -> ...:
        """
        The matrix values
        """
class SquareMatrix:
    """
    Covariance component - NI-type sub-subsection given as a square matrix
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> SquareMatrix:
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
    def __init__(self, ls: int, energies: list[float], values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            ls             symmetry flag (0=asymmetric, 1=symmetric)
            energies       energies
            values         matrix values
        """
    @typing.overload
    def __init__(self, component: SquareMatrix) -> None:
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
    def LB(self) -> int:
        """
        the procedure
        """
    @property
    def LS(self) -> int:
        """
        the symmetry flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NE(self) -> int:
        """
        the number of energies in the array
        """
    @property
    def NT(self) -> int:
        """
        the number of values in this component
        """
    @property
    def energies(self) -> ...:
        """
        the energy values
        """
    @property
    def is_symmetric(self) -> bool:
        """
        the symmetry flag as a boolean
        """
    @property
    def number_energies(self) -> int:
        """
        the number of energies in the array
        """
    @property
    def number_values(self) -> int:
        """
        the number of values in this component
        """
    @property
    def procedure(self) -> int:
        """
        the procedure
        """
    @property
    def symmetry_flag(self) -> int:
        """
        the symmetry flag
        """
    @property
    def values(self) -> ...:
        """
        the matrix values
        """
class TabulationRecord:
    """
    ENDF TAB1 record
    
    The tabulation record is a multi-line ENDF record containing 2 doubles
    and 4 integers on the first line, followed by a interpolation data and a
    list of x,y values on the following lines.
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TabulationRecord:
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
    def __init__(self, C1: float, C2: float, L1: int, L2: int, boundaries: list[int], interpolants: list[int], x: list[float], y: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self           the record
            C1             the double in column 1
            C2             the double in column 2
            L1             the integer in column 3
            L2             the integer in column 4
            boundaries     the interpolation range boundaries
            interpolants   the interpolation types for each range
            x              the x values
            y              the y values
        """
    @typing.overload
    def __init__(self, record: TabulationRecord) -> None:
        """
        Initialise the record with another record
        
        Arguments:
            self      the record
            record    the record to be copied
        """
    @typing.overload
    def __init__(self, component: TabulationRecord) -> None:
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
    def C1(self) -> float:
        """
        The double in column 1
        """
    @property
    def C2(self) -> float:
        """
        The double in column 2
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def L1(self) -> int:
        """
        The integer in column 3
        """
    @property
    def L2(self) -> int:
        """
        The integer in column 4
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
    def x(self) -> ...:
        """
        The x values
        """
    @property
    def y(self) -> ...:
        """
        The y values
        """
class TapeIdentification:
    """
    Tape identification
    """
    @typing.overload
    def __init__(self, text: str) -> None:
        """
        Initialise the record
        
        Arguments:
            self   the tape identifier
            text   the tape identification
        """
    @typing.overload
    def __init__(self, record: TapeIdentification) -> None:
        """
        Initialise the record with another record
        
        Arguments:
            self      the record
            record    the record to be copied
        """
    def to_string(self) -> str:
        """
        Return the string representation of the tape identification
        
        Arguments:
            self   the record
        """
    @property
    def text(self) -> str:
        """
        The tape indentification
        """
