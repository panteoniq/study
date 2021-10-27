# C++11의 새 기능(1) - auto 키워드 / decltype 키워드

필자가 대학교에 입학하고 c언어를 처음 배울 때, 변수 선언을 위해서는 반드시 변수가 저장될 특정 자료형을 앞에 명시해야 했었다.

```c++
int a = 0; // 정수는 int
std::string str = "Hello World!"; // 문자열은 std::string
struct TestStruct structObj(1,2,3); // 구조체
Shape *shape = new Shape("Circle", 2.3) // 클래스
```

하지만 c++11을 기준으로 많이 사용하게 되는 auto 키워드는 변수 앞에 자료형을 컴파일러가 컴파일 시점에 자동으로 추론해준다는 특징을 갖고 있다. 

![image-20210928201619544](C:\Users\dhjeong\AppData\Roaming\Typora\typora-user-images\image-20210928201619544.png)

(a는 아직 선언조차 안 된 시점인데 자료형이 int로 정의되어 있다)

사실 c++98에서도 auto 키워드가 있으나 c++98에서의 auto 키워드는 구글링해도 자료가 잘 나오지 않고, 설명된 내용으로 보면 `지역변수`에 한정되어 있는 느낌을 강했다. 하지만 c++11에서 auto는 새로 개편되었다고 봐도 무방할 정도의 특징을 보여준다.

## 사용법

### 일반 변수

위의 캡처에서 알 수 있듯 우리가 평소에 변수 선언하는 것처럼 선언하면 된다

```c++
auto a = 1;
auto b = 1.1;
auto c = "test string";
```

### 참조/포인터 변수



### 클래스/구조체/공용체

```c++
// 클래스 정의와 동시에 변수 한 개 선언
// 구조체나 공용체, 클래스도 가능함
class Test {
public:
	int a;
} tt;

// 1. 아래 변수는 Test 클래스 객체인지 알 수 없기 때문에 잘못된 선언 방식이다
auto TestObj;

// 2.
auto autoClass = tt;
autoClass.a = 3;
std::cout << autoClass.a << std::endl;

// 3.
Test t2;
auto autoClass2 = t2;
autoClass2.a = 1010;
std::cout << autoClass2.a << std::endl;
```

auto에 클래스 객체를 담을 경우 반드시 기존에 존재하는 객체를 담아야 하므로 1번과 같은 선언은 잘못된 선언이다

auto는 할당되는 값에 따라 컴파일 시점에 타입을 정해주는 키워드인데, 할당되는 값 없이 auto만 선언하면 컴파일러가 어떤 자료형인지 알 수 있을까?

2번은 클래스 정의와 동시에 선언된 변수를 할당한 auto 변수다. 이는 올바른 사용법이며 컴파일 및 실행도 정상적으로 진행된다

3번은 클래스 객체를 별도로 선언하고, 이를 auto에 할당한 변수이다. 이 또한 올바른 사용법이며 컴파일 및 실행도 정상적으로 진행된다

### 함수 및 람다함수

```c++
//함수포인터나, 함수 자체도 가능함 -> 이러한 함수를 람다 함수라고 함
//함수 포인터 -> 구조체나 클래스의 함수 포인터도 가능
int test2(int a) {
	return a;
}

// 1번
auto autoFn = test2;
std::cout << autoFn(7) << std::endl;

// 2번
auto autoFnLambda = [] {
    std::cout << "hello wolrd" << std::endl;
};
autoFnLambda();

// 3번
auto autoFnLambda2 = [](int a) {
    return a;
};
std::cout << autoFnLambda2(7) << std::endl;

// 4번
auto autoFnLambda3 = [&](int a) {
    int c = b + a;
    return c;
};
std::cout << autoFnLambda3(10) << std::endl;
```

1번 : 일반 함수를 auto 변수에 할당하는 것은, 그 함수의 포인터를 auto 변수에 할당하는 것과 동일하다. 이렇게 할당된 auto 변수는 원래 함수와 동일한 형태로 사용할 수 있다

2, 3, 4번 : 별도의 함수 선언부 없이 할당 시점에 원형이 정의되는 함수를 람다 함수라고 하며, 위와 같은 람다함수의 형태도 auto 변수에 할당할 수 있다.

## auto 키워드를 사용 불가능한 경우

### 함수의 매개변수

```c++
void notAuto (auto a, auto b) {
	std::cout << a+b << std::endl;
}

// c++11 이하 : error: use of ‘auto’ in parameter declaration only available with ‘-std=c++14’ or ‘-std=gnu++14’
// c++14 이상 : warning: use of ‘auto’ in parameter declaration only available with ‘-fconcepts’
notAuto(2,3.2);
```

사용 불가능하다고 적어놓긴 했지만 c++14 이상에서는 컴파일 시 경고가 출력되고 실제로는 사용이 가능하다. 어쨌든 매개변수에 전달되는 값은 자료형이 특정된 상태이기 때문에 동작이 가능한 것으로 보인다

### 클래스/구조체/공용체의 멤버변수

## auto 키워드를 사용할 수 있으나 사용에 주의가 필요한 경우

### 함수의 반환형

# decltype 키워드

