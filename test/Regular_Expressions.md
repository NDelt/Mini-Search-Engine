# 정규 표현식 내용 정리
## 정규 표현식(Regular Expression)이란?
정규 문자열이 주어진 규칙에 식별하는지 파악하기 위한 식

## 정규 문자열
선형적인 규칙을 연달아 적용할 수 있는 문자열
* ex) a를 최소 한 번 사용 + 그 뒤에 b를 짝수 번 사용 + 마지막에 d가 있어도 되고 없어도 됨
* 왼쪽부터 오른쪽까지 일직선으로 규칙을 적용할 수 있는 문자열이면 정규 문자열이라고 부른다.
* '회문 작성'과 같은 규칙은 정규 문자열에 적용할 수 없다. 문자열의 앞과 뒤를 동시에 파악해야 하므로, 선형적이지 않기 때문이다.

## 정규 표현식의 예시
### 1.
>aa*bbbb(cc)*(d| )(a*b)*
* aa*
  * 먼저 a가 등장했으므로 한 개의 a는 반드시 있어야 한다. 그 뒤의 a*는 a가 몇 개든(0개여도) 상관없다는 뜻이다.
  * 따라서 a의 최소 개수는 1개가 된다. 또한, `*` 기호는 맨 앞에 올 수 없다.
* bbbb
  * 4개의 b가 반드시 등장한다.
* (cc)*
  * c의 쌍이 임의의 숫자만큼 존재한다. 즉 c의 개수는 0, 2, 4, 12, 20, ...처럼 2의 배수가 된다.
* (d| )
  * '|'는 OR 연산자이다. d와 공백 사이에 `|`가 쓰였으므로 d가 한 개 있을 수도 있고, 공백만 있을 수도 있다.
  * 또한 정규 표현식을 평가(Evaluate)할 때는 이처럼 소괄호로 묶은 하위 표현식이 가장 먼저 평가된다.
* (a*b)*
  * 임의의 개수 a와 b의 쌍이 임의의 개수만큼 나타난다.(매번 동일한 개수로 쌍이 생성되는 게 아니다.)
  * 예를 들어 aabaaaab와 같은 문자열을 들 수 있다. 첫 번째 쌍은 a가 2개이고, 두 번째 쌍은 a가 4개인 것이다.

### 2.
* ACB.*
  * ACBbfkg, ACB367cNM
  * `.*` 기호가 사용되었으므로, 이는 문자열 ACB 뒤에 임의의 문자(숫자 포함, 개행 문자 제외)가 임의의 개수만큼 나타난다는 의미이다.
  * `ACB*`와는 다른 정규 표현식이다. `ACB*`는 문자열 AC 뒤에 B가 0번 이상 나타난다는 뜻이기 때문이다.
* [a-z].*
  * aAQR, vj01EV
  * 영문 소문자 `a~z` 중 하나의 문자 뒤에 임의의 문자가 임의의 개수만큼 나타난다.
* [A-Za-z]*.*
  * 영문 대소문자 중 하나가 임의의 개수만큼 나타나고, 그 뒤에 또다른 임의의 문자가 임의의 개수만큼 온다는 뜻이다.
  * 즉, 숫자로 시작하는 경우를 제외하면 사실상 모든 문자열과 일치하게 된다.

### 3-1
>^(https|http|www)((?!oreilly.com).)*$
* ^(https|http|www)
  * 문자열의 맨 앞에는 https, http, www 중 하나가 와야 한다.
* ((?!oreilly.com).)*$
  * ^(...)의 바로 뒤에는 `oreilly.com`이 배제된 임의의 문자열이 나타나고, 종료된다.

### 3-2
>^(https|http|www)((?!oreilly.com).)*
* ^(https|http|www)
  * 문자열의 맨 앞에는 https, http, www 중 하나가 와야 한다.
* ((?!oreilly.com).)*
  * ^(...)의 바로 뒤에는 `oreilly.com`이 배제된 임의의 문자열이 나타난다.
  * 그러나 이 문자열이 마지막이라는 뜻은 없으므로, oreilly.com~ 이전의 `https://www.`까지는 주어진 정규 표현식과 일치하게 된다.


### 4.
>이메일 주소를 식별하는 정규 표현식: [A-Za-z0-9\._+]+@[A-Za-z]+\.(com|org|edu|net)
* [A-Za-z0-9\.+]+
  * 영문 대문자 `A~Z`, 소문자 `a~z`, 숫자 `0~9`, 마침표, 그리고 덧셈 기호가 이메일 주소의 앞부분(`@` 이전)에 올 수 있다.
  * 마침표의 경우, 단순히 `.`만 적으면 "개행 문자를 제외한 모든 문자"를 의미하게 된다.
  * 오직 마침표만 오게 하려면 이스케이프 문자를 포함한 `\.`을 사용해야만 한다.
  * 대괄호([])를 사용하면 "대괄호 안에 들어 있는 문자들 중 임의의 문자 하나"라는 뜻이 된다.
  * 대괄호 바깥의 덧셈 기호는, 바로 앞에 있는 것(여기서는 대괄호 내 임의의 문자)이 최소 한 번 이상은 나타난다는 의미이다.
* @
  * 이메일 주소의 중간에는 반드시 `@` 기호가 나타나야 한다.
* [A-Za-z]+
  * `@` 이후 도메인의 첫 부분에는 영문 대문자 A~Z, 소문자 a~z가 올 수 있다.
  * 그리고 그 문자들 중 한 개가 최소 한 번 이상 나타나야 한다.
* .
  * 도메인의 첫 부분 다음에는 반드시 마침표가 와야 한다.
* (com|org|edu|net)
  * 도메인의 두번째 부분에는 com, org, edu, net 중 하나가 올 수 있다.(실제로는 더 많은 도메인이 사용된다.)

## 기타 정규 표현식 기호
* {m, n}
  * 이 중괄호 앞에 있는 문자들은 m번 이상 n번 이하로 나타난다.
  * a{2, 3}b{2, 3}: aabb, aabbb, aaabb, aaabbb
  * [A-Z]{2, 3}: AAA, BB
  * 중괄호 앞에는 `+`, `^`, `*` 문자가 올 수 없으며, 뒤에는 `*` 문자가 올 수 없다.
* ^
  * 이 기호 뒤에 있는 문자나 하위 표현식은 반드시 문자열의 맨 앞에 나타난다.
  * ^a: apple, a, asdf
  * ^(e|d): egg, demon
* [^]
  * `^` 기호 뒤에 있는 문자를 제외한 문자가 나타난다.
  * [^A-Z]*: lowercase, qwerty (영문 대문자를 제외한 문자들 중 하나가 0번 이상 나타난다.)
* $
  * 이 기호 앞에 있는 문자 또는 하위 표현식이 문자열의 마지막임을 나타낸다.
  * [A-Za-z]*$: ABCabc, abDEF ('aB012'의 경우 불일치하는 식이 된다. 대괄호에 포함되지 않은 숫자가 나타났기 때문이다.)
* ?! - 이 기호 뒤에 있는 문자 또는 하위 표현식은 해당 순서에 등장하지 않는다. 소괄호로 전체를 묶어줘야만 정확하게 인식된다.
  * [A-Za-z]*(?!:)B$: 영문 알파벳이 임의의 개수만큼 나타나고, 알파벳 바로 뒤에는 `:`이 나타나지 않고, B로 문자열이 끝난다.
