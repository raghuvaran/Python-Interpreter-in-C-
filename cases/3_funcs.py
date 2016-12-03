a = 34
def f():
  a = 4
  def g():
    print a
  g()
  a = 3
  print a
def g():
  print a
print a

f()
g()
