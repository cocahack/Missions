# Step 2. 다각형의 넓이

## 올바른 결과 출력해보기

## 첫번째 시도

에러 메시지: `TypeError: sum is not a function`

```javascript
// main.js
const sum = require("util");

function runProgram(arr) {
    const result = sum(arr);
    return `result is ${result}`;
}

const result = runProgram([undefined, 1,2,3,4,5,-1,"3"]);
console.log(result); //result is 14
```

```javascript
//util.js
(function callModuleChecker(){
    result = new Date();
    console.log("WELCOME UTIL MODULE : " + result);
})();

module.exports.sum = (arr) => {
    result = result || 0;

    for (const i = 0; i < arr.length; i++) {
        if (typeof arr !== undefined) continue;
        result += arr[i]
    }

    return result;
}
```

원인: `main.js` 의 첫번째 줄에서 `util` 모듈을 불러올 때 받은 것이 함수가 아닌 객체임.

해결방법: `require` 의 argument로 파일의 경로를 올바르게 써 주고, `module.exports` 의 `sum` 프로퍼티를 받아오도록 수정함. 

### 두번째 시도

출력 메시지: `WELCOME UTIL MODULE : Mon Apr 08 2019 11:01:30 GMT+0900 (Korean Standard Time)
result is Mon Apr 08 2019 11:01:30 GMT+0900 (Korean Standard Time)`

에러가 발생하지 않고 정상적으로 실행되었지만 원하는 결과가 출력되지 않았다.

```javascript
// main.js
const { sum } = require("./util");

function runProgram(arr) {
    const result = sum(arr);
    return `result is ${result}`;
}

const result = runProgram([undefined, 1,2,3,4,5,-1,"3"]);
console.log(result); //result is 14
```

```javascript
// util.js
(function callModuleChecker(){
    result = new Date();
    console.log("WELCOME UTIL MODULE : " + result);
})();

module.exports.sum = (arr) => {
    result = result || 0;

    for (const i = 0; i < arr.length; i++) {
        if (typeof arr !== undefined) continue;
        result += arr[i]
    }

    return result;
}
```

원인: `util.js`에서 `callModuleChecker` 함수와 `sum` 함수의 `result` 가 전역변수이기 때문에 공유되고 있는 상황이다. 이는 `result`가 호이스팅 되었기 때문에 발생한 현상이었다.

해결 방법각 함수의 `result`를 `let` 으로 선언한다.

디버깅 과정에서 루프 내의 인덱스 변수가 ` const`로 선언되어 있는 것을 발견하여 `let` 으로 변경함.

### 세번째 시도

에러 메시지: `ReferenceError: result is not defined`

```javascript
// main.js
const { sum } = require("./util");

function runProgram(arr) {
    const result = sum(arr);
    return `result is ${result}`;
}

const result = runProgram([undefined, 1,2,3,4,5,-1,"3"]);
console.log(result); //result is 14
```

```javascript
// util.js
(function callModuleChecker(){
    let result = new Date();
    console.log("WELCOME UTIL MODULE : " + result);
})();

module.exports.sum = (arr) => {
    let result = result || 0;

    for (let i = 0; i < arr.length; i++) {
        if (typeof arr !== undefined) continue;
        result += arr[i]
    }

    return result;
}
```

원인: `result` 변수를 `let` 으로 선언하면서 `result || 0` 표현식이 평가될 때, `result` 가 존재하지 않는 상태이기 때문에 에러가 발생했다.

해결 방법: `result`에 0을 할당하였다.

#### 네번째 시도

출력 메시지: `WELCOME UTIL MODULE : Mon Apr 08 2019 11:08:10 GMT+0900 (Korean Standard Time)
result is 0`

```javascript
// main.js
const { sum } = require("./util");
function runProgram(arr) {
    const result = sum(arr);
    return `result is ${result}`;
}

const result = runProgram([undefined, 1,2,3,4,5,-1,"3"]);
console.log(result); //result is 14
```

```javascript
// util.js
(function callModuleChecker(){
  let result = new Date();
  console.log("WELCOME UTIL MODULE : " + result);
})();

module.exports.sum = (arr) => {
  let result = 0;

  for (let i = 0; i < arr.length; i++) {
      if (typeof arr[i] === "undefined") continue;
      result += arr[i]
  }

  return result;
}
```

원인: 루프를 돌지 못해서 할당되었던 0이 바로 출력되었다. `typeof` 는 결과를 `string` 으로 반환하고, `undefined` 는 말그대로 `undefined` 타입이었기 때문에 if문이 항상 true가 되어 매 루프마다 continue를 실행하고 있었다.

해결 방법: `typeof`의 operand로 배열이 아닌 배열의 요소로 바꾸고, 그 결과를 문자열 `undefined`와 비교하도록 변경하였다.

### 다섯번째 시도

출력 메시지: `WELCOME UTIL MODULE : Mon Apr 08 2019 11:09:10 GMT+0900 (Korean Standard Time)
result is "143"`

```javascript
// main.js
const { sum } = require("./util");
function runProgram(arr) {
    const result = sum(arr);
    return `result is ${result}`;
}

const result = runProgram([undefined, 1,2,3,4,5,-1,"3"]);
console.log(result); //result is 14
```

```javascript
// util.js
(function callModuleChecker(){
  let result = new Date();
  console.log("WELCOME UTIL MODULE : " + result);
})();

function checkNumber(target){
  return typeof target === 'number';
}

module.exports.sum = (arr) => {
  let result = 0;

  for (let i = 0; i < arr.length; i++) {
        result += checkNumber(arr[i]) ? arr[i] : 0;
  }

  return result;
}

```

원인: 배열 내부에 존재하는 문자열 때문에 `result`의 타입이 `number`에서 `string`으로 타입변환이 이루어졌다.

해결 방법: `number` 타입을 체크하는 함수 하나를 만들고 배열의 원소를 함수에 넣어 `number` 타입일 때만 더하도록 수정하였다.





## 정리

### 스코프

변수를 사용할 수 있는 위치를 말한다.

#### 전역 스코프(Global Scope)

스코프는 계층적이므로 바탕이 되는 무언가가 필요하다. 즉, 프로그램을 실행할 때 암시적으로 주어지는 스코프가 필요한데, 이 스코프를 전역 스코프라고 한다. 

#### 블록 스코프(Block Scope)

`let` 과 `const` 는 식별자(`identifier`, 변수와 상수, 함수의 이름)를 블록 스코프에서 선언한다. `if`, `switch`, `for` 그리고 `while` 의 내부 공간이 블록 스코프이다(`{}` 도 가능). 

#### 함수 스코프(Function Scope)

함수 내부에 변수를 선언하면 변수를 둘러싸고 있는 함수에서만 그 변수를 볼 수 있다. 	

### var, let, const

#### var

`var` 로 선언된 변수의 스코프는 변수의 현재 실행 컨텍스트이다. 즉, 그 변수를 감싼 함수가 되거나  `global` 이 된다.  변수를 다시 선언해도 원래 가지고 있던 값을 그대로 가지고 있다. 

선언하지 않은 변수에 값을 할당하면 암묵적으로 전역 변수가 된다. 선언된 변수와 그렇지 않은 변수의 차이점은 3가지가 있다.

1. 선언된 변수는 선언된 위치의 실행 컨텍스트에 제한된다. 반면, 선언되지 않은 변수는 항상 전역 변수이다.

```javascript
function x(){
  y = 1;
  var z = 2;
}

x();

console.log(y); // 1
console.log(z); // Throws a ReferenceError: z is not defined outside x.
```

`strict mode` 를 사용하면 선언되지 않은 변수에 값을 할당하면 `ReferenceError`가 발생한다.

2. 선언된 변수는 코드가 실행되기 전에 생성된다. 선언하지 않은 변수는 값을 할당하는 코드가 실행될 때까지 존재하지 않는다.

```JavaScript
console.log(a); // undefined or ""
console.log('still going...');
```

```javascript
var a = 1;
console.log(a); // 1
console.log('still going...');
```

3. 선언된 변수는 실행 컨텍스트(함수 또는 전역)에서 `non-configurable` 하고, 선언되지 않은 변수는 `configurable`하다.  `configurable`하다는 것은 제거될 수 있다는 뜻이다.

```javascript
var a = 1;
b = 2;

// delete keyword remove a property of Object.
delete this.a; // Throws a TypeError in strict mode. Fails silently otherwise.
delete this.b; 

console.log(a, b); // Throws a ReferenceError.
// The 'b' property was deleted and no longer exists.
```

선언되지 않은 변수는 전역 변수가 되고, 전역 변수가 된다는 것은 `global` 객체의 프로퍼티가 된다는 뜻이기 때문에 `delete` 키워드를 사용할 수 있는 것이다.

var hoisting

변수 선언은 코드가 실행되기 전에 처리되므로, 변수를 선언하는 것은 코드의 맨 위에 선언하는것과 같다. 이는 변수는 선언되기 전에도 사용될 수 있는 것처럼 보이게 된다. 이를 `hoisting`이라고 한다. 다시 정의하면  `hoisting`은 변수의 선언이 코드의 함수나 global 영역의 맨 위로 이동하는 것처럼 보이는 현상이다.

```javascript
a = 2;
var a;

// ... is implicitly understood as:

var a;
a = 2;
```

이런 이유로, `var`로 선언하는 변수는 해당 스코프의 가장 위에서 하는 것을 권장한다. 

```javascript
function do_something() {
  console.log(bar); // undefined
  var bar = 111;
  console.log(bar); // 111
}

// ...is implicitly understood as:

function do_something() {
  var bar;
  console.log(bar); // undefined
  bar = 111;
  console.log(bar); // 111
}
```

#### let

`let` 은 선언한 변수의 스코프를 block, statement, 또는 변수를 사용하는 expression으로 제한한다.변수를 전역적으로 정의하거나 블록 스코프와 상관없이 함수 전체에 변수를 정의하는 `var` 와는 다르다.

몇가지 특징을 정리하면 다음과 같다.

1. `let` 으로 정의한 변수의 스코프는 변수가 위치한 블록과 블록 내부에 존재하는 블록이다. 이런 특징은 `var` 와 비슷하지만, `var` 의 스코프는 함수 전체라는 점을 명심해야 한다. 전역 변수의 경우, `var` 로 선언한 변수는 global 객체의 프로퍼티가 되지만 `let` 은 그렇지 않다.

```javascript
function varTest() {
  var x = 1;
  if (true) {
    var x = 2;  // same variable!
    console.log(x);  // 2
  }
  console.log(x);  // 2
}

function letTest() {
  let x = 1;
  if (true) {
    let x = 2;  // different variable
    console.log(x);  // 2
  }
  console.log(x);  // 1
}
```

2. `let` 으로 `클로저`를 사용하지 않고 생성자를 흉내낼 수 있다.

```javascript
var Thing;

{
  let privateScope = new WeakMap();
  let counter = 0;

  Thing = function() {
    this.someProperty = 'foo';
    
    privateScope.set(this, {
      hidden: ++counter,
    });
  };

  Thing.prototype.showPublic = function() {
    return this.someProperty;
  };

  Thing.prototype.showPrivate = function() {
    return privateScope.get(this).hidden;
  };
}

console.log(typeof privateScope);
// "undefined"

var thing = new Thing();

console.log(thing);
// Thing {someProperty: "foo"}

thing.showPublic();
// "foo"

thing.showPrivate();
// 1
```

`var` 로 위와 같은 일을 하려면 함수 스코프가 필요하다. 이는 주로 IIFE라고 하는 패턴으로 구현한다.

3. `let` 으로 선언한 변수를 다시 선언하면 `SyntaxError` 가 발생한다.

#### const

블록 스코프에 상수를 선언하는 키워드이다. 한번 값이 할당되면 재할당이 불가능하다. 할당된 값이 객체, 배열 등이면 내부의 값을 변경할 수 있다.

### 동적 타입 바인딩(Dynamic type binding)

변수에 값을 넣을 때 타입이 결정되는 것을 동적 타입 바인딩이라고 한다. 자바스크립트는 동적 타입 바인딩이다.

### `typeof` 만으로 타입을 완벽하게 확인할 수 있을까?

다음 예제를 보자.

```
typeof []; // object
typeof {}; // object
typeof ''; // string
typeof new Date() // object
typeof 1; // number
typeof function () {}; // function
typeof /test/i; // object
typeof true; // boolean
typeof null; // object
typeof undefined; // undefined
```

`function`, `array`, `null`, `Date`, `RegExp`등이 `object` 타입이라는 결과가 반환된다. 

`typeof` 키워드는 `primitive` 은 정확하지만 참조 값에 대한 타입은 정확하지 않다. 

정확한 객체 타입을 출력하려면 아래의 코드를 사용해야 한다.

```javascript
Object.prototype.toString.call();
```

```javascript
Object.prototype.toString.call([]); // [object Array]
Object.prototype.toString.call({}); // [object Object]
Object.prototype.toString.call(''); // [object String]
Object.prototype.toString.call(new Date()); // [object Date]
Object.prototype.toString.call(1); // [object Number]
Object.prototype.toString.call(function () {}); // [object Function]
Object.prototype.toString.call(/test/i); // [object RegExp]
Object.prototype.toString.call(true); // [object Boolean]
Object.prototype.toString.call(null); // [object Null]
Object.prototype.toString.call(); // [object Undefined]

var getType = function (elem) {
  return Object.prototype.toString.call(elem);
};
if (getType(person) === '[object Object]') {
  person.getName();
}

```

#### instanceof

`instanceof` 연산자는 생성자의 `prototype` 프로퍼티가 객체의 프로토타입 체인에 존재하는지 확인한다.

```javascript
function Car(make, model, year) {
  this.make = make;
  this.model = model;
  this.year = year;
}
var auto = new Car('Honda', 'Accord', 1998);

console.log(auto instanceof Car); // true

console.log(auto instanceof Object); // true
```



### Default parameter

함수의 파라미터에 default function parameter를 사용하면 값이 없거나 `undefined` 일 경우 파라미터를 기본값으로 초기화 할 수 있다.

#### 특징

1. Default argument는 호출 시에 평가된다. Python에서와는 다르게, 새로운 객체는 호출될 때마다 생성된다. 

```javascript
function append(value, array = []) {
  array.push(value);
  return array;
}

append(1); //[1]
append(2); //[2], [1, 2]가 아니라
```

2. Default parameter는 다른 default parameter에서도 사용할 수 있다.

```javascript
function singularAutoPlural(singular, plural = singular+"s",
                            rallyingCry = plural + " ATTACK!!!") {
  return [singular, plural, rallyingCry ];
}

//["Gecko","Geckos", "Geckos ATTACK!!!"]
singularAutoPlural("Gecko");

//["Fox","Foxes", "Foxes ATTACK!!!"]
singularAutoPlural("Fox","Foxes");

//["Deer", "Deer", "Deer ... change."]
singularAutoPlural("Deer", "Deer", "Deer peaceably and respectfully
   petition the government for positive change.")
```

### Rest parameter

Rest parameter는 정해지지 않은 수의 인수를 배열로 나타내도록 한다.

```javascript
function sum(...theArgs) {
  return theArgs.reduce((previous, current) => {
    return previous + current;
  });
}

console.log(sum(1, 2, 3));
// expected output: 6

console.log(sum(1, 2, 3, 4));
// expected output: 10
```

#### 특징

1. Rest parameter와 `arguments` 객체 사이에는 세 가지 차이점이 있다.

   - Rest parameter는 이름이 주어지지 않은 나머지 파라미터들의 배열이지만, `arguments` 객체는 함수로 전달된 모든 인수를 포함한다.
   - `arguments` 객체는 실제 배열이 아니고 rest parameter는 배열이다. 즉 배열에 내장된 함수(`map`, `sort` 등 ) 를 바로 적용할 수 있다.
   - 즉 `arguments` 객체는 자체에 특정 추가 기능이 있다 (`callee` 속성처럼).

2. Rest parameter는 해체 할당이 가능하다.

   ```javascript
   function f(...[a, b, c]) {
     return a + b + c;
   }
   
   f(1)          // NaN (b 와 c 는 undefined)
   f(1, 2, 3)    // 6
   f(1, 2, 3, 4) // 6 (4번 째 파라미터는 해체되지 않음)
   ```



### Call by value, Call by reference

```javascript
function callByValue(a){
  a = 20;
  console.log(a); // 20
}

function callByReference(obj){
  obj.name = 'squad';
  console.log(obj.name); // squad
}

var a = 10;
console.log(a); // 10
callByValue();
console.log(a); // 10

var obj = {name: 'code'};
console.log(obj.name); // 'code'
callByReference();
console.log(obj.name); // 'squad'
```





## References

[ MDN - `var` 키워드](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/var)

[MDN - `let` 키워드](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/let)

`const` 키워드: <https://developer.mozilla.org/en-US/search?q=const>

동적 타입 바인딩: <https://m.blog.naver.com/PostView.nhn?blogId=hjdu21&logNo=220728153470&proxyReferer=https%3A%2F%2Fwww.google.com%2F>

안전한 타입 체크: <https://ultimatecourses.com/blog/understanding-javascript-types-and-reliable-type-checking>

`instanceof` : <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/instanceof>

Default parameter: <https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Functions/Default_parameters>

Rest parameter: <https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Functions/rest_parameters>