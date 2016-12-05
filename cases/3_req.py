x = 7
def f():
  x = 99
  def g():
    # x += 1
    x = x +1
    print x

  g()

def a():
	def b():
		def c():
			y = 77
			def d():
				def e():
					def h():
						print y
						print x
					h()
				e()
			d()
		c()
	b()

a()

f()
print x
