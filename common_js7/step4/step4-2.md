# Step 4-2. 비동기 프로그래밍

## Node.js 비동기 기본

### 비동기

자바스크립트는 하나의 스레드만 사용할 수 있다. 이는 Call stack을 한 개만 가지고 있고 한 번에 하나의 작업만 할 수 있다는 뜻이다. 이러한 한계를 극복하기 위해 비동기를 사용한다.

### 이벤트 기반(Event-Driven) 시스템

이벤트가 발생하면 미리 저장되어 있던 함수를 수행하는 방식이다. 이벤트가 발생할 때 실행할 함수를 지정하는 것을 **이벤트 리스너**에 **콜백 함수**를 등록한다고 한다. 

### Event loop, Task queue, Background

- 이벤트 루프: 이벤트가 발생할 때 실행되는 함수들을 관리하고, 콜백 함수의 실행 순서를 결정한다. 
- 태스크 큐: 이벤트 발생 후 실행되어야 할 함수들이 여기에 저장된다. 콜백 함수가 큐에 들어가는 순서는 이벤트 루프가 결정한다.
- 백그라운드: 타이머나 I/O 태스크 콜백, 이벤트 리스너가 대기하는 곳이다.

### Non-Blocking I/O 

**Non-blocking** 은 이전 작업을 기다리지 않고 다음 작업을 수행하는 것이다. 따라서 동시간에 여러 작업을 할 수 있게 되는 것이다. 하지만 싱글 스레드를 사용하는 자바스크립트 환경에서는 non-blocking을 사용해도 모든 작업에 시간적으로 이득을 볼 수는 없다. 따라서 비교적 작업시간이 긴 I/O 작업에 이를 적용한다. I/O 작업에는 파일 시스템에서 파일을 조작하거나 네트워크로 요청을 날리는 등의 작업이 있다. 

### 프로세스와 스레드

#### 프로세스

파일 시스템에 저장되어 있는 프로그램을 실행하면 메인 메모리로 로드된다. 메인 메모리에 로드된 프로그램의 인스턴스를 프로세스라고 한다. 

#### 스레드

프로세스에 존재하는 실행 흐름으로, 한 개의 스레드를 가질 수도 있고, 여러 개의 스레드를 가질 수도 있다. 각 스레드는 각자 하나의 스택을 가진다. 또한 프로세스 내부에 존재하므로 프로세스가 사용할 수 있는 자원(메모리 등)을 공유할 수 있다. 

#### 프로세스 간 메모리 공유

기본적으로 프로세스 간 메모리 공유는 불가능하다. 따라서 이를 가능케하는 솔루션이 필요하며 대표적으로는 [Redis](https://redis.io/)가 있다.



## 동기와 비동기에서 Call Stack 탐색

### 동기

```javascript
const baseData = [1,2,3,4,5,6,100];

function foo() {
  baseData.forEach((v,i) => {
    console.log("sync ", i);
    bar();
  });
}

function bar() {
  baseData.forEach((v,i) => {
    console.log("sync 2", i);
  });
}

foo();
```

코드를 실행하면 `foo` 내부에서 `baseData` 의 요소를 하나씩 순회하면서 `bar` 함수를 호출하게 될 것이다. 따라서 출력되는 결과는 항상 아래처럼 나올 것이다.

```console
$ node test.js
sync  0
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
sync 2 5
sync 2 6
sync  1
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
sync 2 5
sync 2 6
sync  2
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
...
```

Call stack을 그림으로 나타내면 다음과 같다. `foo` 에서 `forEach` 로 배열을 순회하면서 `bar` 함수를 반복적으로 호출하게 된다. 

<img width="986" alt="image-20190416113745820" src="https://user-images.githubusercontent.com/18232901/56178168-34b39780-603c-11e9-8e5b-eb5e33ca889e.png">



#### 중첩된 setTimeout

```javascript
const baseData = [1,2,3,4,5,6,100];

const asyncRun = (arr, fn) => {
   arr.forEach((v,i) => {
     setTimeout(() => {
       setTimeout(() => {
         console.log("cb 2");
         fn(i)
        },1000);
       console.log("cb 1");
     }, 1000);
   });
}

asyncRun(baseData, idx =>console.log(idx))
```

콜 스택, 백그라운드 타이머, 콜백 큐, 이벤트 루프를 사용하여 실행 흐름을 나타내었다.

![nested_setTimeout](https://user-images.githubusercontent.com/18232901/56215982-8f301080-609b-11e9-8677-844578747f67.gif)

## Promise



## Reference

[콜 스택과 이벤트 루프 - Zerocho](https://www.zerocho.com/category/JavaScript/post/597f34bbb428530018e8e6e2)

