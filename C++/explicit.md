# explicit 키워드

smart pointer를 공부하다가 explicit 키워드가 붙은 함수를 본 적이 있는데 이 부분에 대한 궁금증이 생겨 따로 포스팅을 작성하려고 한다.

우선 explicit의 사전적 개요는 다음과 같다

```
explicit
1. [형용사] 분명한, 명쾌한
2. [형용사] 솔직한, 터놓고 말하는 (=frank)
3. [형용사] 명백한, 노골적인 (→implicit)
```

'분명한'과 '명백한'이라는 단어를 기억해둔 채로, 형변환에 대해 다시 한번 되짚보자



# 형변환

explicit에 대해 설명하다가 갑자기 형변환이 왜 나오나요?<br>

explicit이 형변환과 관련된 키워드이기 때문이다. 우선 형변환의 종류에 대해 알아보자.



## 명시적 형변환

```
int intVal = 2;

float floatVal = (float) intVal;
float floatVal = float(intVal);
```

이처럼 변환할 자료형 (float)를 변환 대상 변수명(intVal) 앞에 붙여주는 것을 명시적 형변환이라고 한다

이렇게 보면 앞에 자료형을 안 붙인 거랑 큰 차이가 없는 것 같다고? 그럼 다음 코드를 보면 이해가 빠를 것이다

```c++
int first = 5;
int second = 2;

float floatVal = first / second;
float floatVal2 = (float) first / second;

std::cout << floatVal << std::endl;
std::cout << floatVal2 << std::endl;

// 결과는
// 2
// 2.5
```

5/2는 우리가 알고있는 상식으로는 2.5가 나오는 것이 맞다. 하지만 명시적 형변환을 하지 않고 float에 결과를 대입하면 소수점 부분이 날아가서 값이 2가 나온다.

같은 자료형끼리 연산하면 형변환이 발생하지 않으므로 계산 전 명시적 형변환을 사용해 변수 중 하나를 형변환시키면 결과는 변환할 자료형으로 바뀌어 나온다 

* 연산자 우선순위처럼 자료형 우선순위라는 게 있진 않지만, 두 값 을 반대로 변환했을 때 값 소실이 있는 자료형이 우선순위가 더 높다고 보면 된다
  * ex) int와 float를 서로 변환할 때 int->float는 값 소실이 없지만 float->int는 값 소실이 있다. 따라서 float가 우선순위가 더 높다

계산기와 같은 프로그램을 짤 때 값의 소실이 일어나선 안 되므로 반드시 명시적 형변환으로 값을 대입해야한다



## 묵시적 형변환

묵시적 형변환은 명시적 형변환과 다르기 때문에 앞에 변환할 자료형을 붙여주지 않고 값을 변환하는 것을 의미한다

위의 `float floatVal = first / second;`에 해당하며 이는 값의 소실을 불러일으킬 수 있기 때문에 묵시적 형변환으로 값을 대입할 경우 값의 소실이 발생할 가능성에 대해 반드시 알아두어야 한다



# 그럼, exlipcit은 뭔가요?

explicit 키워드는 묵시적 형변환을 하지 못하도록 막는 키워드다. 자주 사용되는 예제를 통해 알아보자

## explicit이 없을 경우

```c++
class Tmp {
public:
	Tmp(int num) :
			m_num(num) {
		std::cout << "Tmp 생성자 : " << m_num << std::endl;
	}

	void print() {
		std::cout << "Tmp 내부 값 : " << m_num << std::endl;
	}

private:
	int m_num;
};

void test(Tmp tmp) {
    tmp.print();
}

int main(void) {
    test(10);
}

/*
Tmp 생성자 : 10
Tmp 내부 값 : 10
*/
```

위 코드를 보면 test 함수의 매개변수는 Tmp 클래스의 객체인데 메인 함수에서 test 함수를 호출할 때 그냥 int값을 던져주고 있다.

이는 내부에서 다음 순서대로 동작한다

* test 함수의 매개변수로 int가 전달되면 test 함수로 진입하기 전 컴파일러가 10을 Tmp 클래스 객체로 변환하기 위해 생성자를 호출한다
  * 이때의 호출식은 Tmp tmp = 10, 묵시적 형변환이다
* 묵시적 형변환으로 생성된 객체가 test 함수로 전달되어 처리된다

즉 매개변수 전달 시 묵시적 형변환 과정이 일어난다는 것이다. 이게 가능한가? 싶지만

```c++
// 명시적 형변환
Tmp tmp1 = Tmp(1);
// 묵시적 형변환
Tmp tmp2 = 10;
```

위 두 줄은 모두 정상 동작한다



## explicit이 있을 경우

위 예제에서 explicit을 추가한다면 어디에 추가해야 할까? 묵시적 형변환이 일어나는 부분에 추가해야 하므로, **생성자에 추가해야 한다**

```c++
class Tmp {
public:
	explicit Tmp(int num) :
			m_num(num) {
		std::cout << "Tmp 생성자 : " << m_num << std::endl;
	}

	void print() {
		std::cout << "Tmp 내부 값 : " << m_num << std::endl;
	}

private:
	int m_num;
};

void test(Tmp tmp) {
    tmp.print();
}

int main(void) {
    test(10);
}

/*
error: cannot convert ‘int’ to ‘Tmp’
42 |  test(10);
*/
```

int를 바로 Tmp 객체로 대입할 수 없다는 에러가 발생한다. 따라서 이를 정상 동작시키려면, test 함수 호출 전 Tmp 객체를 하나 만들어서 그걸 전달해줘야 한다

```c++
Tmp tmp(10);
test(tmp);
```

이렇게.



함수로 전달하는 것 외에 explicit을 테스트하는 방법은 하나 더 있다.

```c++
// 명시적 형변환
Tmp tmp1 = Tmp(1);
// 묵시적 형변환
Tmp tmp2 = 10; // rror: conversion from ‘int’ to non-scalar type ‘Tmp’ requested

```

이 친구들이 기억나는지?

explicit을 추가하면 묵시적 형변환에 해당하는 두번째 줄이 에러를 내뱉는다.