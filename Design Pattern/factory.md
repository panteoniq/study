# 팩토리 패턴
팩토리 패턴은 이름에서 유추할 수 있듯, 공장에서 물건을 생산하듯이 객체를 생산할 수 있도록 하는 패턴이다.

* 객체의 생산을 전담하는 하나의 클래스를 만듦
* 다음의 장점이 있다
  * 객체 생성 코드가 분산된 경우 변경사항에 대한 적용이 오래 걸리는 문제를 보완
  * 신규 클래스에 대한 객체 생성 코드를 factory 클래스에만 적용하면 되므로 외부에서 객체 생성에 대한 내용을 몰라도 된다
  * 클래스 간 결합도를 낮출 수 있다

### 결합도?
결합도는 다음 코드를 통해 알 수 있다

```
class Mouse {
    ...
}

class Keyboard {
    ...
}

class Monitor {
    ...
}

class Desktop {
    Mouse mouse = new Mouse();
    Keyboard kbd = new Keyboard();
    Monitor monitor = new Monitor();
    ...
}

class Server {
    Keyboard kbd = new Keyboard();
    Monitor monitor = new Monitor();
    ...
}

class Labtop {
    Keyboad kbd = new Keyboard();
    Monitor monitor = new Monitor();
    Touchpad pad = new Touchpad();
    ...
}

```
위 코드에서 다음 상황을 고려해보자
* Keyboard 클래스의 생성자에서 매개변수를 받는다면?
* Mouse 클래스가 사라진다면?
  * CLI 환경의 OS에서는 설치과정을 제외하고는 마우스가 필요없다
* Monitor 클래스에서 init 함수를 반드시 호출해야 한다면?

이러한 상황이 발생했을 때 각 클래스마다 전달해야 하는 내용을 정리해야 하며 클래스마다 이러한 데이터를 전달하는 것도 여간 귀찮은 일이 아닐 것이다. 이처럼 한 클래스의 변경사항이 다른 클래스에 얼마나 영향을 미치는지에 대한 정도를 **결합도**라고 부르며, 위와 같은 경우는 ***결합도가 높다***고 부른다.

즉, 좋은 프로그램은 클래스 간 결합도가 낮다는 의미이다
<br>
<br>
<br>

# 종류
## 1. 팩토리 매서드 패턴
그림을 그리는 프로그램을 개발 중이라고 가정하자.<br>
현재는 초기 단계여서, 그릴 수 있는 개체가 원, 사각형, 삼각형 3개가 있다
```
class Shape {
    /*
    * 그림을 그린다
    * 
    * @return
    * 		true : 정상 동작
    * 		false : 동작 중 문제 발생
    */
    virtual bool draw() = 0;
}

class Circle : public Shape {
    bool draw() {
        printf("Draw Circle\n");
        return true;
    }
}

class Square : public Shape {
    bool draw() {
        printf("Draw Square\n");
        return true;
    }
}

class Triangle : public Shape {
    bool draw() {
        printf("Draw Triangle\n");
        return true;
    }
}
```

위에 나열된 객체들을 생성하는 코드를 매우 간단하게 짜면 다음과 같은 코드가 나올 것이다

```
void drawShape(ShapeType type) {
    Shape *shape = NULL;
    if (type == CIRCLE) {
        shape = new Circle();
    } else if (type == SQUARE) {
        shape = new Square();
    } else if (type == TRIANGLE) {
        shape = new Triangle();
    } else {
        printf("Wrong shape type[%d]\n", type);
        return;
    }

    ...
}
```

이 함수가 속한 클래스는 Shape, Circle, Triangle, Square의 변경사항이 생길 때마다 코드를 수정해야 하므로 결합도가 매우 높다.<br>
이때 결합도를 낮추려면 new로 생성하는 부분을 별도 클래스로 분리하면 된다. 이것이 기본적인 factory 패턴인 팩토리 매서드 패턴이다.

```
class ShapeFactory {
    Shape* createShape(ShapeType type) {
        Shape *shape = NULL;
        if (type == CIRCLE) {
            shape = new Circle();
        } else if (type == SQUARE) {
            shape = new Square();
        } else if (type == TRIANGLE) {
            shape = new Triangle();
        } else {
            printf("Wrong shape type[%d]\n", type);
        }

        // 만약 여기에 새로운 클래스를 생성해야 한다면?

        return shape;
    }
}
```


## 2. 추상 팩토리 패턴
위에서 설명한 팩토리 매서드 패턴에서는 팩토리 내부에서 if를 많이 사용하고 있으며,<br>신규 클래스를 생성하려면 팩토리 클래스 내에 코드를 직접 추가해야 한다는 불편함이 있다

위 단점을 보완하기 위해 나온 패턴이 추상 팩토리 패턴이다. 이 패턴은 팩토리 클래스 위에 있는 부모 클래스가 있고 (Java로 치면 슈퍼 클래스) 각 팩토리 클래스에서 이를 상속받아 필요한 코드를 구현하는 방식이다.

부모 클래스는 다음과 같다

```
class BasicShapeFactory {
    virtual Shape* createShape() = 0;
}
```

팩토리 매서드 패턴과 다르게 createShape 함수에서 매개변수를 받지 않는다. 그러면 어떻게 타입을 구분할까?

```
class CircleShapeFactory : public BasicShapeFactory{
    Shape* createShape() {
        return new Circle();
    }
}

class SquareShapeFactory : public BasicShapeFactory{
    Shape* createShape() {
        return new Square();
    }
}

class TriangleShapeFactory : public BasicShapeFactory{
    Shape* createShape() {
        return new Triangle();
    }
}

// 새로운 클래스가 만들어져도 위와 같은 포맷을 맞춰 코드를 작성하면 된다
```

각 클래스 객체를 만드는 팩토리 클래스를 선언함으로써, 각 팩토리 클래스는 타입 구분 없이 자신이 담당하는 클래스의 객체만 생성해서 반환해주면 된다.<br>

```
Shape *circle = m_circleFactory.createShape();
Shape *square = m_squareFactory.createShape();
Shape *triangle = m_triangleFactory.createShape();

circle->draw();
square->draw();
triangle->draw();
```

이것보다 더 간단하게 하려면, 생성만 담당하는 상위 클래스를 하나 생성하여, 각 팩토리 클래스 객체를 매개변수로 전달받아 매개변수로부터 객체를 뽑아내 반환하는 함수를 만드는 것이다<br>

```
class ShapeMaker {
	Shape* getShape(BasicShapeFactory *shapeFactory) {
		if (shapeFactory != NULL) {
			return shapeFactory->createShape();
		}

        return NULL;
    }
}
```