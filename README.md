# PythonTutorial

Python 기초부터 함수형, 컬렉션 심화, OOP, 예외/파일 I/O, 미니 프로젝트까지 **짧은 예제 중심**으로 정리한 튜토리얼입니다.

- [좋은 코드를 만드는 습관](/0.좋은%20코드를%20만드는%20습관/01-좋은_코드를_만드는_습관.md)
- [Python 장점](./001-Python장점.md),
- [예약어](./002-예약어.md),
- [주요 상수](./003-주요상수.md),
- [내장 네임스페이스](./004-내장네임스페이스.md)

---

## 📚 목차(바로가기)

- [A. 기본 문법 & 출력/형식](#a-기본-문법--출력형식)
- [B. 데이터 타입 & 기본 연산](#b-데이터-타입--기본-연산)
- [C. 컬렉션(리스트,튜플,딕셔너리,셋)](#c-컬렉션리스트튜플딕셔너리셋)
- [D. 제어문](#d-제어문)
- [E. 함수 & 함수형 패턴](#e-함수--함수형-패턴)
- [F. 클래스 & OOP](#f-클래스--oop)
- [G. 시퀀스 심화 & 자료구조](#g-시퀀스-심화--자료구조)
- [H. 예외 & 어서션](#h-예외--어서션)
- [I. 표준 라이브러리/모듈/내장함수](#i-표준-라이브러리모듈내장함수)
- [J. 파일 IO & 입력](#j-파일-io--입력)
- [K. 반복자/이터러블/itertools](#k-반복자이터러블itertools)
- [L. 미니 프로젝트](#l-미니-프로젝트)
- [M. 메모리 참조](#m-메모리-참조)
- [N. Design Pattern](#n-Design-Pattern)
- [O. 실행 모델 & 변수 스코프](#o-실행-모델--변수-스코프)
- [Z. 비동기 프로그래밍 & Coroutine](#z-비동기-프로그래밍--Coroutine)
- [검색 팁](#검색-팁)
- [기여 가이드](#기여-가이드)

---

## A. 기본 문법 & 출력/형식
- [여러 문장 한 줄에 코딩](./A.%20기본%20문법%20%26%20출력/01-여러문장_한줄에코딩.md)
- 타입 힌트: [Type Hint](./A.%20기본%20문법%20%26%20출력/02-TypeHint.md)
- 출력과 포맷
  - [print 기본](./A.%20기본%20문법%20%26%20출력/03-Print.md)
  - [포맷 기본 1](./A.%20기본%20문법%20%26%20출력/04-PrintFormat.md)
  - [포맷 기본 2](./A.%20기본%20문법%20%26%20출력/05-03-PrintFormat.md)
  - [포맷 최신 정리(2023)](./A.%20기본%20문법%20%26%20출력/06-Print2023.md)
  - [format 함수](./A.%20기본%20문법%20%26%20출력/07-Format.md)
  - [기타 포맷](./A.%20기본%20문법%20%26%20출력/08-Format.md)
    
- 식별자/불리언:
  - [id & is Reference 참조](./A.%20기본%20문법%20%26%20출력/09-id_is.md)
  - [None/Bool](./A.%20기본%20문법%20%26%20출력/10-None_Bool.md)
- 🔼 [맨 위로](#-목차바로가기)

## B. 데이터 타입 & 기본 연산
- 개요: [자료형 훑어보기](./B.%20데이터%20타입%20%26%20기본%20연산/01-자료형.md)
- 숫자형: [숫자형 타입](./B.%20데이터%20타입%20%26%20기본%20연산/02-숫자형타입.md)
- 문자열:
  - [문자형 타입](./B.%20데이터%20타입%20%26%20기본%20연산/03-문자형타입.md)
  - [문자형 연산](./B.%20데이터%20타입%20%26%20기본%20연산/04-문자형연산.md)
  - [슬라이스](./B.%20데이터%20타입%20%26%20기본%20연산/05-문자형Slice.md)
  - [불변/변경](./B.%20데이터%20타입%20%26%20기본%20연산/06-문자형변경.md)
  - [인코딩/디코딩](./B.%20데이터%20타입%20%26%20기본%20연산/07-문자형인코딩디코딩.md)
- 열거형:
  - [Enum](./B.%20데이터%20타입%20%26%20기본%20연산/08-Enum.md)  
- 🔼 [맨 위로](#-목차바로가기)

## C. 컬렉션(리스트/튜플/딕셔너리/셋)
- 리스트:
  - [리스트 기본](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/01-list.md),
  - [리스트 값 비교](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/02-list_값비교.md)
- 튜플:
  - [Tuple](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/03-Tuple.md)
  - [NamedTuple](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/04-Named_Tuple.md)
- 딕셔너리: [Dictionary](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/05-Dictionary.md)
- 셋:
  - [Set](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/06-Set.md)
  - [frozenset](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/07-set_frozenset.md)
- 맵(개념): [Map](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/08-Map.md)
- 변경 가능성: [Mutable/Immutable 구분](./C.%20컬렉션(리스트%2C튜플%2C딕셔너리%2C셋)/09-변경가능여부확인.md)
- 🔼 [맨 위로](#-목차바로가기)

## D. 제어문
- if:
  - [기본](./D.%20제어문/01-if기본.md),
  - [논리연산자](./D.%20제어문/02-if논리연산자.md),
  - [다중 조건](./D.%20제어문/03-if다중_조건문.md)
- for:
  - [기본](./D.%20제어문/04-for기본.md),
  - [break/continue](./D.%20제어문/05-for_break_continue.md),
  - [for-else](./D.%20제어문/06-for_else.md)
- while: [while](./D.%20제어문/07.md)
- 표현식:
  - [조건부 표현식](./D.%20제어문/08-Conditional_Expression.md)
  - [switch 스타일](./D.%20제어문/09-switch.md)
- 🔼 [맨 위로](#-목차바로가기)

## E. 함수 & 함수형 패턴
- 기초:
  - [함수 정의](./E.%20함수%20%26%20함수형%20패턴/01-함수정의.md)
  - [인자](./E.%20함수%20%26%20함수형%20패턴/02-함수Arugment.md)
  - [lambda](./E.%20함수%20%26%20함수형%20패턴/03-lambda.md)
- 고급:
  - [Currying](./E.%20함수%20%26%20함수형%20패턴/04-Currying.md)
  - [함수 객체 네임스페이스](./E.%20함수%20%26%20함수형%20패턴/05-함수%20객체의%20이름%20공간.md)
  - [메모이제이션](./E.%20함수%20%26%20함수형%20패턴/06-Memoization.md)
- 일급함수/클로저:
  - [First-class function](./E.%20함수%20%26%20함수형%20패턴/07-First_class_Function.md)
  - [global/nonlocal/점수 예제](./E.%20함수%20%26%20함수형%20패턴/08-Score_Closure_Globa_nonlocal.md)
  - [클로저/스코프](./E.%20함수%20%26%20함수형%20패턴/09-Closure_Scope.md)
- 체이닝 & 데코레이터:
  - [함수 체이닝](./E.%20함수%20%26%20함수형%20패턴/10-Function_Chaining.md)
  - [데코레이터 기본](./E.%20함수%20%26%20함수형%20패턴/11-Decorator.md)
  - [가변 인자 데코레이터](./E.%20함수%20%26%20함수형%20패턴/12-Decorator_Variable.md)
  - [클래스 데코레이터](./E.%20함수%20%26%20함수형%20패턴/13-Class_Decorator.md)
- 🔼 [맨 위로](#-목차바로가기)

## F. 클래스 & OOP
- 기초:
  - [클래스 기본](./F.%20클래스%20%26%20OOP/01-class_basic.md)
  - [self](./F.%20클래스%20%26%20OOP/02-class_self.md)
  - [메서드](./F.%20클래스%20%26%20OOP/03-class_method.md)
- 심화:
  - [bound/unbound 메서드](./F.%20클래스%20%26%20OOP/04-class_method_bound_method.md)
  - [클래스 메서드 심화](./F.%20클래스%20%26%20OOP/05-class_method_심화1md.md)
  - [id/dict](./F.%20클래스%20%26%20OOP/06-class_id_dict_.md)
  - [type과 클래스 메서드](./F.%20클래스%20%26%20OOP/07-class_method_type.md)
  - [클래스 속성](./F.%20클래스%20%26%20OOP/08-class_attr.md)
  - [다중 상속](./F.%20클래스%20%26%20OOP/09-다중_상속.md),
  - [super](./F.%20클래스%20%26%20OOP/10-super_class.md),
  - [Mixin](./F.%20클래스%20%26%20OOP/11-Mixin.md)
  - [매직 메서드](./12-MagicMethod.md),
  - [오버로딩](./F.%20클래스%20%26%20OOP/13-MagicMethodOverloading.md)
  - [isinstance/issubclass Type check](./F.%20클래스%20%26%20OOP/17-type_types_isinstance_issubclass.md)
- 실습:
  - [Vector 클래스 만들어보기](./F.%20클래스%20%26%20OOP/14-Vector클래스_만들어보기.md)
- 이터러블/이터레이터:
  - [Iterable](./F.%20클래스%20%26%20OOP/15-Iterable.md)
  - [Iterator/Generator](./F.%20클래스%20%26%20OOP/16-Iterator_Generator.md)
- Getter/Setter:
  - [Underscore를 이용한 Getter Setter 만들기](./F.%20클래스%20%26%20OOP/18-Underscore를%20이용한%20Getter%20Setter.md)
- Method Overriding 설명:
  - [Method Overring](./F.%20클래스%20%26%20OOP/19-Method_Overriding.md)
- Method Overloading 설명:
  - [Method Overloading](./F.%20클래스%20%26%20OOP/20-Method_Overloading.md)
- Metaclass 설명:
  - [Metaclass Type](./F.%20클래스%20%26%20OOP/21-Metaclass_type.md) 
  - [Metaclass Type 생성](./F.%20클래스%20%26%20OOP/22-Metaclass_type_생성.md)
  - [Metaclass Custom Class](./F.%20클래스%20%26%20OOP/23-Metaclass_CustomClass.md)
- dataclass 설명:
  - [DataClass](./F.%20클래스%20%26%20OOP/24-dataclass.md)
- Descriptor 설명:
  - [Descriptor](./F.%20클래스%20%26%20OOP/25-Descriptor.md)
- 🔼 [맨 위로](#-목차바로가기)

## G. 시퀀스 심화 & 자료구조
- [지능형 시퀀스](./G.%20시퀀스%20심화%20%26%20자료구조/01-Sequence_지능형.md)
- [Array](./G.%20시퀀스%20심화%20%26%20자료구조/02-Array.md)
- [Shallow/Deep Copy](./G.%20시퀀스%20심화%20%26%20자료구조/03-Sequence_Swallow_Deep_Copy.md)
- [Mutable 개념](./G.%20시퀀스%20심화%20%26%20자료구조/04-Sequence_Concept(Mutable).md)
- [해시테이블](./G.%20시퀀스%20심화%20%26%20자료구조/05-Sequence_HashTable.md)
- [Immutable Dict](./G.%20시퀀스%20심화%20%26%20자료구조/06-Sequence_Imutable_Dict.md)
- [색인 연산자](./G.%20시퀀스%20심화%20%26%20자료구조/07-색인_연산자.md)
- 🔼 [맨 위로](#-목차바로가기)

## H. 예외 & 어서션
- 예외 개요
  - [Exception](./H.%20예외%20%26%20어서션/01-exception.md)
  - [try/except](./H.%20예외%20%26%20어서션/02-try_except.md)
- assert
  - [assert](./H.%20예외%20%26%20어서션/03-assert.md),
  - [warnings](./H.%20예외%20%26%20어서션/04-waring.md)
- 🔼 [맨 위로](#-목차바로가기)

## I. 표준 라이브러리/모듈/내장함수
- [모듈](./I.%20표준%20라이브러리%20모듈%20내장함수/01-module.md)
- [내장 함수](./I.%20표준%20라이브러리%20모듈%20내장함수/02-내장함수.md)
- [외장 함수(표준 라이브러리)](./I.%20표준%20라이브러리%20모듈%20내장함수/03-외장함수.md)
- 🔼 [맨 위로](#-목차바로가기)

## J. 파일 IO & 입력
- [입력]
- [Input](./J.%20파일%20IO%20%26%20입력/01-Input.md)
- 파일 다루기:
  - [읽기 기본](./J.%20파일%20IO%20%26%20입력/02-File_Read.md)
  - [with open 패턴](./J.%20파일%20IO%20%26%20입력/03-File_With_Open.md)
  - [CSV/JSON 쓰기](./J.%20파일%20IO%20%26%20입력/04-File_With_Write_CSV_JSON.md)
- 메모리 파일 다루기:
  - [Ascii Memory 파일](./05-StringIO.md)
- 🔼 [맨 위로](#-목차바로가기)
  
## K. 반복자 이터러블 itertools
- [즉시 실행 vs 단계별 실행](./K.%20반복자%20이터러블%20itertools/01-즉시실행_단계별_실행.md)
- [itertools 요약](./K.%20반복자%20이터러블%20itertools/02-itertools.md)
- 🔼 [맨 위로](#-목차바로가기)

## L. 미니 프로젝트
- [특정 인덱스 찾기 구현](./L.%20미니%20프로젝트/01-특정인덱스_찾기_구현.md)
- [행맨 만들기](./L.%20미니%20프로젝트/02-Hangman_만들어보기.md)
  - → [개선안](./L.%20미니%20프로젝트/03-Hangman_개선.md)
- 🔼 [맨 위로](#-목차바로가기)

## M. 메모리 참조
- [강한 참조, 약한 참조 등](./M.%20메모리%20%26%20참조%20관리/01-Python의_참조_시스템.md)
- 🔼 [맨 위로](#-목차바로가기)

## N. Design Pattern
- [Factory Pattern](./N.%20Design%20Pattern/01-Factory_Pattern.md)
- [Observer Pattern](./N.%20Design%20Pattern/02-Observer_Pattern.md)
- 🔼 [맨 위로](#-목차바로가기)

## O. 실행 모델 & 변수 스코프
- 변수 스코프:
  - [변수 스코프 (global)](./01-변수스코프_global.md)
  - [변수 스코프 (nonlocal과 Closure)](./02-nonloca_Closure.md)
  - [locals](./03-locals.md)
  - [globals](./04-globals.md)
- Shallow Copy & Deep Copy:  
  - [Shallow Copy & Deep Copy](./05-Shallow_Copy%26Deep_Copy.md)
- Context Manger:
  - [Context Manaer](./06-ContextManger.md)
  - [Context Manaer Contextlib](./07-Context_Manager_Contextlib.md)
- 🔼 [맨 위로](#-목차바로가기)
 
## Z. 비동기 프로그래밍 & Coroutine
- [Python Coroutine](./Z.%20비동기%20프로그래밍%20%26%20Coroutine/01-Corouine_개념.md)
- [Concurrent Future submit](./Z.%20비동기%20프로그래밍%20%26%20Coroutine/02-Concurrent_futures.md)
- [Future wait as_completed](./Z.%20비동기%20프로그래밍%20%26%20Coroutine/03-Futures_wait_as_completed.md)
- [AsyncIO Download & HTMLParsing](./Z.%20비동기%20프로그래밍%20%26%20Coroutine/04-AsyncIO_Parsing.md)
- 🔼 [맨 위로](#-목차바로가기)
---



## 검색 팁
- GitHub 파일 검색: `t` 키 → 파일명 일부 입력 (예: `Decorator`)
- 코드/내용 검색: `/` 또는 상단 검색 → `repo:xmlbuilder/PythonTutorial 키워드`

## 기여 가이드
- 오탈자/링크 수정: PR 환영합니다 🙌  


