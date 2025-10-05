# CPP 연동
- 아주 작은 C++ 클래스를 만들고, pybind11로 파이썬 모듈로 노출하는 “최소완성” 예제.

## 구성
- 클래스: MyThing
- 멤버 변수: value_ (int)
- 멤버 메소드: increment(int delta)
- 정적 메소드: version()
- getter/setter도 함께 바인딩
