# Node.js와 개발환경

## Module 방식의 개발

Node.js에서는 각각의 파일을 모듈로 간주한다. 모듈을 불러오려면 `require`를 사용한다.

```javascript
const add = require('./modules/add');
```

`./modules/add.js`파일 내부는 다음과 같다.

```JavaScript
module.exports = (a, b) => a + b;
```

관련 문서는 [여기](https://nodejs.org/api/modules.html#modules_exports_shortcut)를 참고.

## 디버깅

터미널에서 `node inspect file.js` 을 입력하면 디버그 모드로 자바스크립트가 실행된다.

```console
❯ node inspect module_test.js
< Debugger listening on ws://127.0.0.1:9229/04e835ce-8cd2-403a-a8c3-4b416df36980
< For help, see: https://nodejs.org/en/docs/inspector
< Debugger attached.
Break on start in file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/module_test.js:1
> 1 (function (exports, require, module, __filename, __dirname) { const add = require('./ops/add');
  2
  3 let a = 9, b = 3;
debug>
```

디버그 쉘에서 `help`를 입력하면 사용할 수 있는 명령어를 볼 수 있다.

### Breakpoint

프로그램을 의도적으로 중단시킬 위치를 breakpoint라고 한다. 버그의 원인이라고 짐작가는 부분에 breakpoint를 설정하고, 그 곳에서 프로그램을 한 줄 씩 실행하여 디버깅을 진행한다.

디버그 쉘에서 `setBreakpoint` 또는 `sb` 로 breakpoint를 설정할 수 있다. Argument로 breakpoint를 설정할 줄 번호를 입력한다. 다른 파일에 breakpoint를 설정하고 싶다면 파일 이름과 줄 번호를 같이 주면 된다.
`breakpoints`로 현재 설정된 breakpoint의 목록을 볼 수 있다.

```console
debug> sb(3)
  1 (function (exports, require, module, __filename, __dirname) { const add = require('./ops/add');
  2
> 3 let a = 9, b = 3;
  4 console.log(add(a++ ,b));
  5 ++b;
  6 console.log(add(a ,b));
  7
  8 // console.log(mul(a ,b));
debug> breakpoints
#0 file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/module_test.js:3
debug>
```

`cont`를 입력하면 breakpoint까지 프로그램을 실행한다. 

Breakpoint를 제거하려면 `cb`를 사용한다. 파일 이름을 반드시 같이 넣어줘야 한다.

```console
debug> breakpoints
#0 file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/module_test.js:3
debug> cb('module_test.js', 3);
debug>
```

### Watch

보고 싶은 변수를 watch로 설정할 수 있다. 

```console
debug> watch('a')
debug> next
break in file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/module_test.js:3
Watchers:
  0: a = undefined

  1 (function (exports, require, module, __filename, __dirname) { const add = require('./ops/add');
  2
> 3 let a = 9, b = 3;
  4 console.log(add(a++ ,b));
  5 ++b;
debug> next
break in file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/module_test.js:3
Watchers:
  0: a = 9

  1 (function (exports, require, module, __filename, __dirname) { const add = require('./ops/add');
  2
> 3 let a = 9, b = 3;
  4 console.log(add(a++ ,b));
  5 ++b;
debug>
```

`watch`에는 어떤 표현식(expression)이라도 사용 할 수 있다.

```console
debug> n
break in file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/module_test.js:4
Watchers:
  0: a===10 = false

  2
  3 let a = 9, b = 3;
> 4 console.log(add(a++ ,b));
  5 ++b;
  6 console.log(add(a ,b));
debug> n
< 12
break in file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/module_test.js:5
Watchers:
  0: a===10 = true

  3 let a = 9, b = 3;
  4 console.log(add(a++ ,b));
> 5 ++b;
  6 console.log(add(a ,b));
  7
```

### Call Stack

[MDN](https://developer.mozilla.org/ko/docs/Glossary/Call_stack)에서 `Call Stack`의 정의를 이렇게 내렸다.

> **호출 스택**은 여러 함수들([functions](https://developer.mozilla.org/ko/docs/Glossary/function))을 호출하는 스크립트에서 해당 위치를 추적하는 인터프리터 (웹 브라우저의 자바스크립트 인터프리터같은)를 위한 메커니즘입니다. 현재 어떤 함수가 동작하고있는 지, 그 함수 내에서 어떤 함수가 동작하는 지, 다음에 어떤 함수가 호출되어야하는 지 등을 제어합니다.
>
> - 스크립트가 함수를 호출하면 인터프리터는 이를 호출 스택에 추가한 다음 함수를 수행하기 시작합니다.
> - 해당 함수에 의해 호출되는 모든 함수는 호출 스택에 추가되고 호출이 도달하는 위치에서 실행합니다.
> - 메인 함수가 끝나면 인터프리터는 스택을 제거하고 메인 코드 목록에서 중단된 실행을 다시 시작합니다.
> - 스택이 할당된 공간보다 많은 공간을 차지하면 "stack overflow" 에러가 발생합니다.

```console
function greeting() {
   // [1] Some codes here
   sayHi();
   // [2] Some codes here
}
function sayHi() {
   return "Hi!";
}

// Invoke the `greeting` function
greeting();

// [3] Some codes here
```

위의 코드에서 실행흐름은 `greating()`, `sayHi()`,`return "Hi!"` 가 될 것이다.

최초에 `node inspect`를 실행하고 `backtrace`또는 `bt`를 입력하면 다음과 같다.

```console
❯ node inspect call_stack.js
< Debugger listening on ws://127.0.0.1:9229/15849da3-9d70-4d00-949f-99646adc6841
< For help, see: https://nodejs.org/en/docs/inspector
< Debugger attached.
Break on start in file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/call_stack.js:8
  6 }
  7
> 8 greeting();
  9
 10 });
debug> bt
#0 (anonymous) file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/call_stack.js:8:0
#1 Module._compile internal/modules/cjs/loader.js:733:13
#2 Module._extensions..js internal/modules/cjs/loader.js:747:9
#3 Module.load internal/modules/cjs/loader.js:628:31
#4 tryModuleLoad internal/modules/cjs/loader.js:568:11
#5 Module._load internal/modules/cjs/loader.js:560:2
#6 Module.runMain internal/modules/cjs/loader.js:801:11
#7 executeUserCode internal/bootstrap/node.js:526:14
#8 startMainThreadExecution internal/bootstrap/node.js:439:2
```

이 상태에서 `step into` 하고 `bt`를 보면 다음과 같다.

```console
debug> s
break in file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/call_stack.js:2
  1 (function (exports, require, module, __filename, __dirname) { function greeting() {
> 2    sayHi();
  3 }
  4 function sayHi() {
debug> bt
#0 greeting file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/call_stack.js:2:3
#1 (anonymous) file:///Users/mcc/Workspace/Web/JavaScript/functional_programming/call_stack.js:8:0
#2 Module._compile internal/modules/cjs/loader.js:733:13
#3 Module._extensions..js internal/modules/cjs/loader.js:747:9
#4 Module.load internal/modules/cjs/loader.js:628:31
#5 tryModuleLoad internal/modules/cjs/loader.js:568:11
#6 Module._load internal/modules/cjs/loader.js:560:2
#7 Module.runMain internal/modules/cjs/loader.js:801:11
#8 executeUserCode internal/bootstrap/node.js:526:14
#9 startMainThreadExecution internal/bootstrap/node.js:439:2
```

`greeting` 함수가 call stack 리스트에 추가 된 것을 확인할 수 있다. 

### Step over/ Step into / Step out

- Step **into** 는 현재 라인에 함수가 있다면 디버거의 실행 위치를 그 함수로 넘긴다. 위의 예제에서 8번째 라인에서 `s` 를 입력하고 `greeting`함수로 들어간 것을 볼 수 있다.
- Step **over**는 다음 함수로 넘어가지 않고 다음 줄로 넘어간다. 
- Step **out**는 다음 `return`을 만날 때 까지 프로그램을 진행한다. 



## Chrome에서의 디버깅

터미널에서 Node.js 디버거를 실행하고 Chrome 주소창에 `chrome://inspect`을 입력한다.

<img width="1662" alt="image-20190405153349953" src="https://user-images.githubusercontent.com/18232901/55608320-2a320c00-57b9-11e9-9ef7-ccf24dbfd0a1.png">

터미널에서 실행한 디버깅 목록을 Chrome에서도 확인할 수 있음을 알 수 있다. `inspect`를 누르면 Chrome 환경에서 디버깅할 수 있다.

![image-20190405153756637](https://user-images.githubusercontent.com/18232901/55608362-3a49eb80-57b9-11e9-9936-7056b49d84bf.png)



## 참고 자료

[Node.js 디버깅 관련 문서](https://developer.ibm.com/tutorials/learn-nodejs-debugging-and-profiling-node-applications/)