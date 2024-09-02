from FunEnginePy import math
from FunEnginePy.math import approximately as aprox
from FunEnginePy.math import Vector2, Vector3, Vector3Int, Vector4, Vector4Int

def  test_repr():
  assert repr(Vector4Int(10, 10, 10, 10)) == "Vector4Int(10, 10, 10, 10)"

def test_vectors_magnitude():
    assert aprox(Vector2(10, 10).magnitude(), 14.142135623730951)
    assert aprox(Vector2(1, 1).magnitude(), 1.4142135623730951)
    assert aprox(Vector2(-1, 1).magnitude(), 1.4142135623730951)
    assert aprox(Vector2(1, -1).magnitude(), 1.4142135623730951)

    assert aprox(Vector3(10, 10, 10).magnitude(), 17.320508075688775)
    assert aprox(Vector3(1, 1, 1).magnitude(), 1.7320508075688772)
    assert aprox(Vector3(-1, 1, 1).magnitude(), 1.7320508075688772)
    assert aprox(Vector3(1, -1, 1).magnitude(), 1.7320508075688772)

    # This is here more as a sanity check than anything.
    assert aprox(Vector3Int(10, 10, 10).magnitude(), 17.320508075688775)
    assert aprox(Vector3Int(1, 1, 1).magnitude(), 1.7320508075688772)
    assert aprox(Vector3Int(-1, 1, 1).magnitude(), 1.7320508075688772)
    assert aprox(Vector3Int(1, -1, 1).magnitude(), 1.7320508075688772)


def test_vectors_properties():
    curr_vec = Vector4(0, 1, 2, 3)

    assert aprox(curr_vec.get_x(), 0)
    assert aprox(curr_vec.get_y(), 1)
    assert aprox(curr_vec.get_z(), 2)
    assert aprox(curr_vec.get_w(), 3)
