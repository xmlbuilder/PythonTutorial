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
- [C. 컬렉션(리스트/튜플/딕셔너리/셋)](#c-컬렉션리스트튜플딕셔너리셋)
- [D. 제어문](#d-제어문)
- [E. 함수 & 함수형 패턴](#e-함수--함수형-패턴)
- [F. 클래스 & OOP](#f-클래스--oop)
- [G. 시퀀스 심화 & 자료구조](#g-시퀀스-심화--자료구조)
- [H. 예외 & 어서션](#h-예외--어서션)
- [I. 표준 라이브러리/모듈/내장함수](#i-표준-라이브러리모듈내장함수)
- [J. 파일 I/O & 입력](#j-파일-io--입력)
- [K. 반복자/이터러블/itertools](#k-반복자이터러블itertools)
- [L. 미니 프로젝트](#l-미니-프로젝트)
- [검색 팁](#검색-팁)
- [기여 가이드](#기여-가이드)

---

## A. 기본 문법 & 출력/형식
- [여러 문장 한 줄에 코딩](./005-여러문장_한줄에코딩.md)
- 타입 힌트: [Type Hint](./006-TypeHint.md)
- 출력과 포맷
  - [print 기본](./007-01-Print.md)
  - [포맷 기본 1](./007-02-PrintFormat.md), [포맷 기본 2](./007-03-PrintFormat.md)
  - [포맷 최신 정리(2023)](./007-04-Print2023.md)
  - [format 함수](./007-05-Format.md), [기타 포맷](./008-01-Format.md)
- 식별자/불리언: [ID](./008-02-ID.md), [None/Bool](./008-10-None_Bool.md)

## B. 데이터 타입 & 기본 연산
- 개요: [자료형 훑어보기](./008-03-자료형.md)
- 숫자형: [숫자형 타입](./008-04-숫자형타입.md)
- 문자열:
  - [문자형 타입](./008-05-문자형타입.md)
  - [문자형 연산](./008-06-문자형연산.md)
  - [슬라이스](./008-07-문자형Slice.md)
  - [불변/변경](./008-08-문자형변경.md)
  - [인코딩/디코딩](./008-09-문자형인코딩디코딩.md)

## C. 컬렉션(리스트/튜플/딕셔너리/셋)
- 리스트: [리스트 기본](./009-01-list.md), [리스트 값 비교](./009-02-list_값비교.md)
- 튜플: [Tuple](./010-Tuple.md), [NamedTuple](./56-Named_Tuple.md)
- 딕셔너리: [Dictionary](./011-Dictionary.md)
- 셋: [Set](./012-Set.md), [frozenset](./63-set_frozenset.md)
- 맵(개념): [Map](./013-Map.md)
- 변경 가능성: [Mutable/Immutable 구분](./014-변경가능여부확인.md)

## D. 제어문
- if: [기본](./016-01-if기본.md), [논리연산자](./016-02-if논리연산자.md), [다중 조건](./016-03-if다중_조건문.md)
- for: [기본](./017-01-for기본.md), [break/continue](./017-02-for_break_continue.md), [for-else](./017-03-for_else.md)
- while: [while](./018-while.md)
- 표현식: [조건부 표현식](./39-Conditional_Expression.md), [switch 스타일](./40-switch.md)

## E. 함수 & 함수형 패턴
- 기초: [함수 정의](./019-함수정의.md), [인자](./020-함수Arugment.md), [lambda](./021-lambda.md)
- 고급: [Currying](./022-Currying.md), [함수 객체 네임스페이스](./023-함수%20객체의%20이름%20공간.md), [메모이제이션](./024-Memoization.md)
- 일급함수/클로저:
  - [First-class function](./64-First_class_Function.md)
  - [global/nonlocal/점수 예제](./65-Score_Closure_Globa_nonlocal.md)
  - [클로저/스코프](./66-Closure_Scope.md)
- 체이닝 & 데코레이터:
  - [함수 체이닝](./67-Function_Chaining.md)
  - [데코레이터 기본](./68-Decorator.md), [가변 인자 데코레이터](./69-Decorator_Variable.md)
  - [클래스 데코레이터](./70-Class_Decorator.md)

## F. 클래스 & OOP
- 기초: [클래스 기본](./026-class_basic.md), [self](./027-class_self.md), [메서드](./028-class_method.md)
- 심화:
  - [bound/unbound 메서드](./45-class_method_bound_method.md)
  - [클래스 메서드 심화](./46-class_method_심화1md.md)
  - [id/dict](./47-class_id_dict_.md)
  - [type과 클래스 메서드](./48-class_method_type.md)
  - [클래스 속성](./49-class_attr.md)
  - [다중 상속](./50-다중_상속.md), [super](./51-super_class.md), [Mixin](./52-Mixin.md)
  - [매직 메서드](./53-MagicMethod.md), [오버로딩](./54-MagicMethodOverloading.md)
- 실습: [Vector 클래스 만들어보기](./55-Vector클래스_만들어보기.md)
- 이터러블/이터레이터: [Iterable](./71-Iterable.md), [Iterator/Generator](./72-Iterator_Generator.md)

## G. 시퀀스 심화 & 자료구조
- [지능형 시퀀스](./57-Sequence_지능형.md)
- [Array](./58-Array.md)
- [Shallow/Deep Copy](./59-Sequence_Swallow_Deep_Copy.md)
- [Mutable 개념](./60-Sequence_Concept(Mutable).md)
- [해시테이블](./61-Sequence_HashTable.md)
- [Immutable Dict](./62-Sequence_Imutable_Dict.md)

## H. 예외 & 어서션
- [예외 개요](./30-exception.md), [try/except](./31-try_except.md)
- [assert](./37-assert.md), [warnings](./38-waring.md)

## I. 표준 라이브러리/모듈/내장함수
- [모듈](./029-module.md)
- [내장 함수](./32-내장함수.md), [외장 함수(표준 라이브러리)](./33-외장함수.md)

## J. 파일 I/O & 입력
- [입력 input()](./025-Input.md)
- 파일 다루기:
  - [읽기 기본](./34-File_Read.md)
  - [with open 패턴](./35-File_With_Open.md)
  - [CSV/JSON 쓰기](./36-File_With_Write_CSV_JSON.md)

## K. 반복자/이터러블/itertools
- [즉시 실행 vs 단계별 실행](./94-즉시실행_단계별_실행.md)
- [itertools 요약](./95-itertools.md)

## L. 미니 프로젝트
- [특정 인덱스 찾기 구현](./41-특정인덱스_찾기_구현.md)
- [행맨 만들기](./42-Hangman_만들어보기.md) → [개선안](./43-Hangman_개선.md)

---

## 검색 팁
- GitHub 파일 검색: `t` 키 → 파일명 일부 입력 (예: `Decorator`)
- 코드/내용 검색: `/` 또는 상단 검색 → `repo:xmlbuilder/PythonTutorial 키워드`

## 기여 가이드
- 오탈자/링크 수정: PR 환영합니다 🙌  
- 파일명은 **번호-제목.md** 형식을 유지해주세요.  
- 주제 추가 시, 위 목차 섹션에 **상대경로 링크**를 함께 추가해주세요.

