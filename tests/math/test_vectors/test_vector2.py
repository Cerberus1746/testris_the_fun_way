from FunEnginePy.math import approximately as aprox
from FunEnginePy.math import Vector2, Vector2Int

def  test_repr():
  assert repr(Vector2(10, 10)) == "Vector2(10.000000, 10.000000)"
  assert repr(Vector2Int(10, 10)) == "Vector2Int(10, 10)"

def test_vectors_magnitude():
    assert aprox(Vector2(10, 10).magnitude(), 14.142135623730951)
    assert aprox(Vector2(1, 1).magnitude(), 1.4142135623730951)
    assert aprox(Vector2(-1, 1).magnitude(), 1.4142135623730951)
    assert aprox(Vector2(1, -1).magnitude(), 1.4142135623730951)

    assert aprox(Vector2Int(10, 10).magnitude(), 14.142135623730951)
    assert aprox(Vector2Int(1, 1).magnitude(), 1.4142135623730951)
    assert aprox(Vector2Int(-1, 1).magnitude(), 1.4142135623730951)
    assert aprox(Vector2Int(1, -1).magnitude(), 1.4142135623730951)


def test_vectors_properties():
    curr_vec = Vector2(0, 1)

    assert aprox(curr_vec.get_x(), 0)
    assert aprox(curr_vec.get_y(), 1)

    assert aprox(curr_vec.x_axis, 0)
    assert aprox(curr_vec.y_axis, 1)

    curr_vec.x_axis = 6
    curr_vec.y_axis = 7

    assert aprox(curr_vec.get_x(), 6)
    assert aprox(curr_vec.get_y(), 7)

    assert aprox(curr_vec.x_axis, 6)
    assert aprox(curr_vec.y_axis, 7)
