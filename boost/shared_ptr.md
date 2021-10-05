# RAII and Memory Management(1) - boost::shared_ptr

RAII란 Resource Acquisition Is Initialization, '자원 할당은 초기화'의 줄임말이다. 이는 별도의 포스팅으로 다룰 예정이므로 깊게는 얘기하지 않고 짧게 얘기해주자면, `한 번의 선언만으로 번거로운 절차를 거치지 않고 자원 할당 및 반환을 자동으로 할 수 있게 해주는 기법`이라고 보면 된다. 이 중 가장 널리 사용되는 boost의 API인 shared_ptr에 대해서 설명하고자 한다. 이는 C++11 표준에 추가되었다.



## SHARED?

공유 포인터라는 말만 들으면 이게 무슨 소린가 싶다. 포인터는 주소값을 갖고 있고, 그러면 당연히 여러 곳에서 공유할 수 있지 않나? 싶지만 `shared_ptr`은 단순히 포인터에 대한 '공유'를 위해 탄생한 것이 아니다.



### 그럼 공유는 무슨 의미지?

`shared_ptr`은 스마트 포인터 중 하나이다. 스마트 포인터는 `포인터 변수에 할당되는 자원의 효율적인 반환`을 위해 등장한 개념이며 초기 `unique_ptr`에서 시작해 `auto_ptr`을 지나 발전을 거듭하여 `shared_ptr`에 다다랐다. (이후 `weak_ptr`도 나타나는데 이것 또한 별도의 포스팅으로 다룰 예정)



`shared_ptr`에서 말하는 '공유'는 '포인터 객체를 몇 명이서 참조하고 있는지?'와 동일한 내용이라 보면 된다. 

즉 `shared_ptr`의 내부에는 자신이 감싸고 있는 포인터 변수에 대한 참조 카운터가 있다.

어느 곳에서든 이 포인터 변수를 참조하게 된다면 참조 카운터는 증가하게 되고, 참조를 그만둔다면 (소멸한다면) 참조 카운터는 감소하게 되어, 최종적으로 참조 카운터가 0이 된다면 `shared_ptr` 변수는 자동 삭제된다

# 사용법

대표적인 사용법은 다음 3가지로 볼 수 있다

```c++
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <string>

typedef struct DataInfo {
	std::string name;
	size_t size;
	int permission;

	DataInfo() {
		size = 0;
		permission = 0;
	}

	DataInfo(const std::string &sName, size_t sSize, int sPermission) {
		name = sName;
		size = sSize;
		permission = sPermission;
	}
} DataInfo;

int main() {
    // 1번
	boost::shared_ptr<DataInfo> infoPtr(new DataInfo());
    // 2번
   	DataInfo info;
	boost::shared_ptr<DataInfo> infoPtr2 = boost::make_shared<DataInfo>(info);
    // 3번
	boost::shared_ptr<DataInfo> infoPtr3 = boost::make_shared<DataInfo>("testName3", 1234, 655);
}
```

### 1번 

* 생성자의 매개변수로 new로 생성된 포인터 변수를 전달한다
  * `template<class Y> explicit shared_ptr(Y * p);`

### 2번

* 생성자의 매개변수로 기존 객체를 전달한다
  * `make_shared`는 전달받은 객체 정보를 바탕으로 새로운 `shared_ptr` 변수를 반환하는 함수
  * 매개변수로 전달된 객체가 아닌 새로 생성된 객체를 전달한다. 내부에서 new로 포인터 변수를 생성 후 값을 복사해준다고 생각하면 편하다
    * 따라서 생성 이후 기존 객체의 값이 바뀌더라도 `shared_ptr`로 생성된 객체의 데이터는 변하지 않는다
  * 실제로 `make_shared`의 반환형은 `boost::shared_ptr`이다
    * `return boost::shared_ptr< T >( pt, pt2 );`

### 3번

* 생성자의 매개변수로 객체 생성자에 일치하는 데이터를 전달한다
  * 이 경우 `make_shared` 내부에서 새로운 포인터 객체를 생성할 때 생성자에다 매개변수의 데이터를 전달해준다



### 포인터 변수는 전달할 수 없는가?

가능하다. 다만 다음과 같은 에러가 발생할 수 있으니 조심해야 한다

```c++
int main() {
    DataInfo *info = new DataInfo("test", 1234, 644);
    
    // no matching function for call to ‘make_shared(DataInfo*&)’
	boost::shared_ptr<DataInfo> infoPtr = boost::make_shared(info);
	// no matching function for call to ‘make_shared(DataInfo&)’
	boost::shared_ptr<DataInfo> infoPtr2 = boost::make_shared(*info);
	// conversion from ‘DataInfo*’ to non-scalar type ‘boost::shared_ptr<DataInfo>’ requested
	boost::shared_ptr<DataInfo> infoPtr3 = info;
    // 정상 처리!
    boost::shared_ptr<DataInfo> infoPtr4(info);
}
```

shared_ptr에 포인터 변수를 전달할 경우 make_shared를 사용할 수 없는 것으로 보인다. make_shared의 생성자를 봐도

```c++
namespace boost {

  template<typename T> class shared_ptr;

  template<typename T>
    shared_ptr<T> make_shared();

  template<typename T, typename A>
    shared_ptr<T> allocate_shared( A const & );

#if !defined( BOOST_NO_CXX11_VARIADIC_TEMPLATES ) && !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )    // C++0x prototypes

  template<typename T, typename... Args>
    shared_ptr<T> make_shared( Args && ... args );

  template<typename T, typename A, typename... Args>
    shared_ptr<T> allocate_shared( A const & a, Args && ... args );

#else // no C++0X support

  template<typename T, typename Arg1 >
    shared_ptr<T> make_shared( Arg1 const & arg1 );
  template<typename T, typename Arg1, typename Arg2 >
    shared_ptr<T> make_shared( Arg1 const & arg1, Arg2 const & arg2 );
// ...
  template<typename T, typename Arg1, typename Arg2, ..., typename ArgN >
    shared_ptr<T> make_shared( Arg1 const & arg1, Arg2 const & arg2, ..., ArgN const & argN );

  template<typename T, typename A, typename Arg1 >
    shared_ptr<T> allocate_shared( A const & a, Arg1 const & arg1 );
  template<typename T, typename A, typename Arg1, typename Arg2 >
    shared_ptr<T> allocate_shared( Arg1 const & arg1, Arg2 const & arg2 );
// ...
  template<typename T, typename A, typename Arg1, typename Arg2, ..., typename ArgN >
    shared_ptr<T> allocate_shared( A const & a, Arg1 const & arg1, Arg2 const & arg2, ..., ArgN const & argN );

#endif
}
```

중간에 define으로 지정된 내용을 제외하고 생성자의 매개변수로 포인터 변수를 받는 부분은 없다.<br>

이때 중간에 define으로 지정된 내용은 가변 템플릿을 이용한 생성자이며 포인터를 매개변수로 받을 수 있도록 지원하는 것 같은데... 사용하는 경우를 본 적이 없어서 잘 모르겠다. 어설프게 적었다가 실제로 내용이 다르면 어떡할까 싶어서 생략한다.

# 내부 구조

shared_ptr의 내부 구조는 다음과 같이 되어있다

![image-20210923225504805](C:\Users\dhjeong\AppData\Roaming\Typora\typora-user-images\image-20210923225504805.png)

디버거로 확인해보면 다음과 같이 구성되어 있다

![image-20210923225625633](C:\Users\dhjeong\AppData\Roaming\Typora\typora-user-images\image-20210923225625633.png)

## px

`shared_ptr`가 실제로 가리키고 있는 객체의 주소를 반환한다. `shared_ptr`에 `-> `연산자를 사용해 접근하는 것은 사실 `px`에 접근하는 것과 동일하다.



## pn (pi_)

`pn`은 `pi_`라는 1개의 요소로 구성되어 있으며 이후 서술되는 내용에서 `pn`은 `pi_`와 동일하다.

### boost::detail::sp_counted_base

이는 하위에 2개의 count 변수를 갖고 있다

#### use_count_

`use_count_`변수는 this를 포함한 몇 개의 shared_ptr 객체가 동일한 대상을 참조하고 있는지를 나타낸다. 

참조하는 대상이 있는 경우 최소 값은 1이며 만약 shared_ptr만 선언되었고 참조하는 객체가 없을 경우 0으로 지정된다.

이는 use_count() 함수로 확인할 수 있다.

```c++
void SharedPtr::inside(boost::shared_ptr<DataInfo> &ptr) {
	ptr = boost::make_shared<DataInfo>("Struct", 1, 2);
	ptr->name = "outside";

	boost::shared_ptr<DataInfo> ptr2 = ptr;
	std::cout << ptr2->size << std::endl;
	std::cout << "Inside count ---" << std::endl;
	std::cout << ptr.use_count() << std::endl;
	std::cout << ptr2.use_count() << std::endl;
	boost::shared_ptr<DataInfo> ptr3;
	std::cout << ptr3.use_count() << std::endl;
}
```

```
Inside count ---
2
2
0
```

#### weak_count_

코드는 존재하나.. 상세한 설명을 적은 내용을 찾을 수 없었다.

다만 검색했을 때 weak_ptr과 엮이는 걸 봤는데, weak_ptr에 관련 내용이 있을 수도 있겠다는 생각이 들었다.

weak_ptr에 대해서는 별도 포스팅으로 설명하겠다.



### ptr



### del









참고자료

https://pknam.tistory.com/14

https://202psj.tistory.com/1408

http://egloos.zum.com/hellpme/v/1543080

