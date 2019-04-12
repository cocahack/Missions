# Step3 배열과 객체

## 객체(Object)

객체는 **컨테이너**다. 컨테이너의 내용물은 바뀔 수 있지만, 컨테이너 그 자체가 변하지는 않으므로 항상 같은 객체이다. 객체의 내용물은 `property` 또는 `member` 라고 부르며, 키와 값으로 구성된다. 프로퍼티의 이름은 반드시 `string` 또는 `symbol`이어야 하며 값은 어떤 타입이든 상관없다.

### 생성자

객체를 초기화하는 방법은 2가지가 있다. 객체 리터럴을 값으로 주거나 생성자를 사용하는 방법이다. 생성자에 `null` 이나 `undefined` 가 전달되면 빈 객체를 생성한다.

```javascript
const obj = { key1: 'value1', key2: 'value2' }; // { key1: 'value1', key2: 'value2' }
const obj2 = new Object(); // {}
const obj3 = new Object('value'); // { String: 'value' }
```

### 프로퍼티 추가 / 접근

프로퍼티를 추가하려면  `.`  연산자를 사용하여 프로퍼티에 값을 할당하는 방식으로 할 수 있다. `.` 은 멤버 접근 연산자(member access operator)라고 한다.  올바른 식별자를 `.` 연산자와 함께 사용하면 프로퍼티의 값을 가져올 수 있다. 식별자를 사용하지 않는다면 `[]` 연산자를 사용해서 접근해야 한다. 심볼 프로퍼티에 접근할 때는 `[]` 연산자를 사용해야 한다.

```javascript
let key = 'color';
const SIZE = Symbol();
const obj = {};
obj.color = 'yellow';
obj[SIZE] = 8;
obj.SIZE = 0;
console.log(obj.color); // yellow
console.log(obj[key]); // yellow
console.log(obj[SIZE]); // 8
console.log(obj.size); // 0
```

### 프로퍼티 제거

`delete` 연산자를 사용하여 프로퍼티를 제거한다.

```javascript
delete obj.SIZE;
console.log(obj.SIZE); // undefined
```

### Iteration

객체는 일반적으로 배열처럼 순회가 불가능하지만 일부 메소드나 구문을 통해서 순회할 수 있다. 이때 키가 심볼인 프로퍼티는 포함되지 않으므로 주의해야 한다.

#### Object.entries

`Object.entries` 는 키-값 쌍을 리스트로 반환한다. 리스트에는 열거할 수 있는(enumerable) 프로퍼티만 포함되며 프로토타입 체인의 프로퍼티는 포함하지 않는다. `enumerable property`  란 내부의 `enumerable flag` 의 값이 `true` 로 설정된 프로퍼티로, `simple assignment` 또는 `property initializer` 로 생성된 프로퍼티가 이에 해당된다. 

```javascript
const symbol = Symbol();
let obj = {
    key1: "value1",
    key2: "value2",
    key3: { anotherKey: "value3" },
    key4: [1,2,3,4,5],
}

obj[symbol] = "Not include"

Object.entries(obj).forEach(entry => {
    console.log(entry);
});
/*
[ 'key1', 'value1' ]
[ 'key2', 'value2' ]
[ 'key3', { anotherKey: 'value3' } ]
[ 'key4', [ 1, 2, 3, 4, 5 ] ]
*/
```

#### Object.keys

객체의 키를 배열로 반환한다. 열거할 수 있는 프로퍼티만 배열에 존재한다. 

```javascript
let obj = {
  key1: "value1",
  key2: "value2",
  key3: "value3"
}

console.log(Object.keys(obj)); // ['key1', 'key2', 'key3']
```

#### Object.values

프로퍼티 값의 배열을 반환한다. 역시 열거할 수 있는 프로퍼티만 해당된다.

```javascript
let obj = {
  key1: "value1",
  key2: "value2",
  key3: "value3",
}

console.log(Object.keys(obj)); // ['value1', 'value2', 'value3']
```

#### for…in loop

객체의 열거할 수 있는 프로퍼티를 순회하는데 사용한다. 프로토타입 체인에서 상속된 프로퍼티도 포함된다.

```javascript
const symbol = Symbol();

const obj = { a: 1, b: 2, c: 3, [symbol]: 4};

for(let prop in obj){
  console.log(`${prop}: ${obj[prop]}`);
}
/*
a: 1
b: 2
c: 3
*/
```

#### Object.getOwnPropertyNames

열거할 수 없는 프로퍼티를 포함한 모든 프로퍼티를 반환한다. 그러나 키가 심볼인 프로퍼티는 제외된다.

```javascript
class Super{
  constructor(){
    this.name = 'super';
    this.isSuper = true;
  }
}

Super.prototype.inheritedProperty = 'non-enumerable';

class Sub extends Super{
  constructor(){
    super();
    this.name = 'sub';
    this.isSub = true;
  }
}

const obj = new Sub();

for(let p in obj){
  console.log(`${p}: ${obj[p]}`);
}
```

### 객체의 프로퍼티 속성

프로퍼티에는 객체에서 어떻게 동작할지 결정할 척도인 `attribute`가 존재한다. `Object.getOwnPropertyDescription` 을 사용하면 프로퍼티의 속성을 볼 수 있다.

```javascript
const obj = {name: 'Object'}
console.log(Object.getOwnPropertyDescriptor(obj, 'name'));
/*
{ value: 'Object',
  writable: true,
  enumerable: true,
  configurable: true }
*/

```

속성에 3가지가 존재함을 알 수 있다.

- `writable`:  프로퍼티의 값을 변경할 수 있는지를 나타낸다.
- `enumerable`: `for ... in`  문이나 `Object.keys` , `… `연산자에서 객체 프로퍼티를 나열할 때 해당 프로퍼티를 포함할지 여부를 결정한다.
- `configurable`: 프로퍼티를 객체에서 삭제하거나 속성을 수정할 수 있는지를 결정한다.  

`Object.defineProperty`로 속성을 제어하거나 새로운 프로퍼티를 만들 수 있다.

### Freezing

객체를 동결할 경우 문자열이나 숫자처럼 어느 정도 `immutable` 한 존재가 된다. 객체를 동결할 때는 `Object.freeze` 를 사용하고 확인할 때는 `Object.isFrozen` 을 사용한다. 클래스의 경우 슈퍼 클래스가 물려준 속성까지도 동결되지만 중첩된 객체의 속성까지 동결해주지는 못한다.

```javascript
const frozenObj = Object.freeze({frozen: 'cannot reassignment', b: { frozen: 'can assignment' }});

frozenObj.b.frozen = 'hi';
frozenObj.frozen = 'hi';

console.log(frozenObj); // { frozen: 'cannot reassignment', b: { frozen: 'hi' } }
```

### Freezing, Sealing, Preventing extension 비교

| Action             | 일반 객체 | 동결된 객체 | 봉인된 객체 | 확장 금지된 객체 |
| ------------------ | --------- | ----------- | ----------- | ---------------- |
| 프로퍼티 추가      | O         | X           | X           | X                |
| 프로퍼티 읽기      | O         | O           | O           | O                |
| 프로퍼티 값 설정   | O         | X           | O           | O                |
| 프로퍼티 속성 변경 | O         | X           | X           | O                |
| 프로퍼티 삭제      | O         | X           | X           | O                |



## 배열

자바스크립트 배열의 기본적인 특성을 나열하면 아래와 같다,

- 순서가 있는 데이터 집합이며, 0으로 시작하는 number 타입의 인덱스를 사용한다.
- 배열의 모든 요소가 같을 필요는 없다.
- 요소의 개수를 나타내는 `length` 프로퍼티가 존재한다.
- 배열 길이보다 큰 인덱스의 위치에 값을 할당하면 나머지는 `undefined` 로 채워진다.

### 배열 조작

#### map

일정한 형식의 배열을 다른 형식으로 바꿀 때 사용한다. 원래 배열을 수정하지 않고 새로운 배열을 반환한다. 

```javascript
const prices = [159, 87, 39, 245];
let discountRate = 0.15
const discountPrices = prices.map(x => (1 - discountRate) * x);
```

#### filter

배열에서 필요한 요소만 선택해서 새로운 배열을 반환한다.

```javascript
const prices = [159, 87, 39, 245];
const pricesOver100 = prices.filter(x => x >= 100);
```

#### reduce

각 배열의 요소마다 콜백으로 넘긴 함수를 적용한 뒤 그 결과를 Accumulator에 누적해서 반환하는 함수이다. 파라미터는 콜백함수와 초기값으로 구성된다. 콜백함수의 매개변수는 현재 배열의 요소, 현재 인덱스, 배열 전체이다. 초기값을 정하지 않을 경우 배열의 첫번째 요소가 초기값이 된다.

```javascript
const arr = [5,7,2,4];
const sum = arr.reduce((acc, x) => a += x, 0);
```

#### some

배열의 요소 중 콜백으로 넘긴 함수의 조건을 만족하는 것이 하나라도 존재하면 `true` 를 반환한다.

#### every

배열의 요소 중 콜백으로 넘긴 함수의 조건을 모두 만족해야 `true` 를 반환한다.



## References

[MDN - Object](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object)

[hackernoon - 5 Techniques to Iterate Over JavaScript Object Entries and their Performance](https://hackernoon.com/5-techniques-to-iterate-over-javascript-object-entries-and-their-performance-6602dcb708a8)

[MDN - Enumerability and ownership of properties](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Enumerability_and_ownership_of_properties)

[MDN - Object.getOwnProperty](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/getOwnPropertyNames)

[MDN - Object.getOwnPropertyDescriptor](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/getOwnPropertyDescriptor)