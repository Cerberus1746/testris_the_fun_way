from typing import Any, Optional, overload, Typing, Sequence, Iterable, Union, Callable
from enum import Enum
import FunEnginePy.math

class Vector2:
    """
    None
    """

    def __init__(self, arg0: float, arg1: float, /) -> None:
        ...
    
    def angle(*args, **kwargs):
        """
        angle(self, arg: FunEngine::Math::Vector@math.vectors<double, 2ul>, /) -> float
        """
        ...
    
    def angle_to(*args, **kwargs):
        """
        angle_to(self, arg: FunEngine::Math::Vector@math.vectors<double, 2ul>, /) -> float
        """
        ...
    
    def get_x(self) -> float:
        ...
    
    def get_y(self) -> float:
        ...
    
    def magnitude(self) -> float:
        ...
    
    def set_x(self, arg: float, /) -> None:
        ...
    
    def set_y(self, arg: float, /) -> None:
        ...
    
    @property
    def x_axis(self) -> float:
        ...
    @x_axis.setter
    def x_axis(self, arg: float, /) -> None:
        ...
    
    @property
    def y_axis(self) -> float:
        ...
    @y_axis.setter
    def y_axis(self, arg: float, /) -> None:
        ...
    
class Vector2Int:
    """
    None
    """

    def __init__(self, arg0: int, arg1: int, /) -> None:
        ...
    
    def angle(*args, **kwargs):
        """
        angle(self, arg: FunEngine::Math::Vector@math.vectors<int, 2ul>, /) -> int
        """
        ...
    
    def angle_to(*args, **kwargs):
        """
        angle_to(self, arg: FunEngine::Math::Vector@math.vectors<int, 2ul>, /) -> int
        """
        ...
    
    def get_x(self) -> int:
        ...
    
    def get_y(self) -> int:
        ...
    
    def magnitude(self) -> float:
        ...
    
    def set_x(self, arg: int, /) -> None:
        ...
    
    def set_y(self, arg: int, /) -> None:
        ...
    
    @property
    def x_axis(self) -> int:
        ...
    @x_axis.setter
    def x_axis(self, arg: int, /) -> None:
        ...
    
    @property
    def y_axis(self) -> int:
        ...
    @y_axis.setter
    def y_axis(self, arg: int, /) -> None:
        ...
    
class Vector3:
    """
    None
    """

    def __init__(self, arg0: float, arg1: float, arg2: float, /) -> None:
        ...
    
    def angle_to(*args, **kwargs):
        """
        angle_to(self, arg: FunEngine::Math::Vector@math.vectors<double, 3ul>, /) -> float
        """
        ...
    
    def get_x(self) -> float:
        ...
    
    def get_y(self) -> float:
        ...
    
    def get_z(self) -> float:
        ...
    
    def magnitude(self) -> float:
        ...
    
    def set_x(self, arg: float, /) -> None:
        ...
    
    def set_y(self, arg: float, /) -> None:
        ...
    
    def set_z(self, arg: float, /) -> None:
        ...
    
    @property
    def x_axis(self) -> float:
        ...
    @x_axis.setter
    def x_axis(self, arg: float, /) -> None:
        ...
    
    @property
    def y_axis(self) -> float:
        ...
    @y_axis.setter
    def y_axis(self, arg: float, /) -> None:
        ...
    
    @property
    def z_axis(self) -> float:
        ...
    @z_axis.setter
    def z_axis(self, arg: float, /) -> None:
        ...
    
class Vector3Int:
    """
    None
    """

    def __init__(self, arg0: int, arg1: int, arg2: int, /) -> None:
        ...
    
    def angle_to(*args, **kwargs):
        """
        angle_to(self, arg: FunEngine::Math::Vector@math.vectors<int, 3ul>, /) -> int
        """
        ...
    
    def get_x(self) -> int:
        ...
    
    def get_y(self) -> int:
        ...
    
    def get_z(self) -> int:
        ...
    
    def magnitude(self) -> float:
        ...
    
    def set_x(self, arg: int, /) -> None:
        ...
    
    def set_y(self, arg: int, /) -> None:
        ...
    
    def set_z(self, arg: int, /) -> None:
        ...
    
    @property
    def x_axis(self) -> int:
        ...
    @x_axis.setter
    def x_axis(self, arg: int, /) -> None:
        ...
    
    @property
    def y_axis(self) -> int:
        ...
    @y_axis.setter
    def y_axis(self, arg: int, /) -> None:
        ...
    
    @property
    def z_axis(self) -> int:
        ...
    @z_axis.setter
    def z_axis(self, arg: int, /) -> None:
        ...
    
class Vector4:
    """
    None
    """

    def __init__(self, arg0: float, arg1: float, arg2: float, arg3: float, /) -> None:
        ...
    
    def angle_to(*args, **kwargs):
        """
        angle_to(self, arg: FunEngine::Math::Vector@math.vectors<double, 4ul>, /) -> float
        """
        ...
    
    def get_w(self) -> float:
        ...
    
    def get_x(self) -> float:
        ...
    
    def get_y(self) -> float:
        ...
    
    def get_z(self) -> float:
        ...
    
    def magnitude(self) -> float:
        ...
    
    def set_w(self, arg: float, /) -> None:
        ...
    
    def set_x(self, arg: float, /) -> None:
        ...
    
    def set_y(self, arg: float, /) -> None:
        ...
    
    def set_z(self, arg: float, /) -> None:
        ...
    
    @property
    def w_axis(self) -> float:
        ...
    @w_axis.setter
    def w_axis(self, arg: float, /) -> None:
        ...
    
    @property
    def x_axis(self) -> float:
        ...
    @x_axis.setter
    def x_axis(self, arg: float, /) -> None:
        ...
    
    @property
    def y_axis(self) -> float:
        ...
    @y_axis.setter
    def y_axis(self, arg: float, /) -> None:
        ...
    
    @property
    def z_axis(self) -> float:
        ...
    @z_axis.setter
    def z_axis(self, arg: float, /) -> None:
        ...
    
class Vector4Int:
    """
    None
    """

    def __init__(self, arg0: int, arg1: int, arg2: int, arg3: int, /) -> None:
        ...
    
    def angle_to(*args, **kwargs):
        """
        angle_to(self, arg: FunEngine::Math::Vector@math.vectors<int, 4ul>, /) -> int
        """
        ...
    
    def get_w(self) -> int:
        ...
    
    def get_x(self) -> int:
        ...
    
    def get_y(self) -> int:
        ...
    
    def get_z(self) -> int:
        ...
    
    def magnitude(self) -> float:
        ...
    
    def set_w(self, arg: int, /) -> None:
        ...
    
    def set_x(self, arg: int, /) -> None:
        ...
    
    def set_y(self, arg: int, /) -> None:
        ...
    
    def set_z(self, arg: int, /) -> None:
        ...
    
    @property
    def w_axis(self) -> int:
        ...
    @w_axis.setter
    def w_axis(self, arg: int, /) -> None:
        ...
    
    @property
    def x_axis(self) -> int:
        ...
    @x_axis.setter
    def x_axis(self, arg: int, /) -> None:
        ...
    
    @property
    def y_axis(self) -> int:
        ...
    @y_axis.setter
    def y_axis(self, arg: int, /) -> None:
        ...
    
    @property
    def z_axis(self) -> int:
        ...
    @z_axis.setter
    def z_axis(self, arg: int, /) -> None:
        ...
    
def approximately(left: float, right: float, tolerance: float = 2.220446049250313e-16) -> bool:
    """
    Compare two floating points together
    """
    ...

