# Step 2-1. 다각형의 넓이

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

`var` 로 선언된 변수의 스코프는 변수의 현재 실행 컨텍스트이다. 즉, 그 변수를 감싼 함수가 되거나 함수 외부에서 선언된 경우에 `global` 이 된다.  

`var` 선언은 어느 위치에 있던 상관없이 코드가 실행되기 전에 처리된다. 이를 `hoisting` 이라고 한다. 



- var
- const
- let
- 안적을 경우 = 추정(자동으로 var?)

* 호이스팅과 scope
- let vs var : 호이스팅 유무

* 타입과 타입체크, 타입은 언제 결정되는가?

- typeof만으로 온전히 체크가능한가?