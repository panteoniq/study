# Data Structure (1) - Boost::any
Boost::Any는 변수를 <b>익명화</b>하는 API다. 변수가 본래 갖고 있던 자료형을 숨겨주는 기능을 한다고 보면 된다.<br>
C++에서 종종 볼 수 있는 제네릭과 매우 유사하며, 런타임 시점에서의 다형성을 보장하기 위한 API이다.<br>
그래서 Any 변수에는 int도 저장할 수 있고, String도 저장할 수 있고, 구조체도 저장할 수 있고, 뭐든지 저장할 수 있다.<br> ~~이거 완전 자바스크립트 아니냐~~

하지만 다음의 이유로 그닥 사용을 추천하지는 않는다.<br>
* 쓰려면 캐스팅 함수를 통해 다시 원래 유형으로 돌려놔야 한다
  * 이때 any에 저장된 변수가 무엇인지 특정하기 위한 검사 과정이 필요하게 된다
* C++의 특성상 연산자 오버로딩을 하지 않거나 순수 타입 간에는 자료형을 변경할 수 없다.
  * string은 int가 될 수 없고 int는 vector가 될 수 없다.
  * 자동 형변환을 지원하지 않기 때문에 int에서 short로 동종 간 형변환마저도 기본 캐스팅 함수로는 진행할 수 없다. <br> 하려면 특별한 캐스팅 함수를 사용해야 하며 이 캐스팅 함수는 이름에서부터 불길한 기운(unsafe)이 느껴진다
* 마피아 게임도 아니고, 타입이 중요한 C++에서 변수 자료형의 익명화는 그닥 반가운 특징이 아니다.<br>any를 사용해서 자료를 짬뽕하여 저장했더라도 언젠간 원래 모습으로 돌아가야 한다.
<br>
<br>
# 사용 방법
## 1) 변수 -> any
```c++
#include <boost/any.hpp>

int intVal = 333;
boost::any anyInt(intVal);

std::string stringVal = "Hello World!";
boost::any anyString(stringVal);
```
any로 변환할 변수를 생성자로 전달하면 된다.
<br>
<br>

## 2) any -> 변수
### 동일 자료형으로 복구
```c++
#include <boost/any.hpp>

// 일반 변수로 변환하려면 매개변수도 일반 변수여야 한다
std::string strConv1 = boost::any_cast<std::string>(anyString);
// 일반변수 -> 포인터로 변환하려면 매개변수에 주소값을 던져줘야 한다
std::string *strConv2 = boost::any_cast<std::string>(&anyString);

int intConv1 = boost::any_cast<int>(anyInt);
int *intConv2 = boost::any_cast<int>(&anyInt);


std::cout << "strConv1 : " << strConv1.c_str() << std::endl;
std::cout << "strConv2 : " << strConv2->c_str() << std::endl;
std::cout << "intConv1 : " << intConv1 << std::endl;
// 포인터로 받았으니 참조연산자 *로 실제 값으로 출력해야 함. 그렇지 않으면 주소값 출력됨
std::cout << "intConv2 : " << *intConv2 << std::endl;
```

결과

```c++
strConv1 : Hello World!
strConv2 : Hello World!
intConv1 : 333
intConv2 : 333
```

`any_cast`의 특징은 다음과 같다

* 매개변수로 일반 변수 및 포인터 변수를 모두 받을 수 있다
  * 반드시 반환형은 매개변수와 동일한 자료형으로 지정해야 한다. 매개변수가 int인 경우 반환형도 int, 매개변수가 int\*인 경우 반환형도 int\*로 해야 한다.
  * 만약 cast에 실패한 경우 cast 대상의 자료형에 따라 다음과 같이 동작한다
    * 일반 매개변수 : exception이 발생한다. catch 구문을 사용하여 exception에 대한 상세 설명을 확인해야 한다
    * 포인터 매개변수 : NULL을 반환한다. 따라서 포인터를 반환받을 경우 반드시 null check를 진행한다



### 유사한 자료형으로 복구

```c++
// unsafe_any_case의 매개변수는 무조건 포인터 변수여야 한다
// 따라서 반환형도 무조건 주소값이다
//short shortConv1 = boost::unsafe_any_cast<short>(anyInt); // 에러남
short *shortConv2 = boost::unsafe_any_cast<short>(&anyInt);
short *shortConv3 = boost::unsafe_any_cast<short>(&anyInt);

//std::cout << "shortConv1 : " << shortConv1 << std::endl;
std::cout << "shortConv2 : " << *shortConv2 << std::endl;
std::cout << "shortConv3 : " << *shortConv3 << std::endl;
```

결과

```c++
shortConv2 : 333
shortConv3 : 333
```

우리는 정수형 변수 간에 자료형을 굳이 따지지 않고 잘 사용해왔지만 any_cast는 무조건 any 저장 전 자료형으로만 정상 변환이 가능하다. 이러한 상황을 용납할 수 없다면, `unsafe_any_cast`로 서로 다른 자료형 간의 변환을 시도해보자.

`unsafe_any_cast`는 다음과 같은 특징을 갖고 있다

* 말 그대로 정말 unsafe하기 때문에 에러를 일으킬 만한 변환에 대해서도 결과값을 반환해준다.
  * 즉, NULL을 반환하지 않기 때문에 이에 대해 접근을 시도할 경우 segfault가 발생한다. NULL check와 같은 방어코드가 소용없으므로 해당 API를 사용해 변환할 경우 정말 원래 자료형과 유사한 자료형인지 확인해야 한다
* `any_cast`와 달리 매개변수를 포인터 변수로만 받는다. 일반 변수로 `unsafe_any_cast`를 진행할 경우 빌드 에러가 발생한다



## 타입을 알려면 어떻게 해야 하지?

간단한 코드인 경우 any_cast 전 해당 변수가 어떤 자료형이었는지를 쉽게 찾을 수 있겠지만 웬만해선 any로 저장되어 있는 변수가 어떤 자료형이었는지 찾기가 힘들다. 이를 boost에서도 잘 알고 있어서, boost의 any 예제 코드를 보면 타입을 체크할 수 있는 함수 몇 개가 등장한다.

```c++
bool is_empty(const boost::any & operand) {
    return operand.empty();
}

bool is_int(const boost::any & operand) {
    return operand.type() == typeid(int);
}

bool is_char_ptr(const boost::any & operand) {
    try {
        any_cast<const char *>(operand);
        return true;
    } catch(const boost::bad_any_cast &) {
        return false;
    }
}

bool is_string(const boost::any & operand) {
    return any_cast<std::string>(&operand);
}
```



# 결론

자바스크립트처럼 변수를 지정할 때 자료형의 제약을 두지 않도록 한다는 개념 자체는 흥미롭다. 하지만 하나의 자료형은 같은 자료형끼리 연산을 해야 하고, 그러기 위해서는 오히려 자료형을 가리는 것보다 드러내는 것이 개발하기가 더욱 수월할 것이다. 

클래스 객체, 구조체, 사용자 지정 자료형(typedef) 등 수많은 자료형에 대해서 check하는 함수를 만들어야 할 만큼 boost::any가 효율적이고 도움이 되는 존재일지? 난 잘 모르겠다.









