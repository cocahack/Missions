# Step 5. OOP



## 내가 생각하고 있던 클래스와 OOP 관련 용어

### Class

구현하고자 하는 대상의 특성을 분석하여 그 결과로 속성과 행동을 정의하고 이를 다시 코드화 한 것. 

### Encapsulation

외부에서 클래스를 바라볼 때 보여야할 부분(인터페이스)과 그렇지 않은 부분(세부 구현)을 나누는 것.

### Inheritance

이미 정의된 클래스의 속성과 행동을 그대로 사용하는 것. 

### Polymorphism

잘 모르겠다. 같은 클래스라도 여러 형태로 변화할 수 있다는 것인가? 

### Abstaction

구현하고자 하는 대상을 클래스화 시키는 과정 자체를 말하는 것으로 생각한다.

## 실제 정의

### Class

객체가 가지고 있어야 할 것과, 행동을 정의한 것. 대개 이런 형태를 가지고 있다.

```
class <class_name>
{
	field;
	method;
}
```

### Encapsulation

캡슐화는 클래스의 상태나 값을 숨겨서 허용되지 않은 곳에서(unauthorized parties) 직접적으로 접근할 수 없도록 만들 때 사용하는 개념이다. 공개되는 메소드는 값에 접근하기 위해 클래스가 직접 제공하며(getter, setter 등), 주로 다른 클래스에서 객체 내부의 값을 검색하거나 변경하기 위해 이를 사용한다. `public`, `private`, `protected` 와 같은 키워드가 여기에서 생겨난 것 같다.

### Inheritance

클래스의 구현을 다른 클래스를 기반으로 하여 유사한 구조를 유지하는 메커니즘이다. 다른 클래스에서 파생되는 새로운 클래스를 **subclass** 라고 하며 근간이 되는 클래스를 **super class** 또는 **base class** 라고 한다. 상속을 통해 생성되는 객체는 **super class** 의 모든 속성과 행동을 가지게 된다.

### Polymorphism

객체의 다양한 형태를 취할 수 있는 능력이다. **Object is-a Class** 또는 **Object is instance of Class** 라는 말이 어색하지 않다면 다형성을 잘 지켰다고 할 수 있다고 한다.

자바에서 다형성을 구현하는 두 가지 형태가 있다.

- static or compile-time: 자바 등 많은 OOP 언어에서는 같은 클래스 안에 같은 이름을 가지지만 파라미터가 다른 메소드를 여러 개 구현할 수 있다. 이를 **Method overloading** 이라고 부른다. 

```java
public class BasicCoffeeMachine {
    // ...
    public Coffee brewCoffee(CoffeeSelection selection) throws CoffeeException {
        switch (selection) {
        case FILTER_COFFEE:
            return brewFilterCoffee();
        default:
            throw new CoffeeException(
                "CoffeeSelection ["+selection+"] not supported!");
        }   
    }
    public List brewCoffee(CoffeeSelection selection, int number) throws CoffeeException {
        List coffees = new ArrayList(number);
        for (int i=0; i<number; i++) {
            coffees.add(brewCoffee(selection));
        }
        return coffees;
    }
    // ...
}

```

첫 번째 brewCoffee 메소드는 커피 한 잔을 끓이는 행동을 구현했다면, 두 번째 brewCoffee는 같은 커피를 여러 잔 끓이는 것을 구현했다. 

- Dynamic: 런타임에 실행할 메소드를 결정하기 때문에 dynamic이라는 표현이 사용되었다. 상속 관계에서 subclass는 super class의 메소드를 재정의 할 수 있다. Subclass에서의 메소드와 super class에서의 메소드는 같은 이름이지만, 기능적으로는 다르기 때문에 다형성을 구현했다고 할 수 있다.

`BasicCoffeeMachine` 를 상속한 새로운 클래스 `PremiumCoffeeMachine` 을 만들었다고 치자. 코드는 다음과 같다.

```java
import java.util.Map;
public class PremiumCoffeeMachine extends BasicCoffeeMachine {
    public PremiumCoffeeMachine(Map beans) {
        // call constructor in superclass
        super(beans);
        // add configuration to brew espresso
        this.configMap.put(CoffeeSelection.ESPRESSO, new Configuration(8, 28));
    }
    private Coffee brewEspresso() {
        Configuration config = configMap.get(CoffeeSelection.ESPRESSO);
        // grind the coffee beans
        GroundCoffee groundCoffee = this.grinder.grind(this.beans.get(CoffeeSelection.ESPRESSO), config.getQuantityCoffee());
        // brew an espresso
        return this.brewingUnit.brew(
            CoffeeSelection.ESPRESSO, groundCoffee, config.getQuantityWater());
    }
    public Coffee brewCoffee(CoffeeSelection selection) throws CoffeeException {
        if (selection == CoffeeSelection.ESPRESSO)
            return brewEspresso();
        else
            return super.brewCoffee(selection);
    }
}
```

두 클래스 모두 `brewCoffee` 가 각각 구현되어 있다. 코드를 JVM이 실행할 때 `brewCoffee` 는 다음 세 가지 방법으로 실행될 수 있다.

1. Superclass가 Superclass로 참조되는 경우

```java
// create a Map of available coffee beans
Map beans = new HashMap();
beans.put(CoffeeSelection.FILTER_COFFEE,
new CoffeeBean("My favorite filter coffee bean", 1000));
// instantiate a new CoffeeMachine object
BasicCoffeeMachine coffeeMachine = new BasicCoffeeMachine(beans);
Coffee coffee = coffeeMachine.brewCoffee(CoffeeSelection.FILTER_COFFEE);
```

`BasicCoffeeMachine` 으로 인스턴스를 생성하고 이를 `BasicCoffeeMachine` 타입에 할당했다. JVM은 `BasicCoffeeMachine` 의 `brewCoffee` 메소드를 사용할 것이다.

2. Subclass가 Subclass로 참조되는 경우

```java
// create a Map of available coffee beans
Map beans = new HashMap();
beans.put(CoffeeSelection.FILTER_COFFEE,
new CoffeeBean("My favorite filter coffee bean", 1000));
beans.put(CoffeeSelection.ESPRESSO,
new CoffeeBean("My favorite espresso bean", 1000));
// instantiate a new CoffeeMachine object
PremiumCoffeeMachine coffeeMachine = new PremiumCoffeeMachine(beans);
Coffee coffee = coffeeMachine.brewCoffee(CoffeeSelection.ESPRESSO);
```

마찬가지로 `PremiumCoffeeMachine` 의 `brewCoffee` 메소드를 사용할 것이다.

3. Subclass가 Superclass로 참조되는 경우

```java
// create a Map of available coffee beans
Map beans = new HashMap();
beans.put(CoffeeSelection.FILTER_COFFEE,
new CoffeeBean("My favorite filter coffee bean", 1000));
// instantiate a new CoffeeMachine object
BasicCoffeeMachine coffeeMachine = new PremiumCoffeeMachine(beans);
Coffee coffee = coffeeMachine.brewCoffee(CoffeeSelection.ESPRESSO);
```

`PremiumCoffeeMachine` 의 생성자를 사용하고 이를 `BasicCoffeeMachine` 에 할당했어도 여전히 `PremiumCoffeeMachine` 의 인스턴스이다. `BasicCoffeeMachine` 처럼 보일 뿐이다. 컴파일러는 `BasicCoffeeMachine` 의 메소드만 볼 수 있다. 

그러나 코드를 실행하면 JVM은 `coffeeMachine` 이 `PremiumCoffeeMachine` 의 인스턴스임을 알아채고 오버라이드된 메소드를 실행한다. 

### Abstraction

사물이나 어떤 개념에 대한 공통된 특징을 파악하고, 불필요한 속성(구체적인 개념)은 제거하는 과정을 말한다. 

구체적인 개념에 의존할 경우 다음과 같은 코드를 작성하게 될 수 있다. 차량 브랜드라는 세부 사항에 집중하여 코드를 짜게되면 각  브랜드 차량에 대한 엔진오일 교체 방법을 구현해야 한다.

```java
void changeEngineOil(CarType type){
  switch(type){
    case CarType.Benz:
      changeEngineOilOfBenzCar();
      break;
    case CarType.Audi:
      changeEngineOilOfAudiCar();
      break;
    case CarType.BMW:
      changeEngineOilOfBMWCar();
      break;
    ...
  }
}
```

그러나 차량을 `car` 라는 클래스로 만들고 이를 상속받은 새로운 클래스에 엔진오일을 교체하는 메소드를 오버라이딩 하는 방법을 사용할 수도 있다.

```java
public abstract class Car {
  abstract void changeEngineOil;
}
```

```Java
public class BenzCar extends Car{
  void changeEngineOil(){
    // Do something
  }
}
```

```java
void changeEngineOil(Car car){
  car.changeEngineOil();
}

BenzCar benzCar = new BanzCar(); 
changeEngineOil(benzCar);
```

위 코드의 `changeEngineOil(Car)` 메소드는 새로운 종류의 자동차가 탄생해도 `Car`  클래스를 상속하여 클래스를 정의하면 사용할 수 있다. 

## 개인적인 생각

Abstraction과 encapsulation의 개념을 다른 방식으로 정의한 글도 간혹 보였다. 두가지 개념이 뭔가를 가린다는 공통점(?)이 있어서 그런 것이 아닌가 하는 생각이 든다. 

하지만 이번 시간에 정리한 내용을 바탕으로 하면, abstraction은 어떤 대상이나 개념에 대한 필수적인 요소를 뽑아내는 것이고, encapsulation은 객체의 일부 구성요소에 대한 직접적인 접근을 제한하는 것으로 나눌 수 있을 것 같다. 

즉, abstraction은 설계 단계에서 사용해야 할 개념이고, encapsulation은 구현 단계에서 사용해야 할 개념인 것 같다.



## Reference

[클래스 Wiki](https://www.guru99.com/java-oops-class-objects.html)

[캡슐화 Wiki](https://en.wikipedia.org/wiki/Encapsulation_(computer_programming))

[상속 Wiki](https://en.wikipedia.org/wiki/Inheritance_(object-oriented_programming))

[다형성 개념](https://dzone.com/articles/oop-concepts-for-beginners-what-is-polymorphism) 

[Coffee machine 소스](https://github.com/thjanssen/Stackify-OopInheritance/tree/master/CoffeeMachine)

[추상화 개념](https://beginnersbook.com/2013/03/oops-in-java-encapsulation-inheritance-polymorphism-abstraction/)

[추상화 Wiki](https://en.wikipedia.org/wiki/Abstraction_(computer_science))

[OOP 특징](https://gmlwjd9405.github.io/2018/07/05/oop-features.html)