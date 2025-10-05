import mything

print(mything.MyThing.version())   # "MyThing/1.0"

t = mything.MyThing(10)
print(t.value)                     # 10
t.value = 42
print(t.increment(8))              # 50
print(t.value)                     # 50
