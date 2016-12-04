x = 7
def f():
  x = 99
  def g():
    # x += 1
    x = x +1
    print x

  g()

f()
print x
