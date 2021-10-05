# RAII and Memory Management(2) - boost::weak_ptr

예전에 `boost::shared_ptr`에 대한 글을 작성한 적이 있다. 이때, `shared_ptr` 내부 변수 중 `weak_count`에 대한 설명을 작성하려고 구글링했을 때 `weak_count`에 대한 내용은 없고 죄다 `weak_ptr`에 대한 이야기를 하고 있어 당황한 적이 있다. 아마 `weak_count`가 `weak_ptr`과 관련이 있지 않을까 하는 생각이 들어 `shared_ptr`다음 바로 `weak_ptr`을 주제로 포스팅하고자 한다



## Weak?

`weak_ptr`도 스마트 포인터의 한 종류이긴 한데 이름에서부터 시름시름 앓는 소리가 들려오는 것 같다. 맞다. weak_ptr은 이를 의도한 스마트 포인터의 한 종류이다.

이를 설명하기 위해선` shared_ptr`의 reference count에 대한 설명이 필요하다.

### Strong Count (Use count)

`shared_ptr`에서는 간단하게 설명했지만 `shared_ptr` 내부에는 2개의 count 변수가 있다. 하나는 use count라고도 불리는 Strong count, 다른 하나는 weak count이다.

Strong count의 경우 `shared_ptr`에서 참조하고 있는 객체가 몇 개의 다른 `shared_ptr`에서 참조되고 있는지를 나타내는 count이다.

코드를 통해 알아보자

```C++
class DataInfo {
public:
	DataInfo() {
		size = 0;
		permission = 0;
	}

	DataInfo(const std::string &sName, size_t sSize, int sPermission) {
		name = sName;
		size = sSize;
		permission = sPermission;
	}

	~DataInfo() {
		std::cout << "Destroy " << name << std::endl;
	}

	std::string name;
	size_t size;
	int permission;
};

boost::shared_ptr<DataInfo> ptr = boost::make_shared<DataInfo>("Struct", 1, 2);
std::cout << "ptr ref count(1) : " << ptr.use_count() << std::endl;
{
    // 참조 카운터 1 증가
    boost::shared_ptr<DataInfo> ptr2 = ptr;
    std::cout << "ptr ref count(2) : " << ptr.use_count() << std::endl;
    std::cout << "ptr2 ref count(2) : " << ptr2.use_count() << std::endl;
}
// 블럭을 빠져나왔으므로 ptr2는 소멸됨
std::cout << "ptr ref count(3) : " << ptr.use_count() << std::endl;
```

```
ptr ref count(1) : 1
ptr ref count(2) : 2
ptr2 ref count(2) : 2
ptr ref count(3) : 1
Destroy Struct
```

객체를 참조하는 `shared_ptr`이 증가될 때마다 strong count는 증가하며 마지막에는 객체를 참조하는 `shared_ptr`이 모두 삭제되었으므로 본 객체의 소멸자가 호출되는 것을 볼 수 있다.

하지만 strong count만 사용하는 것은 `shared_ptr`가 순환 참조 (deadlock 같은 형태)되는 순간 서로의 소멸을 기다리면서 프로그램이 종료될 때까지 소멸하지 않는 문제가 발생한다. 다음의 코드를 보면 이해할 수 있다.

```c++
class A {
  int *data;
  std::shared_ptr<A> other;

 public:
  A() {
    data = new int[100];
    std::cout << "자원을 획득함!" << std::endl;
  }

  ~A() {
    std::cout << "소멸자 호출!" << std::endl;
    delete[] data;
  }

  void set_other(std::shared_ptr<A> o) { other = o; }
};

int main() {
  std::shared_ptr<A> pa = std::make_shared<A>();
  std::shared_ptr<A> pb = std::make_shared<A>();

  pa->set_other(pb);
  pb->set_other(pa);
}

// 출처 : https://modoocode.com/252
```

pa와 pb를 선언하고 `make_shared`를 사용해 서로 다른 A 객체를 참조시켜 주었다.

선언 시점의 pa와 pb 내부 other은 참조하는 객체가 없기 때문에 ref count가 0이고, pa와 pb는 각각 새로운 A 객체를 할당받았으므로 ref count가 1이다.

![image-20210925232607312](C:\Users\dhjeong\AppData\Roaming\Typora\typora-user-images\image-20210925232607312.png)

//TODO 탭으로 그림 그릴 것

이후 pa의 other에 pb를 할당해주고, pb의 other에 pa를 할당하는 작업을 진행하게 되는데, 이럴 경우 다음과 같은 그림이 된다.

![image-20210925232632513](C:\Users\dhjeong\AppData\Roaming\Typora\typora-user-images\image-20210925232632513.png)

//TODO 탭으로 그림 그릴 것

기존 pa의 ref count 1에다가 pb의 other까지 참조하고 있는 그림이 되어 pa의 ref count는 2가 된다. pb도 마찬가지.

이런 상황에서 소멸 시점이 다가오면 pa 자기 자신은 소멸되나, pb의 other가 아직 소멸되지 않았기 때문에 ref count는 1로 유지되어 pa가 최초에 참조하고 있던 A 객체는 소멸되지 않는다. pb도 마찬가지

이를 순환 참조로 인한 문제라고 하며 내부에 자기 자신을 가리키는 변수가 필요한 자료구조에서는 shared_ptr를 사용할 수 없다.

### weak count

`weak count`는 `shared_ptr`가 객체를 참조하는 횟수가 늘어나도 증가하지 않고 `weak_ptr`이 참조하는 횟수에 따라 증가하고 소멸한다.

또한 이름에서 유추할 수 있듯이, `weak count`의 값이 몇인지 관계없이 `strong count`의 값이 0이 되는 순간 참조하는 객체는 사라지게 된다.

## 사용법

### 어떻게 생성해야 하는지?

weak_ptr은 shared_ptr을 이용해야만 생성될 수 있으며 일반 객체를 사용하여 생성할 수 없다.

```c++
DataInfo info("inside", 123456, 123);
// error: no matching function for call to ‘boost::weak_ptr<DataInfo>::weak_ptr(DataInfo&)’
boost::weak_ptr<DataInfo> weakPtrErr1(info);
// error: no matching function for call to ‘boost::weak_ptr<DataInfo>::weak_ptr(DataInfo*)’
boost::weak_ptr<DataInfo> weakPtrErr2(&info);

// 아래는 모두 정상 빌드
boost::shared_ptr<DataInfo> sharedPtr = boost::make_shared<DataInfo>("Struct", 1, 2);
boost::weak_ptr<DataInfo> weakPtr(sharedPtr);
boost::weak_ptr<DataInfo> weakPtr2(sharedPtr);
```

### 어떻게 사용하는지?

weak_ptr은 shared_ptr처럼 포인터 참조 연산자로 접근할 수 없고, lock() 함수를 사용해 반환되는 shared_ptr 객체로 접근해야 한다

이때 ~~당연하겠지만~~ strong count는 1 증가한다

```c++
boost::shared_ptr<DataInfo2> sPtr = boost::make_shared<DataInfo2>("Struct", 1, 2);
std::cout << sPtr->name << std::endl;
boost::weak_ptr<DataInfo2> weakPtr1 = sPtr;

boost::shared_ptr<DataInfo2> sPtr2 = weakPtr1.lock();
std::cout << sPtr2->name << std::endl;
```

### strong count와의 연관

strong count가 0이 되면 weak count의 수와 관계없이 참조하는 객체는 삭제된다.

```c++
boost::weak_ptr<DataInfo> weakPtr1;
boost::weak_ptr<DataInfo> weakPtr2;
{
    boost::shared_ptr<DataInfo> sPtr = boost::make_shared<DataInfo>("Struct", 1, 2);
    weakPtr1 = sPtr;
    weakPtr2 = sPtr;
}
std::cout << "weakPtr1 lock after block" << std::endl;
boost::shared_ptr<DataInfo> sPtr2 = weakPtr1.lock();

if (sPtr2) {
    std::cout << sPtr2->name << std::endl;
} else {
    std::cout << "sPtr2 NULL" << std::endl;
}
```

```
Destroy Struct
weakPtr1 lock after block
sPtr2 NULL
```

sPtr2를 선언할 때 weakPtr1이 참조하던 sPtr은 블록 탈출 시 소멸되어 strong count는 0이 되고 참조하던 객체는 소멸된다

이때 weak_ptr만 남아있는 상황이라면 lock()을 통해 가리키고 있는 객체에 접근할 경우 빈 shared_ptr 객체가 반환된다.

그러므로 weak_ptr의 lock을 사용해 shared_ptr 객체를 획득한 경우 반드시 NULL check가 필요하다

