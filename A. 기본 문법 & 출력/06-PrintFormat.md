# Python Formatting
Python의 print 포맷팅 예제. 
Rust에서는 println! 매크로를 사용하며, 포맷 문자열은 Python의 format() 방식과 매우 유사하지만 타입별 접두어 없이 중괄호 {}만 사용. 

## 🧵 문자열 포맷팅 비교 (%s 스타일 기준)

| Python 코드                              | Rust 코드                                | 출력 결과       |
|------------------------------------------|-------------------------------------------|-----------------|
| `print("%10s" % 'sample')`               | `println!("{:>10}", "sample");`           | `    sample`    |
| `print("%-10s" % 'sample')`              | `println!("{:<10}", "sample");`           | `sample     `   |
| `print("{:_>10}".format("sample"))`      | `println!("{:_>10}", "sample");`          | `____sample`    |
| `print("{:^10}".format("sample"))`       | `println!("{:^10}", "sample");`           | `  sample  `    |
| `print('%.5s' % 'pythontest')`           | `println!("{:.5}", "pythontest");`        | `pytho`         |
| `print("{:10.5}".format("pythontest"))`  | `println!("{:10.5}", "pythontest");`      | `pytho     `    |

### 예제
```python
# %s
print("%10s" % 'sample')
'''
    sample
'''

print("%10s" % 'sample1234')
'''
sample1234
'''

print('{:>10}'.format('sample'))
'''
    sample
'''

print('{:<10}'.format('sample1234'))
'''
sample1234
'''

print("%-10s" % 'sample')
'''
sample     
'''

print('{:10}'.format('sample'))
'''
sample      
'''

print("{:_>10}".format("sample"))
'''
____sample      
'''

print("{:0>10}".format("sample"))
'''
0000sample      
'''

print("{:^10}".format("sample"))
'''
  sample        
'''

print('%.5s' % 'sample')
'''
sampl        
'''

print('%.5s' % 'test')
'''
test       
'''

print('%.5s' % 'pythontest')
'''
pytho        
'''

print("{:10.5}".format('pythontest'))
'''
pytho        
'''

```


🔢 정수 포맷팅 비교 (%d 스타일 기준)

| Python 코드                        | Rust 코드                          | 출력 결과 |
|------------------------------------|-------------------------------------|------------|
| `print('%4d' % 42)`                | `println!("{:4}", 42);`             | `  42`     |
| `print('{:04d}'.format(42))`       | `println!("{:04}", 42);`            | `0042`     |
| `print('{} {}'.format(1, 2))`      | `println!("{} {}", 1, 2);`          | `1 2`      |

```python
# %d
print('%d %d' % (1, 2))
'''
1 2       
'''

print('{} {}'.format(1, 2))
'''
1 2       
'''

print('%4d' % (42))
'''
  42      
'''

print("{:4d}".format(42))
'''
  42      
'''

```

🔬 실수 포맷팅 비교 (%f 스타일 기준)

| Python 코드                          | Rust 코드                              | 출력 결과               |
|--------------------------------------|-----------------------------------------|--------------------------|
| `print('%f' % 3.14159234)`           | `println!("{:f}", 3.14159234);`         | `3.141592`               |
| `print('%1.18f' % 3.14159234)`       | `println!("{:.18}", 3.14159234);`       | `3.141592339999999872`   |
| `print('%06.2f' % 3.141592)`         | `println!("{:06.2}", 3.141592);`        | `003.14`                 |
```python
# %f
print('%f' % 3.14159234)
'''
3.141592     
'''

print('%1.18f' % 3.14159234)
'''
3.141592339999999872    
'''

print('{:f}'.format(3.14159234))
'''
3.141592     
'''

print('{:1.18f}'.format(3.14159234))
'''
3.141592339999999872  
'''

print('%06.2f' % 3.141592)
'''
003.14 
'''
print('{:06.2f}'.format(3.14159234))
'''
003.14 
'''

```


