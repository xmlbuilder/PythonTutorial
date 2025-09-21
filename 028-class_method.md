# class method

## 🐶 Python 클래스 Method 예제
이 예제는 Python의 클래스와 인스턴스 메서드를 활용하여 개(Dog)의 정보를 출력하고 소리를 내는 기능을 구현합니다.

### 📦 클래스 정의
```python
class Dog:
    species = 'firstdog'  # 클래스 변수

    def __init__(self, name, age):  # 생성자
        self.name = name
        self.age = age

    def info(self):  # 인스턴스 메서드: 정보 출력
        return '{} is {} years old'.format(self.name, self.age)

    def speak(self, sound):  # 인스턴스 메서드: 소리 내기
        return "{} says {}!".format(self.name, sound)

```
### 🐕 인스턴스 생성 및 메서드 호출
```python
# 인스턴스 생성
c = Dog('july', 4)
d = Dog('Marry', 10)

# 메서드 호출
print(c.info())           # july is 4 years old
print(c.speak('Wal Wal')) # july says Wal Wal!
print(d.speak('Mung Mung')) # Marry says Mung Mung!
```

### 🧾 출력 결과
```
july is 4 years old
july says Wal Wal!
Marry says Mung Mung!
```


## 📘 설명
- species: 클래스 변수로 모든 인스턴스가 공유합니다.
- __init__: 생성자 메서드로 이름과 나이를 초기화합니다.
- info(): 인스턴스의 이름과 나이를 문자열로 반환합니다.
- speak(sound): 인스턴스가 특정 소리를 낸다는 메시지를 반환합니다.

---

